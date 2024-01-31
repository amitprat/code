#pragma once
#include "../header.h"

class VariadicTemplate {
   private:
    template <typename T>
    static void printAllImpl(T item) {
        std::cout << item << ' ';
    }

    template <typename T, typename... Args>
    static void printAllImpl(T item, Args... args) {
        printAllImpl(item);
        printAllImpl(args...);
    }

    template <typename... Args>
    static void printAll(Args&&... args) {
        printAllImpl(std::forward<Args>(args)...);
        std::cout << '\n';
    }

   private:
    template <typename T>
    static auto sum(T val) {
        return val;
    }

    template <typename T, typename... Args>
    static auto sum(T first, Args... args) {
        return first + sum(args...);
    }

   public:
    static void test() {
        printAll(3, 2, 1);
        printAll(8.2, 2, 1.1, "duck");
        printAll(23, 32, 8, 11, 9);

        int s = sum(1, 2, 3, 4, 5, 6);
        cout << "Sum = " << s << endl;
    }
};

template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;

class Concepts {
   private:
    static auto add(Number auto a, Number auto b) {
        return a + b;
    }

   public:
    static void test() {
        std::cout << "add(1, 2): " << add(1, 2) << '\n';
        std::cout << "add(1, 2.14): " << add(1, 2.14) << '\n';
        // std::cout << "add(\"one\", \"two\"): " << add("one", "two") << '\n'; // error: invalid operands of types 'const char*' and 'const char*' to binary 'operator+'
        std::cout << "add(true, false): " << add(true, false) << '\n';
    }
};

namespace visitor {
struct NodeA {};
struct NodeB {};
struct NodeC {};

using Nodes = std::variant<NodeA, NodeB, NodeC>;

struct Visitor {
    void operator()(const NodeA&) { std::cout << "NodeA" << std::endl; }
    void operator()(const NodeB&) { std::cout << "NodeB" << std::endl; }
    void operator()(const NodeC&) { std::cout << "NodeC" << std::endl; }
};

static void test() {
    std::vector<Nodes> nodes = {
        NodeA{},
        NodeB{},
        NodeA{},
        NodeC{}};

    for (auto&& node : nodes) std::visit(Visitor{}, node);
}
}  // namespace visitor

class ModernCpp {
   public:
    static void test() {
        VariadicTemplate::test();
        Concepts::test();
        visitor::test();
    }
};