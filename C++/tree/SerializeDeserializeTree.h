#pragma once
#include "../Header.h"
using namespace std;

struct BinaryTreeNode
{
    int val;
    BinaryTreeNode* left, * right;
};

struct NaryTreeNode
{
    int val;
    vector<NaryTreeNode*> children;
};

class SerializeDeserializeBinaryTree
{
    vector<char> serializedTree;
public:
    static void testBinaryTree()
    {
        BinaryTreeNode* root = new BinaryTreeNode({ 1 });
        root->left = new BinaryTreeNode({ 2 });
        root->right = new BinaryTreeNode({ 3 });
        root->left->left = new BinaryTreeNode({ 4 });
        root->right->left = new BinaryTreeNode({ 5 });

        SerializeDeserializeBinaryTree obj;
        cout << "Serialized Tree:";
        obj.printTree(root);
        cout << endl;

        obj.Serialize(root, 0);
        cout << "Serialized Tree String:" << obj.str() << endl;

        auto tmp = obj.Deserialize(0);
        cout << "Deserialized Tree:";
        obj.printTree(tmp);
        cout << endl;
    }

    void Serialize(BinaryTreeNode* node, int index)
    {
        if (index >= serializedTree.size()) serializedTree.resize(index + 1);
        if (node == nullptr) {
            serializedTree[index] = '\0';
            return;
        }
        serializedTree[index] = (node->val + '0');
        Serialize(node->left, 2 * index + 1);
        Serialize(node->right, 2 * index + 2);
    }

    BinaryTreeNode* Deserialize(int index)
    {
        if (index >= serializedTree.size() || serializedTree[index] == '\0') return nullptr;

        BinaryTreeNode* tmp = new BinaryTreeNode({ serializedTree[index] - '0' });
        tmp->left = Deserialize(2 * index + 1);
        tmp->right = Deserialize(2 * index + 2);

        return tmp;
    }

    string str()
    {
        stringstream ss;
        for (auto ch : serializedTree) {
            if (ch == '\0') ss << "NULL";
            else ss << (ch - '0');
            ss << " ";
        }

        return ss.str();
    }

    void printTree(BinaryTreeNode* node) {
        if (node)
        {
            cout << node->val << " ";
            printTree(node->left);
            printTree(node->right);
        }
    }
};

class SerializeDeserializeBinarySearchTree
{
    vector<char> serializedTree;
public:
    static void testBinarySearchTree()
    {
        BinaryTreeNode* root = new BinaryTreeNode({ 3 });
        root->left = new BinaryTreeNode({ 2 });
        root->right = new BinaryTreeNode({ 5 });
        root->left->left = new BinaryTreeNode({ 1 });
        root->right->left = new BinaryTreeNode({ 4 });

        SerializeDeserializeBinarySearchTree obj;
        cout << "Serialized Tree:";
        obj.printTree(root);
        cout << endl;

        obj.Serialize(root);
        cout << "Serialized Tree String:" << obj.str() << endl;

        auto tmp = obj.Deserialize(INT_MIN, INT_MAX);
        cout << "Deserialized Tree:";
        obj.printTree(tmp);
        cout << endl;
    }

    void Serialize(BinaryTreeNode* node)
    {
        if (node == nullptr) return;
        serializedTree.push_back(node->val + '0');
        Serialize(node->left);
        Serialize(node->right);
    }

    BinaryTreeNode* Deserialize(int mn, int mx)
    {
        static int index = 0;
        if (index >= serializedTree.size()) return nullptr;
        if (serializedTree[index] - '0' <= mn || serializedTree[index] - '0' >= mx) return nullptr;

        BinaryTreeNode* tmp = new BinaryTreeNode({ serializedTree[index++] - '0' });
        tmp->left = Deserialize(mn, tmp->val);
        tmp->right = Deserialize(tmp->val, mx);

        return tmp;
    }

    string str()
    {
        stringstream ss;
        for (auto ch : serializedTree) {
            if (ch == '\0') ss << "NULL";
            else ss << (ch - '0');
            ss << " ";
        }

        return ss.str();
    }

    void printTree(BinaryTreeNode* node) {
        if (node)
        {
            printTree(node->left);
            cout << node->val << " ";
            printTree(node->right);
        }
    }
};

class SerializeDeserializeNaryTree
{
    vector<char> serializedTree;
public:
    static void testNaryTree()
    {
        NaryTreeNode* root = new NaryTreeNode({ 0 });
        for (int i = 1; i < 4; i++) {
            root->children.push_back(new NaryTreeNode({ i }));
            for (int j = i * 10; j < i * 10 + 3; j++) {
                root->children[i - 1]->children.push_back(new NaryTreeNode({ j }));
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

    void Serialize(NaryTreeNode* node)
    {
        if (node == nullptr) return;

        serializedTree.push_back(node->val + '0');
        for (auto& ch : node->children) {
            Serialize(ch);
        }
        serializedTree.push_back('\0');
    }

    NaryTreeNode* Deserialize()
    {
        static int index = 0;
        if (index >= serializedTree.size()) return nullptr;

        NaryTreeNode* tmp = new NaryTreeNode({ serializedTree[index++] - '0' });
        while (serializedTree[index] != '\0') {
            tmp->children.push_back(Deserialize());
        }
        index++;

        return tmp;
    }

    string str()
    {
        stringstream ss;
        for (auto ch : serializedTree) {
            if (ch == '\0') ss << "NULL";
            else ss << (ch - '0');
            ss << " ";
        }

        return ss.str();
    }

    void printTree(NaryTreeNode* node) {
        if (node)
        {
            cout << node->val << " ";
            for (auto& ch : node->children)
            {
                printTree(ch);
            }
        }
    }
};
