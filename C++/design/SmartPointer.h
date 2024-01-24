#pragma once
#include "../header.h"

template <class T>
class SmartPointer {
    T* obj = nullptr;
    int* refcount = nullptr;

public:
    SmartPointer() {
        refcount = new int();
        *refcount = 0;
    }
    SmartPointer(T* obj) {
        cout << "Creating smart pointer" << obj->to_string() << endl;
        this->obj = obj;
        this->refcount = new int();
        *refcount = 1;
    }
    SmartPointer(const SmartPointer& that) {
        cout << "Copy construct that " << that.obj->to_string() << " to this " << (obj ? obj->to_string() : "null") << endl;
        this->obj = that.obj;
        this->refcount = that.refcount;
        (*refcount)++;
    }
    SmartPointer<T>& operator =(const SmartPointer& that) {
        cout << "Assigning that" << that.obj->to_string() << " to this " << (obj ? obj->to_string() : "null") << endl;
        if (*this == that) return *this;
        this->remove();

        refcount = that.refcount;
        (*refcount)++;
        obj = that.obj;

        return *this;
    }

    bool operator ==(const SmartPointer& that) {
        return this->obj == that.obj;
    }

    T& operator* () {
        return *obj;
    }

    ~SmartPointer() {
        this->remove();
    }

    T* getValue() {
        return obj;
    }

    string to_string() {
        const void* address = static_cast<const void*>(obj);
        std::stringstream ss;
        ss << "{";
        ss << "Address = " << address;
        ss << ", ";
        ss << "RefCnt = " << *refcount;
        ss << "}";

        return ss.str();
    }

private:
    void remove() {
        if (*refcount == 0) return;
        (*refcount)--;
        if (*refcount == 0) {
            cout << "Deleting obj " << obj->to_string() << endl;
            delete obj;
        }
    }
};

class Student {
public:
    string name;
    int age = 20;
    Student(string name) :name(name) {}

    string to_string() {
        return "{" + name + ", " + std::to_string(age) + "}";
    }
};

class SmartPointerTest {
public:
    static void test() {
        SmartPointer<Student> other(new Student("Student1"));
        SmartPointer<Student> unassigned;
        SmartPointer<Student> otherref = other;
        cout << other.to_string() << endl;
        {
            SmartPointer<Student> obj(new Student("Student2"));
            other = obj;
            unassigned = other;
        }
        SmartPointer<Student> obj1(new Student("Student3"));
        SmartPointer<Student>* obj2 = new SmartPointer<Student>(new Student("Student4"));

        cout << other.to_string() << endl;
        cout << unassigned.to_string() << endl;
        cout << otherref.to_string() << endl;
        cout << obj1.to_string() << endl;

        delete obj2;
    }
};