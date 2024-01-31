#include "../header.h"

/*
https://www.careercup.com/question?id=6051601991073792

Find minimum distance between two words (order preserved) in a big string.
For e.g 1. "hello how are you" - distance between "hello" and "you" is 3.
e.g 2. "hello how are hello you" - distance is 1
e.g 3. "you are hello" - distance is -1. Order of "hello" and "you" should be preserved.
e.g 4. "hello how are hello" - distance is -1 since "you" didnt occur even once.
*/
class MinimumDistanceBetweenWordsInSentence {
   public:
    static void test() {
        MinimumDistanceBetweenWordsInSentence obj;
        vector<vector<string>> inputs = {
            {"hello", "how", "are", "hello", "you"}, {"hello", "how", "are", "you"}};

        string word1 = "hello";
        string word2 = "you";

        for (const auto& input : inputs) {
            int distance = obj.minimum_distance(input, word1, word2);
            cout << format("Minimum distance between words={} and {} is {}", word1, word2, distance) << endl;
        }
    }

   public:
    int minimum_distance(const vector<string>& input, const string& word1, const string& word2) {
        int word1_pos = -1;
        int word2_pos = -1;
        int min_distance = INT_MAX;
        int i = 0;

        for (auto& word : input) {
            if (word == word1) word1_pos = i;
            if (word == word2) word2_pos = i;

            if (word1_pos != -1 && word2_pos != -1) {
                min_distance = min(min_distance, abs(word1_pos - word2_pos));
            }

            i++;
        }

        return min_distance;
    }
};