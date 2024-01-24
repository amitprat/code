#pragma once
#include "../Header.h"

class TelephoneDirectory {
	struct ContactCard {
		string first;
		string last;
		string org;
		string number;

		ContactCard(string first, string last, string org, string number) :
			first(first), last(last), org(org), number(number) {}

		string to_string() {
			stringstream ss;
			ss << "{";
			ss << setw(16) << first << " " << last << " ";
			ss << setw(16) << "[" << org << "]" << ":";
			ss << setw(16) << number;
			ss << "}";
			return ss.str();
		}
	};
	class Trie {
		struct Node {
			unordered_map<char, Node*> neighbours;
			bool isEnd;
			vector<ContactCard*> contacts;
		};
		Node* root = nullptr;
	public:
		void add(ContactCard* card) {
			root = add(root, card, card->first);
			root = add(root, card, card->last);
			root = add(root, card, card->org);
			root = add(root, card, card->number);
		}

		vector<ContactCard*> search(string prefix) {
			auto* res = search(root, prefix, 0);
			if (res == nullptr) return {};
			return res->contacts;
		}
	private:
		Node* add(Node* cur, ContactCard* card, string name) {
			return add(cur, card, name, 0);
		}

		Node* add(Node* cur, ContactCard* card, string name, int index) {
			if (!cur) cur = new Node();
			cur->contacts.push_back(card);

			if (index == name.length()) {
				cur->isEnd = true;
				return cur;
			}

			char ch = tolower(name[index]);
			cur->neighbours[ch] = add(cur->neighbours[ch], card, name, index + 1);

			return cur;
		}

		Node* search(Node* cur, string prefix, int index) {
			if (!cur) return cur;
			if (index == prefix.length()) return cur;

			char ch = tolower(prefix[index]);
			return search(cur->neighbours[ch], prefix, index + 1);
		}
	};

	Trie trie;
public:
	static void test() {
		TelephoneDirectory obj;
		obj.addContact(new ContactCard("Amit", "Singh", "Microsoft", "7167803185"));
		obj.addContact(new ContactCard("Amit", "Singh", "Microsoft", "2134324"));
		obj.addContact(new ContactCard("Amit", "Singh", "Amazon", "20103"));
		obj.addContact(new ContactCard("Kapil", "Singh", "Microsoft", "7167803185"));
		obj.addContact(new ContactCard("Singh", "Ravi", "Cisco", "002384823"));
		obj.addContact(new ContactCard("Bhanu Pratap", "Singh", "LG", "9999606133"));

		while (true) {
			string prefix;
			cout << "Enter name/number to search: ";
			cin >> prefix;
			if (prefix == "N") break;
			auto res = obj.search(prefix);
			for (auto val : res) cout << val->to_string() << endl;
			cout << endl;
		}
	}

	void addContact(ContactCard* card) {
		trie.add(card);
	}

	vector<ContactCard*> search(string prefix) {
		return trie.search(prefix);
	}
};