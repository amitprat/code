#pragma once
#include "../header.h"

class FunctionTime {
public:
    class Node {
    public:
        string label;
        int startTime = 0, endTime = 0;
        Node* parent;
        vector<Node*> nodes;

        Node(string label, string status, int time, Node* parent) {
            this->label = label;
            if (status == "Start") startTime = time;
            else endTime = time;
            this->parent = parent;
        }

        string to_string() {
            string str;
            str += "{";
            str += label + ", ";
            str += std::to_string(startTime) + ", ";
            str += std::to_string(endTime) + ", ";
            str += "}";
            return str;
        }
    };

    Node* root = nullptr;
    Node* cur = nullptr;

    static void test() {
        FunctionTime obj;
        vector<vector<string>> input = {
            {"func1","Start","0"},
                {"func11","Start","0"},
                {"func11","End","10"},
                {"func12","Start","20"},
                {"func12","End","50"},
                {"func13","Start","50"},
                    {"func131","Start","55"},
                        {"func1311","Start","60"},
                        {"func1311","End","70"},
                    {"func131","End","75"},
                    {"func132","Start","80"},
                        {"func1321","Start","80"},
                        {"func1321","End","85"},
                    {"func132","End","90"},
                {"func13","End","100"},
                {"func14","Start","100"},
                {"func14","End","150"},
                {"func15","Start","180"},
                {"func15","End","200"},
            {"func1","End","200"}
        };
        for (auto i : input) {
            obj.add(i);
        }
        obj.print(obj.getRoot());
        cout << endl;
        cout << "[Func1]Excl Time = " << obj.getExclTime("func1") << endl;
        cout << "[Func1]Incl Time = " << obj.getInclTime("func1") << endl;

        cout << "\t[Func11]Excl Time = " << obj.getExclTime("func11") << endl;
        cout << "\t[Func11]Incl Time = " << obj.getInclTime("func11") << endl;

        cout << "\t[Func12]Excl Time = " << obj.getExclTime("func12") << endl;
        cout << "\t[Func12]Incl Time = " << obj.getInclTime("func12") << endl;

        cout << "\t[Func13]Excl Time = " << obj.getExclTime("func13") << endl;
        cout << "\t[Func13]Incl Time = " << obj.getInclTime("func13") << endl;
        cout << "\t\t[Func131]Excl Time = " << obj.getExclTime("func131") << endl;
        cout << "\t\t[Func131]Incl Time = " << obj.getInclTime("func131") << endl;
        cout << "\t\t\t[Func1311]Excl Time = " << obj.getExclTime("func1311") << endl;
        cout << "\t\t\t[Func1311]Incl Time = " << obj.getInclTime("func1311") << endl;
        cout << "\t\t[Func132]Excl Time = " << obj.getExclTime("func132") << endl;
        cout << "\t\t[Func132]Incl Time = " << obj.getInclTime("func132") << endl;
        cout << "\t\t\t[Func1312]Excl Time = " << obj.getExclTime("func1321") << endl;
        cout << "\t\t\t[Func1312]Incl Time = " << obj.getInclTime("func1321") << endl;

        cout << "\t[Func14]Excl Time = " << obj.getExclTime("func14") << endl;
        cout << "\t[Func14]Incl Time = " << obj.getInclTime("func14") << endl;

        cout << "\t[Func15]Excl Time = " << obj.getExclTime("func15") << endl;
        cout << "\t[Func15]Incl Time = " << obj.getInclTime("func15") << endl;
    }

    void add(vector<string> input) {
        Node* n = new Node(input[0], input[1], stoi(input[2]), cur);
        if (cur == nullptr) {
            root = cur = n;
            return;
        }
        if (input[1] == "Start") {
            cur->nodes.push_back(n);
            cur = n;
        }
        else {
            cur->endTime = stoi(input[2]);
            cur = cur->parent;
        }
    }

    int getInclTime(string funcName) {
        Node* n = getNode(root, funcName);
        return n->endTime - n->startTime;
    }

    int getExclTime(string funcName) {
        Node* n = getNode(root, funcName);
        int excl = n->endTime - n->startTime;
        for (auto* child : n->nodes) {
            excl -= child->endTime - child->startTime;
        }
        return excl;
    }
    void print(Node* curNode) {
        if (curNode == nullptr) return;
        cout << curNode->to_string() << " ";
        for (auto child : curNode->nodes) {
            print(child);
        }
    }

    Node* getRoot() {
        return root;
    }
private:
    Node* getNode(Node* curNode, string label) {
        if (curNode == nullptr) return curNode;
        if (curNode->label == label) return curNode;
        for (auto* child : curNode->nodes) {
            Node* t = getNode(child, label);
            if (t != nullptr) return t;
        }
        return nullptr;
    }
};