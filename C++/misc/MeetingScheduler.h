#pragma once
#include "../Header.h"

namespace scheduler {
    class Status {
    public:
        bool result = false;
        Status(bool result) : result(result) {}
    };

    class Time {
    public:
        int start, end;
        Time(int start, int end) :start(start), end(end) {}
        bool operator <=(Time other) {
            if (start < other.start) return true;
            if (start > other.start) return false;
            return end <= other.end;
        }
        bool operator >=(Time other) {
            if (start > other.start) return true;
            if (start < other.start) return false;
            return end >= other.end;
        }
        string to_string() {
            return std::to_string(start) + ":" + std::to_string(end);
        }
    };

    class Appointment {
    public:
        Time startTime;
        Time endTime;
        Appointment(Time start, Time end) :startTime(start), endTime(end) {}
        string to_string() {
            return "{" + startTime.to_string() + ", " + endTime.to_string() + "}";
        }
    };

    template <class T>
    class Node {
    public:
        T start;
        T end;
        Node* left = nullptr, * middle = nullptr, * right = nullptr;
        Node(T start, T end) :start(start), end(end) {}
        string to_string() {
            return "{" + start.to_string() + ", " + end.to_string() + "}";
        }
    };

    class Person {
    private:
        Node<Time>* root = nullptr;

    public:
        string name;
        Person(string name) :name(name) {}
        string to_string() {
            return "{" + name + ", root=" + to_string(root) + "}";
        }

        Status schedule(Appointment apt, vector<Person*> persons) {
            auto res = isSlotAvailable(apt);
            if (res != nullptr) {
                cout << "Appointment " << apt.to_string() << " has conflict for person: " << name
                    << " at node = " << res->to_string() << endl;
                return Status(false);
            }
            for (auto person : persons) {
                auto res = person->isSlotAvailable(apt);
                if (res != nullptr) {
                    cout << "Appointment " << apt.to_string() << " has conflict for person: " << name
                        << " at node = " << res->to_string() << endl;
                }
            }

            bookSlot(apt);
            for (auto person : persons) {
                person->bookSlot(apt);
            }

            return Status(true);
        }
        Node<Time>* isSlotAvailable(Appointment apt) {
            if (root == nullptr) return root;
            return isSlotAvailable(root, apt);
        }
        void bookSlot(Appointment apt) {
            if (root == nullptr) {
                root = new Node<Time>(apt.startTime, apt.endTime);
                return;
            }
            root = insert(root, apt);
        }
    private:
        Node<Time>* isSlotAvailable(Node<Time>* cur, Appointment apt) {
            if (cur == nullptr) return cur;
            if (apt.endTime <= cur->start) return isSlotAvailable(cur->left, apt);
            else if (apt.startTime >= cur->end) return isSlotAvailable(cur->right, apt);
            else return cur;
        }
        Node<Time>* insert(Node<Time>* cur, Appointment apt) {
            if (cur == nullptr) return new Node<Time>(apt.startTime, apt.endTime);
            if (apt.endTime <= cur->start) cur->left = insert(cur->left, apt);
            else if (apt.startTime >= cur->end) cur->right = insert(cur->right, apt);
            else cur->middle = insert(cur->middle, apt);
            return cur;
        }
        string to_string(Node<Time>* cur) {
            stringstream ss;
            ss << "{";
            inorder(cur, ss);
            ss << "}";
            return ss.str();
        }
        void inorder(Node<Time>* cur, stringstream& ss) {
            if (cur) {
                inorder(cur->left, ss);
                ss << "(" << cur->start.to_string() << ", " << cur->end.to_string() << ")";
                ss << " ";
                inorder(cur->middle, ss);
                inorder(cur->right, ss);
            }
        }
    };

    class MeetingScheduler {
    public:
        static void test() {
            Person person1("Amit");
            Person person3("Pratap");
            Person person2("Singh");

            Appointment apt1({ 9,30 }, { 11,30 });
            Status status = person1.schedule(apt1, { &person2 });
            print(person1, apt1, status);
            cout << person1.to_string() << endl;
            cout << person2.to_string() << endl;
            cout << endl << endl;

            Appointment apt2({ 11,30 }, { 12,30 });
            status = person2.schedule(apt2, { &person1, &person3 });
            print(person2, apt2, status);
            cout << person1.to_string() << endl;
            cout << person2.to_string() << endl;
            cout << person3.to_string() << endl;
            cout << endl << endl;

            Appointment apt3({ 11,00 }, { 12,30 });
            status = person3.schedule(apt3, { &person2 });
            print(person3, apt3, status);
            cout << person2.to_string() << endl;
            cout << person3.to_string() << endl;
            cout << endl << endl;

            Appointment apt4({ 14,00 }, { 15,30 });
            status = person3.schedule(apt4, { &person1, &person2 });
            print(person3, apt4, status);
            cout << person1.to_string() << endl;
            cout << person2.to_string() << endl;
            cout << person3.to_string() << endl;
            cout << endl << endl;

            Appointment apt5({ 16,00 }, { 18,30 });
            status = person1.schedule(apt5, { &person2 });
            print(person3, apt5, status);
            cout << person1.to_string() << endl;
            cout << person2.to_string() << endl;
            cout << endl << endl;

            Appointment apt6({ 15,30 }, { 18,30 });
            status = person3.schedule(apt5, { });
            print(person3, apt6, status);
            cout << person3.to_string() << endl;
            cout << endl << endl;

            Appointment apt7({ 15,30 }, { 19,30 });
            status = person3.schedule(apt7, { &person1, &person2 });
            print(person3, apt7, status);
            cout << person1.to_string() << endl;
            cout << person2.to_string() << endl;
            cout << person3.to_string() << endl;
            cout << endl << endl;
        }

        static void print(Person person, Appointment appt, Status status) {
            if (!status.result) {
                cout << person.name << " scheduling appointment " << appt.to_string() << " has conflict." << endl;
            }
            else {
                cout << person.name << " scheduling appointment " << appt.to_string() << " scheduled successfully." << endl;
            }
        }
    };
}