#include "../header.h"
using namespace std;

class Tree {
   public:
    struct Node {
        int val;
        Node *left, *right;

        Node(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    static void prettyPrintTree(Node *root, std::ostream &out) {
        if (root == nullptr)
            return;

        int tree_height = getHeight(root);
        int width = pow(2, tree_height - 1) * 4 - 3;

        queue<Node *> q;
        q.push(root);

        int level = 1;
        int nodes_to_print = 1;
        int level_width = width;

        while (!q.empty()) {
            if (nodes_to_print == 0)
                break;

            int nodes_in_current_level = min(nodes_to_print, (int)q.size());
            int side_padding = level_width / (nodes_in_current_level * 2);
            int spacing = level_width / (nodes_in_current_level + 1);

            printSpaces(side_padding, out);

            vector<Node *> level_nodes;
            while (nodes_in_current_level > 0) {
                Node *node = q.front();
                q.pop();

                if (node != nullptr) {
                    out << fixedWidthNumber(node->val, 3);
                    level_nodes.push_back(node->left);
                    level_nodes.push_back(node->right);
                } else {
                    out << "   ";
                    level_nodes.push_back(nullptr);
                    level_nodes.push_back(nullptr);
                }

                printSpaces(spacing, out);
                nodes_in_current_level--;
            }

            out << "\n";
            level_width /= 2;

            for (auto node : level_nodes) {
                q.push(node);
                if (node != nullptr)
                    nodes_to_print++;
            }

            level++;
        }
    }

   private:
    // Helper function to get the height of the tree
    static int getHeight(Node *root) {
        if (root == nullptr)
            return 0;

        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

    // Helper function to convert integer to string
    static string intToString(int value) {
        if (value == 0)
            return "0";

        string result = "";
        bool is_negative = false;
        if (value < 0) {
            is_negative = true;
            value = -value;
        }
        while (value > 0) {
            result = char('0' + value % 10) + result;
            value /= 10;
        }
        if (is_negative)
            result = '-' + result;
        return result;
    }

    // Helper function to convert a number to a fixed-width string
    static string fixedWidthNumber(int num, int width) {
        string s = intToString(num);
        int diff = width - s.length();
        if (diff > 0)
            s = string(diff, ' ') + s;

        return s;
    }

    // Helper function to print spaces
    static void printSpaces(int count, ostream &out) {
        for (int i = 0; i < count; i++)
            out << " ";
    }
};
