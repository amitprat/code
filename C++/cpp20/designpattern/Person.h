#pragma once
#include "../../header.h"

class Person {
   private:
    class Impl;
    unique_ptr<Impl> pImpl;

   public:
    Person(const string& name, int age) {}
    ~Person() {}

    void greet() const;

    Person(const Person& other);             // copy constructor
    Person& operator=(const Person& other);  // assignment operator

    Person(Person&& other) noexcept;  // move constructor
    Person& operator=(Person&& other) noexcept;
};

class PersonTest {
   public:
    static void test();
};