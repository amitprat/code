#pragma once
#include "../Header.h"

namespace ObserverPattern {
    class IObserver {
    public:
        virtual ~IObserver() {}
        virtual void update(string msg) = 0;
    };

    class ISubject {
    public:
        virtual ~ISubject() {}
        virtual void attach(IObserver* subscriber) = 0;
        virtual void detach(IObserver* subscriber) = 0;
        virtual void notify(string message) = 0;
    };

    class Subscriber : public IObserver {
    public:
        virtual void update(string msg) override {
            cout << "Message recieved from publisher: " << msg << endl;
        }
    };

    class Subject : public ISubject {
    private:
        set<IObserver*> observers;

    public:
        virtual void attach(IObserver* subscriber) override {
            observers.insert(subscriber);
        }

        virtual void detach(IObserver* subscriber) override {
            observers.erase(subscriber);
        }

        virtual void notify(string message) override {
            for (auto ob : observers) {
                ob->update(message);
            }
        }
    };

    class Client {
    public:
        static void test() {
            ISubject* pub = new Subject();
            IObserver* sub1 = new Subscriber();
            IObserver* sub2 = new Subscriber();

            pub->attach(sub1);
            pub->attach(sub2);

            cout << "First Message: " << endl;
            pub->notify("Hello");

            cout << endl << endl;

            pub->detach(sub2);

            cout << "Second Message: " << endl;
            pub->notify("Hello");

            cout << endl << endl;
        }
    };
}