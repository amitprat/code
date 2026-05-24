#pragma once
#include "../header.h"

/*
* There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you.
* You receive a list of non-empty words from the dictionary, where words are sorted lexicographically by the rules of
* this new language. Derive the order of letters in this language.

* For example, Given the following words in dictionary,
* [
*   "wrt",
*   "wrf",
*   "er",
*   "ett",
*   "rftt"
* ]
* The correct order is: "wertf".

* Note:
* You may assume all letters are in lowercase.
* You may assume that if a is a prefix of b, then a must appear before b in the given dictionary.
* If the order is invalid, return an empty string.
* There may be multiple valid order of letters, return the smallest in normal lexicographical order.
*
* To solve this problem, we can use topological sorting. We will first build a directed graph based on the given list of words.
* We will compare adjacent words and find the first different character to determine the order of characters.
* We will also keep track of the in-degrees of each character. After building the graph, we will perform a topological sort.
*
* Rules:
* 1. If a is a prefix of b, then a must appear before b in the given dictionary.
*    This means that if we have two words where one is a prefix of the other, the shorter word must come first in the order.
* 2. If the order is invalid, return an empty string. This means that if there is a cycle in the graph
*    (i.e., a character depends on itself), then the order is invalid and we should return an empty string.
* 3. There may be multiple valid order of letters, return the smallest in normal lexicographical order.
*    This means that if there are multiple valid topological sorts, we should return the one that is lexicographically smallest.
*.   We can achieve this by using a priority queue (min-heap) instead of a regular queue when performing the topological sort,
*.   so that we always process the character with the smallest lexicographical order first.
*/

class AlienDictionary {
   public:
    static void test() {
        AlienDictionary obj;

        vector<string> words = {"wrt", "wrf", "er", "ett", "rftt"};

        auto res = obj.alienOrder(words);

        println("Alien order: {}", res);
    }

   private:
    class Graph {
       public:
        unordered_map<char, unordered_set<char>> adjList;
        unordered_set<char> vertices;

        void addEdge(char from, char to) {
            adjList[from].insert(to);
        }

        void addVertex(char vertex) {
            vertices.insert(vertex);
        }
    };

   public:
    string alienOrder(vector<string>& words) {
        Graph graph;

        // Add all characters to the graph
        for (string& word : words) {
            for (char ch : word) {
                graph.addVertex(ch);
            }
        }

        // Find the first different character between adjacent words to determine the order.
        // Return early if we find an invalid case where a word is a prefix of the next word.
        for (int i = 0; i < words.size() - 1; i++) {
            string& w1 = words[i];
            string& w2 = words[i + 1];

            int minLength = min(w1.size(), w2.size());

            // If w1 is a prefix of w2, then w1 must come before w2 in the order. If w1 is longer than w2 and w1 starts with w2,
            // then it's an invalid case.
            if (w1.substr(0, minLength) == w2.substr(0, minLength) && w1.size() > w2.size()) {
                return "";
            }

            // Find the first different character and add an edge from w1[j] to w2[j].
            for (int j = 0; j < minLength; j++) {
                if (w1[j] != w2[j]) {
                    graph.addEdge(w1[j], w2[j]);
                    break;
                }
            }
        }

        // Perform topological sort.
        // Also keep track of any cycles in the graph. If we find a cycle, return an empty string.
        unordered_set<char> visited;
        stack<char> st;
        for (auto& vertex : graph.vertices) {
            if (!visited.contains(vertex)) {
                unordered_set<char> recStack;
                if (hasCycle(graph, vertex, visited, recStack, st)) return "";
            }
        }

        // Build the result string from the topological sort order.
        string result;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }

        return result;
    }

    bool hasCycle(Graph& graph, char u, unordered_set<char>& visited, unordered_set<char>& recStack, stack<char>& st) {
        visited.insert(u);
        recStack.insert(u);

        for (char v : graph.adjList[u]) {
            if (!visited.contains(v)) {
                if (hasCycle(graph, v, visited, recStack, st)) return true;
            } else if (recStack.contains(v)) return true;
        }

        recStack.erase(u);
        st.push(u);

        return false;
    }
};