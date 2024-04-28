# Given the following code snippet, Create a diagram displaying the virtual table mechanism.

```cpp
class A { 
public: 
virtual void foo() = 0; 
} 

class B : public A { 
void foo(){}; 
} 
```

```
search for vtable explaination on learncpp.com. They have a good explaination with diagrams. 

Every class has a hidden member pointer called vptr. Along with each class there is a static table called Vtable. The vptr points to vtable. Everytime an object is created, the vptr in that object points to the vtable for the class. The vtable contains pointers to the virtual functions. 
The derived class inherits the Base class and along with it gets the vptr. However this vptr points to vtable associated with the derived class. 
When we invoke a virtual function through the Base pointer, it always goes to the vptr. The vptr for the Base class object points to the associated vtable. The vptr for the Derived class points to the vtable of the derived class. And therefore they accesses the correct functions.
```
