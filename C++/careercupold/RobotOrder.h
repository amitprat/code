#pragma once
#include "../Header.h"

class RobotOrder {
	struct Item {
		string name;
		double price;
		int quantity;
		int order;

		virtual bool prepare() = 0;
		virtual double amount() {
			return price * order;
		}
	};
	struct Sandwich : public Item {
		Sandwich(int order) : Item() {
			this->order = order;
			this->name = "Sandwich";
			this->price = 1;
			this->quantity = 100;
		}

		bool prepare() {
			if (order >= quantity) {
				cout << "Can't serve item" << endl;
				return false;
			}

			quantity -= order;
			cout << "Preparing order" << endl;

			return true;
		}
	};
	struct Coffee : public Item {
		Coffee(int order) : Item() {
			this->order = order;
			this->name = "Coffee";
			this->price = 1;
			this->quantity = 100;
		}

		bool prepare() {
			if (order >= quantity) {
				cout << "Can't serve item" << endl;
				return false;
			}

			quantity -= order;
			cout << "Preparing order" << endl;

			return true;
		}
	};
	struct Customer {
		string name;
		double balance;
		vector<Item*> orders;

		Customer(string name, double balance) :name(name), balance(balance) {}
	};
	struct Order {
		Customer customer;
		vector<Item*> items;

		void addItem(Item* item) {
			items.push_back(item);
		}

		double getAmount() {
			double amount = 0;
			for (auto& item : items) {
				amount += item->amount();
			}

			return amount;
		}
	};

private:
	vector<Order> orders;

public:
	bool takeOrder(Order order) {
		double balance = order.customer.balance;
		double totalAmount = order.getAmount();

		if (balance < totalAmount) {
			cout << "Payment rejected" << endl;
			return false;
		}
		order.customer.balance -= totalAmount;
		orders.push_back(order);

		return true;
	}

	void prepare() {
		for (auto order : orders) {
			for (auto item : order.items) {
				item->prepare();
			}
			cout << "Order prepared for customer " << order.customer.name << ", serving food.." << endl;
		}
	}

	void summary()
	{
		for (auto order : orders) {
			cout << "Orders for customer: " << order.customer.name << ":" << endl;
			for (auto item : order.items) {
				cout << item->name << " " << item->order << endl;
			}
			cout << "Total amount for customer is " << order.getAmount() << endl;
		}
	}
public:
	static void test() {
		RobotOrder robot;

		Customer customer1 = Customer("Person1", 10);
		Order order1(customer1);
		Sandwich* sandwich = new Sandwich(2);
		order1.addItem(sandwich);
		robot.takeOrder(order1);

		Customer customer2 = Customer("Person2", 10);
		Order order2(customer2);
		Coffee* coffee = new Coffee(2);
		order2.addItem(coffee);
		robot.takeOrder(order2);

		robot.prepare();

		robot.summary();
	}
};