#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../header.h"
using namespace std;

class SerializeDeserializeNaryTree {
   private:
    struct NaryTreeNode {
        int val;
        vector<NaryTreeNode*> children;
        NaryTreeNode(int v) : val(v) {}
    };

    vector<string> serializedTree;

   public:
    static void testNaryTree() {
        NaryTreeNode* root = new NaryTreeNode(0);
        for (int i = 1; i < 4; i++) {
            NaryTreeNode* child = new NaryTreeNode(i);
            root->children.push_back(child);
            for (int j = i * 10; j < i * 10 + 3; j++) {
                child->children.push_back(new NaryTreeNode(j));
            }
        }

        SerializeDeserializeNaryTree obj;
        cout << "Original Tree: ";
        obj.printTree(root);
        cout << endl;

        obj.serialize(root);
        cout << "Serialized Tree: " << obj.str() << endl;

        int index = 0;
        NaryTreeNode* deserializedRoot = obj.deserialize(index);
        cout << "Deserialized Tree: ";
        obj.printTree(deserializedRoot);
        cout << endl;
    }

    void serialize(NaryTreeNode* node) {
        if (!node) return;

        serializedTree.push_back(to_string(node->val));
        for (auto& ch : node->children) {
            serialize(ch);
        }
        serializedTree.push_back("#");  // marker for end of children
    }

    NaryTreeNode* deserialize(int& index) {
        if (index >= serializedTree.size() || serializedTree[index] == "#") {
            index++;
            return nullptr;
        }

        NaryTreeNode* node = new NaryTreeNode(stoi(serializedTree[index++]));
        while (index < serializedTree.size() && serializedTree[index] != "#") {
            NaryTreeNode* child = deserialize(index);
            if (child) node->children.push_back(child);
        }
        index++;  // skip the '#' marker

        return node;
    }

    string str() {
        stringstream ss;
        for (auto& s : serializedTree) {
            ss << s << " ";
        }
        return ss.str();
    }

    void printTree(NaryTreeNode* node) {
        if (!node) return;
        cout << node->val << " ";
        for (auto& ch : node->children) {
            printTree(ch);
        }
    }
};