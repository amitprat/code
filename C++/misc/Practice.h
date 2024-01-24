#pragma once
#include "../header.h"

class LRUCache {
private:
    vector<pair<string, string>> backendStore;
    list<pair<string, string>> dll;
    unordered_map<string, list<pair<string, string>>::iterator> map;
    int sz = 0;
    int capacity = 0;

public:
    LRUCache(int capacity) : capacity(capacity) {}
    void put(string key, string val) {
        cout << "Push to backend store" << endl;
        for (auto& e : backendStore) {
            if (e.first == key) {
                e.second = val;
                return;
            }
        }
        backendStore.push_back({ key, val });
    }

    string get(string key) {
        string val;
        if (exists(key)) {
            cout << "Key exists in cache" << endl;
            auto iter = map[key];
            val = iter->second;
            moveToFront(iter);
        }
        else {
            cout << "Read from backend store" << endl;
            if (!existsInBackendStore(key, val)) {
                throw exception("Key not found");
            }
            if (isFull()) {
                cout << "Cache is full, erase last element" << endl;
                removeRearElement();
            }
            cout << "Insert element in front of cache" << endl;
            insertInFront(key, val);
        }
        return val;
    }
    int size() { return sz; }
    string to_string() {
        stringstream ss;
        ss << "{";
        for (auto& iter : dll) {
            ss << "(" << iter.first << "," << iter.second << ")";
            ss << ", ";
        }
        ss << "}";
        return ss.str();
    }

private:
    bool exists(string key) {
        return map.find(key) != map.end();
    }
    bool isFull() {
        return sz >= capacity;
    }

    void update(string key, string val) {
        auto iter = map[key];
        iter->second = val;
        moveToFront(iter);
    }
    void removeRearElement() {
        auto iter = dll.back();
        map.erase(iter.first);
        dll.pop_back();
        sz--;
    }
    void insertInFront(string key, string val) {
        dll.push_front({ key, val });
        map[key] = dll.begin();
        sz++;
    }
    void moveToFront(list<pair<string, string>>::iterator iter) {
        dll.erase(iter);
        dll.push_front(*iter);
    }
    bool existsInBackendStore(string key, string& val) {
        for (auto& e : backendStore) {
            if (e.first == key) {
                val = e.second;
                return true;
            }
        }
        return false;
    }
};

class LRUCacheTest {
public:
    static void test() {
        try {
            LRUCache cache(4);
            cache.put("1", "one");
            cache.put("2", "two");
            cache.put("3", "three");
            cache.put("4", "four");
            cache.put("5", "five");
            cache.put("4", "IV");
            cache.put("5", "V");
            cout << cache.get("1") << endl;
            cout << cache.get("2") << endl;
            cout << cache.get("3") << endl;
            cout << cache.get("4") << endl;
            cout << cache.get("5") << endl;
            cout << cache.get("1") << endl;
            cout << cache.get("2") << endl;
            cout << cache.get("3") << endl;
            cout << "Current state of cache:" << cache.to_string() << endl;
            cout << cache.get("4") << endl;
            cout << cache.get("5") << endl;
            cout << cache.get("6") << endl;
        }
        catch (exception e) {
            cout << "Error: " << e.what() << endl;
        }
    }
};

class Calculator {
public:
    int calculate(string infix) {
        string token;
        int start = 0;
        stack<int> val_stack;
        stack<string> ops_stack;

        while (!(token = next(infix, start)).empty()) {
            if (isOperator(token[0])) {
                evaluate(token, ops_stack, val_stack);
                ops_stack.push(token);
            }
            else {
                val_stack.push(stoi(token));
            }
        }

        while (!ops_stack.empty()) {
            val_stack.push(evaluate(ops_stack, val_stack));
        }

        return val_stack.top();
    }

    string next(string infix, int& index) {
        if (index >= infix.length()) return "";
        string next;
        if (isOperator(infix[index])) {
            next.push_back(infix[index++]);
        }
        else {
            int cur = 0;
            while (index < infix.length() && isNum(infix[index])) {
                cur = cur * 10 + to_int(infix[index++]);
            }
            next = std::to_string(cur);
        }
        return next;
    }

    bool isOperator(char cur) {
        return cur == '+' || cur == '-' || cur == '*' || cur == '/';
    }

    bool isNum(char ch) {
        return ch >= '0' && ch <= '9';
    }

    int to_int(char ch) {
        return ch - '0';
    }

    bool isEndToken(string cur) {
        return cur[0] == ')';
    }
    int prec(string cur) {
        if (cur == "+" || cur == "-") return 1;
        if (cur == "*" || cur == "/") return 2;
        return 0;
    }
    void evaluate(string op, stack<string>& ops_stack, stack<int>& val_stack)
    {
        if (isEndToken(op)) {
            while (!startToken(ops_stack.top())) {
                val_stack.push(evaluate(ops_stack, val_stack));
            }
            ops_stack.pop();
        }

        while (!ops_stack.empty() && prec(ops_stack.top()) >= prec(op)) {
            val_stack.push(evaluate(ops_stack, val_stack));
        }
    }

    bool startToken(string ch) {
        return ch[0] == '(';
    }

    int evaluate(stack<string>& ops_stack, stack<int>& val_stack) {
        auto curToken = ops_stack.top();
        ops_stack.pop();
        int second = val_stack.top(); val_stack.pop();
        int first = val_stack.top(); val_stack.pop();
        switch (curToken[0]) {
            case '+':
                return first + second;
                break;
            case '-':
                return first - second;
                break;
            case '*':
                return first * second;
                break;
            case '/':
                return first / second;
                break;
        }
    }
};

class CalculatorTest {
public:
    static void test() {
        string infix = "2-6-7*8/2+5";
        Calculator obj;
        cout << "Result: " << obj.calculate(infix) << endl;
    }
};