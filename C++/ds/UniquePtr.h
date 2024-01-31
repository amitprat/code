#include "../header.h"

/*
Ref: https://codereview.stackexchange.com/questions/163854/my-implementation-for-stdunique-ptr
https://medium.com/swlh/c-smart-pointers-and-how-to-write-your-own-c0adcbdce04f
*/
template <typename T>
class UniquePtr {
   private:
    T* obj = nullptr;

   public:
    // constructor
    explicit UniquePtr(T* obj) : obj(obj) {
        cout << "Constructed obj" << endl;
    }

    // destructor
    ~UniquePtr() {
        cout << "Deleted obj" << endl;
        delete obj;
    }

    // move copy constructor
    UniquePtr(UniquePtr&& that) noexcept : obj(that.obj) {
        cout << "Move copy constructed" << endl;
        that.obj = nullptr;
    }

    // move assignment
    UniquePtr& operator=(UniquePtr&& that) noexcept {
        cout << "Move assignment" << endl;
        if (this != &that) {
            delete obj;
            obj = that.obj;
            that.obj = nullptr;
        }

        return *this;
    }

    // assignment is deleted
    UniquePtr operator=(const UniquePtr that) = delete;

    // copy constructor is deleted
    UniquePtr(const UniquePtr& that) = delete;

    // Access operator
    T& operator*() const { return *obj; }

    T* operator->() const { return obj; }
};

class Student {
   public:
    string name;
    int age;

    Student(const string& name, int age) : name(name), age(age) {}

    string to_string() {
        stringstream ss;
        ss << "{";
        ss << "name: " << this->name << ",";
        ss << "age: " << this->age;
        ss << "}";

        return ss.str();
    }
};

class UniquePtrTest {
   public:
    static void test() {
        cout << "----------Example1-------------------" << endl;
        UniquePtr<Student> ptr(new Student("amit", 12));

        ptr->age = 10;
        cout << ptr->to_string() << endl;

        cout << "----------Example2-------------------" << endl;
        UniquePtr<Student> ptr2 = std::move(ptr);
        ptr2->age = 20;

        cout << ptr2->to_string() << endl;

        cout << "----------Example3-------------------" << endl;
        UniquePtr<Student> ptr3(std::move(ptr2));
        ptr3->age = 30;

        cout << ptr3->to_string() << endl;
        cout << "------------------------------------" << endl;
    }
};
