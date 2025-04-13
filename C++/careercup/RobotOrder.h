#pragma once
#include <cassert>
#include <memory>

#include "../header.h"

class RobotOrder {
    struct Item {
        string name;
        double price;
        int quantity;
        int order;

        virtual ~Item() = default;
        virtual bool prepare() = 0;

        virtual double amount() const {
            return price * order;
        }
    };

    struct Sandwich : public Item {
        Sandwich(int orderAmount) {
            name = "Sandwich";
            price = 1;
            quantity = 100;
            order = orderAmount;
        }

        bool prepare() override {
            if (order > quantity) {
                cout << "Can't serve item" << endl;
                return false;
            }
            quantity -= order;
            cout << "Preparing sandwich order" << endl;
            return true;
        }
    };

    struct Coffee : public Item {
        Coffee(int orderAmount) {
            name = "Coffee";
            price = 1;
            quantity = 100;
            order = orderAmount;
        }

        bool prepare() override {
            if (order > quantity) {
                cout << "Can't serve item" << endl;
                return false;
            }
            quantity -= order;
            cout << "Preparing coffee order" << endl;
            return true;
        }
    };

    struct ItemFactory {
        static shared_ptr<Item> create(const string& type, int orderAmount) {
            if (type == "Sandwich") return make_shared<Sandwich>(orderAmount);
            if (type == "Coffee") return make_shared<Coffee>(orderAmount);
            return nullptr;
        }
    };

    struct Customer {
        string name;
        double balance;
        vector<shared_ptr<Item>> orders;

        Customer(const string& name, double balance) : name(name), balance(balance) {}
    };

    struct Order {
        Customer customer;
        vector<shared_ptr<Item>> items;

        Order(const Customer& customer) : customer(customer) {}

        void addItem(shared_ptr<Item> item) {
            items.push_back(item);
        }

        double getAmount() const {
            double total = 0;
            for (const auto& item : items) {
                total += item->amount();
            }
            return total;
        }
    };

    vector<Order> orders;

   public:
    bool takeOrder(const Order& order) {
        double totalAmount = order.getAmount();

        if (order.customer.balance < totalAmount) {
            cout << "Payment rejected" << endl;
            return false;
        }

        orders.push_back(order);
        return true;
    }

    void prepare() {
        for (auto& order : orders) {
            for (auto& item : order.items) {
                item->prepare();
            }
            cout << "Order prepared for customer " << order.customer.name << ", serving food.." << endl;
        }
    }

    void summary() const {
        for (const auto& order : orders) {
            cout << "Orders for customer: " << order.customer.name << ":" << endl;
            for (const auto& item : order.items) {
                cout << item->name << " " << item->order << endl;
            }
            cout << "Total amount for customer is " << order.getAmount() << endl;
        }
    }

    static void test() {
        RobotOrder robot;

        Customer customer1("Person1", 10);
        Order order1(customer1);
        order1.addItem(ItemFactory::create("Sandwich", 2));
        robot.takeOrder(order1);

        Customer customer2("Person2", 10);
        Order order2(customer2);
        order2.addItem(ItemFactory::create("Coffee", 2));
        robot.takeOrder(order2);

        robot.prepare();
        robot.summary();
    }
};