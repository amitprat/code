#include "Person.h"

class Person::Impl {
   private:
    string name;
    int age;

   public:
    Impl(const string& name, int age) : name(name), age(age) {}

    void greet() const {
        cout << "Hello world!" << endl;
    }
};

// constructor/destructor
Person::Person(const string& name, int age) : pImpl(make_unique<Impl>(name, age)) {}
Person::~Person() = default;

// copy constructor
Person::Person(const Person& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {}
Person& Person::operator=(const Person& other) {
    if (this != &other) {
        *pImpl = *other.pImpl;
    }

    return *this;
}

// move constructor
Person::Person(Person&& other) noexcept = default;
Person& Person::operator=(Person&& other) noexcept = default;

void Person::greet() const {
    pImpl->greet();
}

void PersonTest::test() {
    unique_ptr<Person> person = std::make_unique<Person>("Amit", 30);
    person->greet();
}