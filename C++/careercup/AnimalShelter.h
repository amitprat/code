#include <compare>

#include "../header.h"

class AnimalShelter {
   public:
    static void test() {
        AnimalShelter obj;
        obj.push({"Dog", "jacky"});
        obj.push({"Cat", "pussy"});

        auto animal = obj.top();
        cout << "Top Animal: " << animal.to_string() << endl;

        auto dog = obj.top(AnimalType::DOG);
        cout << "Top Dog: " << dog.to_string() << endl;

        obj.push({"Cat", "pissa"});

        auto cat = obj.top(AnimalType::CAT);
        cout << "Top Cat: " << cat.to_string() << endl;
    }

   private:
    enum class AnimalType {
        DOG,
        CAT
    };
    struct AnimalDetail {
        string name;

        string to_string() {
            return "Name: " + name;
        }
    };
    struct Order {
        int position = 0;
        bool operator<=>(const Order& that) const = default;

        string to_string() {
            return "Position: " + std::to_string(position);
        }
    };
    struct AnimalInfo {
        AnimalType type;
        AnimalDetail detail;
        Order order;

        AnimalInfo(string type, string name) {
            this->detail.name = name;

            if (type == "Cat")
                this->type = AnimalType::CAT;
            else if (type == "Dog")
                this->type = AnimalType::DOG;
        }

        string to_string() {
            stringstream ss;
            ss << "{Type: " << (type == AnimalType::DOG ? "Dog" : "Cat") << ", ";
            ss << detail.to_string() << ", ";
            ss << order.to_string() << "}";

            return ss.str();
        }
    };

    stack<AnimalInfo> dogsInfo;
    stack<AnimalInfo> catsInfo;
    int globalOrder = -1;

    void push(AnimalInfo info) {
        globalOrder++;
        info.order.position = globalOrder;

        if (info.type == AnimalType::DOG) {
            dogsInfo.push(info);
        } else if (info.type == AnimalType::CAT) {
            catsInfo.push(info);
        }
    }

    AnimalInfo pop() {
        if (dogsInfo.empty()) return pop(AnimalType::CAT);
        else if (catsInfo.empty()) return pop(AnimalType::DOG);

        auto dog = dogsInfo.top();
        auto cat = catsInfo.top();
        if (dog.order > cat.order) {
            dogsInfo.pop();
            return dog;
        } else {
            catsInfo.pop();
            return cat;
        }
    }

    AnimalInfo top() {
        if (isEmpty())
            throw runtime_error("No animals are available.");

        auto dog = dogsInfo.top();
        auto cat = catsInfo.top();
        if (dog.order > cat.order) {
            return dog;
        } else {
            return cat;
        }
    }

    AnimalInfo pop(AnimalType type) {
        if (isEmpty())
            throw runtime_error("No animals are available.");

        if (type == AnimalType::DOG)
            return popDog();
        if (type == AnimalType::CAT)
            return popCat();
    }

    AnimalInfo popDog() {
        if (dogsInfo.empty())
            throw runtime_error("No dogs available.");

        auto val = dogsInfo.top();
        dogsInfo.pop();
        return val;
    }

    AnimalInfo popCat() {
        if (catsInfo.empty())
            throw runtime_error("No cats available.");

        auto val = catsInfo.top();
        catsInfo.pop();
        return val;
    }

    AnimalInfo top(AnimalType type) {
        if (isEmpty())
            throw runtime_error("No animals are available.");

        if (type == AnimalType::DOG)
            return topDog();
        if (type == AnimalType::CAT)
            return topCat();
    }

    AnimalInfo topDog() {
        if (dogsInfo.empty())
            throw runtime_error("No dogs available.");

        return dogsInfo.top();
    }

    AnimalInfo topCat() {
        if (catsInfo.empty())
            throw runtime_error("No cats available.");

        return catsInfo.top();
    }

    bool isEmpty() {
        return dogsInfo.empty() && catsInfo.empty();
    }
};

class AnimalShelter2 {
    struct AnimalInfo {
        string name;
        string type;
        int globalOrder;

        string to_string() {
            stringstream ss;
            ss << "{" << name << ", " << type << ", " << globalOrder << "}";
            return ss.str();
        }
    };

    stack<AnimalInfo> dogs, cats;
    int globalOrder = 0;

   public:
    void push(const string& name, const string& type) {
        type == "dog"
            ? dogs.push(AnimalInfo{.name = name, .type = "dog", .globalOrder = globalOrder})
            : cats.push(AnimalInfo{.name = name, .type = "cat", .globalOrder = globalOrder});
        globalOrder++;
    }

    AnimalInfo pop() {
        auto dog = top("dog");
        auto cat = top("cat");
        if (dog.globalOrder > cat.globalOrder) {
            dogs.pop();
            return dog;
        } else {
            cats.pop();
            return cat;
        }
    }

    AnimalInfo pop(const string& type) {
        if (type == "dog" && dogs.empty()) throw runtime_error("No dogs found");
        if (type == "cat" && cats.empty()) throw runtime_error("No cat found");

        AnimalInfo animal;
        if (type == "dog") {
            animal = dogs.top();
            dogs.pop();
        } else {
            animal = cats.top();
            cats.pop();
        }

        return animal;
    }

    AnimalInfo top() {
        auto dog = top("dog");
        auto cat = top("cat");
        return dog.globalOrder > cat.globalOrder ? dog : cat;
    }

    AnimalInfo top(const string& type) {
        if (type == "dog" && dogs.empty()) return AnimalInfo{.type = "dog", .globalOrder = -1};
        if (type == "cat" && cats.empty()) return AnimalInfo{.type = "cat", .globalOrder = -1};
        return type == "dog" ? dogs.top() : cats.top();
    }

    bool empty() { return dogs.empty() && cats.empty(); }

   public:
    static void test() {
        AnimalShelter2 obj;
        obj.push("jacky", "dog");
        obj.push("pussy", "cat");

        auto animal = obj.top();
        cout << "Top Animal: " << animal.to_string() << endl;

        auto dog = obj.top("dog");
        cout << "Top Dog: " << dog.to_string() << endl;

        obj.push("pissa", "cat");

        auto cat = obj.top("cat");
        cout << "Top Cat: " << cat.to_string() << endl;
    }
};