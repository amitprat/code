#pragma once
#include "../header.h"

/*
Output
WindowsButton
WindowsButton
WindowsMenu
WindowsMenu
WindowsButton
*/
#define MOTIF

class AbstractFactoryDesignPattern {
    class Widget {
       public:
        virtual void draw() = 0;
    };

    class MotifButton : public Widget {
       public:
        void draw() { cout << "MotifButton\n"; }
    };
    class MotifMenu : public Widget {
       public:
        void draw() { cout << "MotifMenu\n"; }
    };

    class WindowsButton : public Widget {
       public:
        void draw() { cout << "WindowsButton\n"; }
    };
    class WindowsMenu : public Widget {
       public:
        void draw() { cout << "WindowsMenu\n"; }
    };

    class Factory {
       public:
        virtual Widget* create_button() = 0;
        virtual Widget* create_menu() = 0;
    };

    class MotifFactory : public Factory {
       public:
        Widget* create_button() {
            return new MotifButton;
        }
        Widget* create_menu() {
            return new MotifMenu;
        }
    };

    class WindowsFactory : public Factory {
       public:
        Widget* create_button() {
            return new WindowsButton;
        }
        Widget* create_menu() {
            return new WindowsMenu;
        }
    };

   public:
    static void test() {
        AbstractFactoryDesignPattern obj;
        Factory* factory;

#ifdef MOTIF
        factory = new MotifFactory;
#else  // WINDOWS
        factory = new WindowsFactory;
#endif

        Widget* w = factory->create_button();
        w->draw();

        obj.display_window_one(factory);
    }

    void display_window_one(Factory* factory) {
        Widget* w[] = {factory->create_button(),
                       factory->create_menu()};
        w[0]->draw();
        w[1]->draw();
    }

    void display_window_two(Factory* factory) {
        Widget* w[] = {factory->create_menu(),
                       factory->create_button()};
        w[0]->draw();
        w[1]->draw();
    }
};
