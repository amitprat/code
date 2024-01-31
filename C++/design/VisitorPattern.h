#pragma once
#include "../header.h"

class element_concrete_1;
class element_concrete_2;

class visitor {
   public:
    virtual void visit(element_concrete_1& el) = 0;
    virtual void visit(element_concrete_2& el) = 0;
};

class visitor_concrete : public visitor {
   public:
    virtual void visit(element_concrete_1& el) override {
        // Do something with el
    };
    virtual void visit(element_concrete_2& el) override {
        // Do something with el
    };
};

class element {
   public:
    virtual void accept(visitor& v) = 0;
};

class element_concrete_1 : public element {
   public:
    virtual void accept(visitor& v) override {
        v.visit(*this);
    }
};

class element_concrete_2 : public element {
   public:
    virtual void accept(visitor& v) override {
        v.visit(*this);
    }
};