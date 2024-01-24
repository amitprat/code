#pragma once
#include "../Header.h"

class Trie
{
private:
	class Node
	{
	public:
		bool end;
		unordered_map<char, Node*> children;
		Node(bool end = false) : end(end) {}
	};
	Node* root = nullptr;

public:
	void insert(string str)
	{
		root = insert(root, str, 0);
	}

	void remove(string str)
	{
		remove(root, str, 0);
	}

	bool contains(string str)
	{
		return contains(root, str, 0);
	}

	vector<string> traverse()
	{
		vector<string> result;
		traverse(root, "", result);

		return result;
	}

	void print()
	{
		vector<string> result;
		traverse(root, "", result);

		cout << to_string(result) << endl;
	}

	vector<string> prefixes(string str)
	{
		vector<string> result;
		prefixes(root, str, 0, result);
		return result;
	}

	vector<string> suffixes(string str)
	{
		vector<string> result;
		suffixes(root, str, 0, result);
		return result;
	}

	static void test()
	{
		Trie trie;
		auto insertLog = [&trie](string item)
		{
			cout << "Inserting: " << item << endl;
			trie.insert(item);
		};
		auto removeLog = [&trie](string item)
		{
			cout << "Deleting: " << item << endl;
			trie.remove(item);
		};
		auto traverseLog = [&trie]()
		{
			auto res = trie.traverse();
			cout << "Traversing Trie: " << to_string(res) << endl;
		};
		auto containsLog = [&trie](string str)
		{
			cout << "Does contains (" << str << ") = " << to_string(trie.contains(str)) << endl;
		};
		auto prefixesLog = [&trie](string str)
		{
			auto prefixes = trie.prefixes(str);
			cout << format("Valid prefixes for word '{}' are {}", str, to_string(prefixes)) << endl;
		};
		auto suffixesLog = [&trie](string str)
		{
			auto suffixes = trie.suffixes(str);
			cout << format("Valid suffixes for word '{}' are {}", str, to_string(suffixes)) << endl;
		};

		insertLog("I");
		insertLog("Am");
		insertLog("Amit");

		traverseLog();
		containsLog("I");
		containsLog("i");
		containsLog("am");
		containsLog("Am");
		containsLog("Amit");
		containsLog("IAmAmit");

		prefixesLog("A");
		prefixesLog("Am");
		prefixesLog("Amit");
		prefixesLog("AmitPratap");
		prefixesLog("AmitSingh");
		prefixesLog("AmitPratapSingh");

		suffixesLog("A");
		suffixesLog("Am");
		suffixesLog("Amit");
		suffixesLog("AmitPratap");
		suffixesLog("AmitSingh");
		suffixesLog("AmitPratapSingh");

		removeLog("Am");
		traverseLog();
		containsLog("I");
		containsLog("i");
		containsLog("am");
		containsLog("Am");
		containsLog("Amit");
		containsLog("IAmAmit");

		insertLog("Am");
		removeLog("Amit");
		traverseLog();
		containsLog("I");
		containsLog("i");
		containsLog("am");
		containsLog("Am");
		containsLog("Amit");
		containsLog("IAmAmit");

		suffixesLog("A");
		suffixesLog("Am");
		suffixesLog("Amit");
		suffixesLog("AmitPratap");
		suffixesLog("AmitSingh");
		suffixesLog("AmitPratapSingh");
	}

private:
	Node* insert(Node* cur, string str, int l)
	{
		if (cur == nullptr) cur = new Node();
		if (l == str.length())
		{
			cur->end = true;
			return cur;
		}

		cur->children[str[l]] = insert(cur->children[str[l]], str, l + 1);
		return cur;
	}

	bool remove(Node*& cur, string str, int l)
	{
		if (cur == nullptr) return false;
		if (l == str.length())
		{
			cur->end = false;
			return isLeaf(cur);
		}

		if (remove(cur->children[str[l]], str, l + 1))
		{
			delete cur->children[str[l]];
			cur->children.erase(str[l]);
			return isLeaf(cur);
		}

		return false;
	}

	bool contains(Node* cur, string str, int l)
	{
		if (cur == nullptr) return false;
		if (l == str.length()) return cur->end;

		return contains(cur->children[str[l]], str, l + 1);
	}

	void traverse(Node* cur, string prefix, vector<string>& result)
	{
		if (!cur) return;

		if (cur->end)
		{
			result.push_back(prefix);
		}

		for (auto child : cur->children)
		{
			traverse(child.second, prefix + child.first, result);
		}
	}

	void prefixes(Node* cur, string str, int index, vector<string>& result)
	{
		if (!cur) return;
		if (cur->end) result.push_back(str.substr(0, index));
		if (index == str.length()) return;

		prefixes(cur->children[str[index]], str, index + 1, result);
	}

	void suffixes(Node* cur, string str, int index, vector<string>& result)
	{
		if (!cur) return;
		if (index == str.length()) {
			traverse(cur, str, result);
		}

		suffixes(cur->children[str[index]], str, index + 1, result);
	}

	bool isLeaf(Node* cur)
	{
		return cur->end && cur->children.empty();
	}
};