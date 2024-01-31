#include <iostream>

int main() {
    int x = 1;
    auto multiply = [&x](int y)->int{ // Anonymous function takes a reference to x. Returns an int
        return x*y;
    };
    std::cout << multiply(5) << std::endl;
    x = 2;
    std::cout << multiply(5) << std::endl;
    return 0;
}