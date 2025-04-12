#pragma once
#include "../header.h"
using namespace std;

class SerializeDeserializeNaryTree {
   private:
    struct NaryTreeNode {
        int val;
        vector<NaryTreeNode*> children;
    };

    vector<char> serializedTree;

   public:
    static void testNaryTree() {
        NaryTreeNode* root = new NaryTreeNode({0});
        for (int i = 1; i < 4; i++) {
            root->children.push_back(new NaryTreeNode({i}));
            for (int j = i * 10; j < i * 10 + 3; j++) {
                root->children[i - 1]->children.push_back(new NaryTreeNode({j}));
            }
        }

        SerializeDeserializeNaryTree obj;
        cout << "Serialized Tree:";
        obj.printTree(root);
        cout << endl;

        obj.Serialize(root);
        cout << "Serialized Tree String:" << obj.str() << endl;

        auto tmp = obj.Deserialize();
        cout << "Deserialized Tree:";
        obj.printTree(tmp);
        cout << endl;
    }

    void Serialize(NaryTreeNode* node) {
        if (node == nullptr) return;

        serializedTree.push_back(node->val + '0');
        for (auto& ch : node->children) {
            Serialize(ch);
        }
        serializedTree.push_back('\0');
    }

    NaryTreeNode* Deserialize() {
        static int index = 0;
        if (index >= serializedTree.size()) return nullptr;

        NaryTreeNode* tmp = new NaryTreeNode({serializedTree[index++] - '0'});
        while (serializedTree[index] != '\0') {
            tmp->children.push_back(Deserialize());
        }
        index++;

        return tmp;
    }

    string str() {
        stringstream ss;
        for (auto ch : serializedTree) {
            if (ch == '\0')
                ss << "NULL";
            else
                ss << (ch - '0');
            ss << " ";
        }

        return ss.str();
    }

    void printTree(NaryTreeNode* node) {
        if (node) {
            cout << node->val << " ";
            for (auto& ch : node->children) {
                printTree(ch);
            }
        }
    }
};
