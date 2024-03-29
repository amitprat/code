#include "../header.h"
using namespace std;

class Tree {
   public:
    struct Node {
        int val;
        Node *left, *right;

        Node(int x) : val(x), left(nullptr), right(nullptr) {}
    };

   public:
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

#if 0
   private:
    // pretty print binary tree another method
    struct cell_display {
        string valstr;
        bool present;
        cell_display() : present(false) {}
        cell_display(std::string valstr) : valstr(valstr), present(true) {}
    };

    using display_rows = vector<vector<cell_display> >;

   public:
    // Dumps a representation of the tree to out
    static void prettyPrint(Node *root, std::ostream &out) {
        const int d = getHeight(root);

        // If this tree is empty, tell someone
        if (d == 0) {
            out << " <empty tree>\n";
            return;
        }

        // This tree is not empty, so get a list of node values...
        const auto rows_disp = get_row_display(root);
        // then format these into a text representation...
        auto formatted_rows = row_formatter(rows_disp);
        // then trim excess space characters from the left sides of the text...
        trim_rows_left(formatted_rows);
        // then dump the text to out.
        for (const auto &row : formatted_rows) {
            out << ' ' << row << '\n';
        }
    }

   private:
    // The text tree generation code below is all iterative, to avoid stack faults.

    // get_row_display builds a vector of vectors of cell_display structs
    // each vector of cell_display structs represents one row, starting at the root
    static display_rows get_row_display(Node *root) {
        // start off by traversing the tree to
        // build a vector of vectors of Node pointers
        vector<Node *> traversal_stack;
        vector<std::vector<Node *> > rows;
        if (!root) return display_rows();

        Node *p = root;
        const int max_depth = getHeight(root);
        rows.resize(max_depth);
        int depth = 0;
        for (;;) {
            // Max-depth Nodes are always a leaf or null
            // This special case blocks deeper traversal
            if (depth == max_depth - 1) {
                rows[depth].push_back(p);
                if (depth == 0) break;
                --depth;
                continue;
            }

            // First visit to node?  Go to left child.
            if (traversal_stack.size() == depth) {
                rows[depth].push_back(p);
                traversal_stack.push_back(p);
                if (p) p = p->left;
                ++depth;
                continue;
            }

            // Odd child count? Go to right child.
            if (rows[depth + 1].size() % 2) {
                p = traversal_stack.back();
                if (p) p = p->right;
                ++depth;
                continue;
            }

            // Time to leave if we get here

            // Exit loop if this is the root
            if (depth == 0) break;

            traversal_stack.pop_back();
            p = traversal_stack.back();
            --depth;
        }

        // Use rows of Node pointers to populate rows of cell_display structs.
        // All possible slots in the tree get a cell_display struct,
        // so if there is no actual Node at a struct's location,
        // its boolean "present" field is set to false.
        // The struct also contains a string representation of
        // its Node's value, created using a std::stringstream object.
        display_rows rows_disp;
        std::stringstream ss;
        for (const auto &row : rows) {
            rows_disp.emplace_back();
            for (Node *pn : row) {
                if (pn) {
                    ss << pn->val;
                    rows_disp.back().push_back(cell_display(ss.str()));
                    ss = std::stringstream();
                } else {
                    rows_disp.back().push_back(cell_display());
                }
            }
        }
        return rows_disp;
    }

    // row_formatter takes the vector of rows of cell_display structs
    // generated by get_row_display and formats it into a test representation
    // as a vector of strings
    static vector<string> row_formatter(const display_rows &rows_disp) {
        using s_t = string::size_type;

        // First find the maximum value string length and put it in cell_width
        s_t cell_width = 0;
        for (const auto &row_disp : rows_disp) {
            for (const auto &cd : row_disp) {
                if (cd.present && cd.valstr.length() > cell_width) {
                    cell_width = cd.valstr.length();
                }
            }
        }

        // make sure the cell_width is an odd number
        if (cell_width % 2 == 0) ++cell_width;

        // allows leaf nodes to be connected when they are
        // all with size of a single character
        if (cell_width < 3) cell_width = 3;

        // formatted_rows will hold the results
        vector<string> formatted_rows;

        // some of these counting variables are related,
        // so its should be possible to eliminate some of them.
        s_t row_count = rows_disp.size();

        // this row's element count, a power of two
        s_t row_elem_count = 1 << (row_count - 1);

        // left_pad holds the number of space charactes at the beginning of the bottom row
        s_t left_pad = 0;

        // Work from the level of maximum depth, up to the root
        // ("formatted_rows" will need to be reversed when done)
        for (s_t r = 0; r < row_count; ++r) {
            const auto &cd_row = rows_disp[row_count - r - 1];  // r reverse-indexes the row
            // "space" will be the number of rows of slashes needed to get
            // from this row to the next.  It is also used to determine other
            // text offsets.
            s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
            // "row" holds the line of text currently being assembled
            string row;
            // iterate over each element in this row
            for (s_t c = 0; c < row_elem_count; ++c) {
                // add padding, more when this is not the leftmost element
                row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
                if (cd_row[c].present) {
                    // This position corresponds to an existing Node
                    const string &valstr = cd_row[c].valstr;
                    // Try to pad the left and right sides of the value string
                    // with the same number of spaces.  If padding requires an
                    // odd number of spaces, right-sided children get the longer
                    // padding on the right side, while left-sided children
                    // get it on the left side.
                    s_t long_padding = cell_width - valstr.length();
                    s_t short_padding = long_padding / 2;
                    long_padding -= short_padding;
                    row += string(c % 2 ? short_padding : long_padding, ' ');
                    row += valstr;
                    row += string(c % 2 ? long_padding : short_padding, ' ');
                } else {
                    // This position is empty, Nodeless...
                    row += string(cell_width, ' ');
                }
            }
            // A row of spaced-apart value strings is ready, add it to the result vector
            formatted_rows.push_back(row);

            // The root has been added, so this loop is finsished
            if (row_elem_count == 1) break;

            // Add rows of forward- and back- slash characters, spaced apart
            // to "connect" two rows' Node value strings.
            // The "space" variable counts the number of rows needed here.
            s_t left_space = space + 1;
            s_t right_space = space - 1;
            for (s_t sr = 0; sr < space; ++sr) {
                string row;
                for (s_t c = 0; c < row_elem_count; ++c) {
                    if (c % 2 == 0) {
                        row += string(c ? left_space * 2 + 1 : left_space, ' ');
                        row += cd_row[c].present ? '/' : ' ';
                        row += string(right_space + 1, ' ');
                    } else {
                        row += string(right_space, ' ');
                        row += cd_row[c].present ? '\\' : ' ';
                    }
                }
                formatted_rows.push_back(row);
                ++left_space;
                --right_space;
            }
            left_pad += space + 1;
            row_elem_count /= 2;
        }

        // Reverse the result, placing the root node at the beginning (top)
        std::reverse(formatted_rows.begin(), formatted_rows.end());

        return formatted_rows;
    }

    // Trims an equal number of space characters from
    // the beginning of each string in the vector.
    // At least one string in the vector will end up beginning
    // with no space characters.
    static void trim_rows_left(vector<string> &rows) {
        if (!rows.size()) return;
        auto min_space = rows.front().length();
        for (const auto &row : rows) {
            auto i = row.find_first_not_of(' ');
            if (i == string::npos) i = row.length();
            if (i == 0) return;
            if (i < min_space) min_space = i;
        }
        for (auto &row : rows) {
            row.erase(0, min_space);
        }
    }
#endif
};
