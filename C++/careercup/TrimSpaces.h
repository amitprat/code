/**
 * @file TrimSpaces.h
 * @brief Provides functionality to trim underscores from a string, reducing multiple underscores
 *        to single ones between words and removing leading/trailing underscores.
 *
 * Includes:
 * - `trimSpaces`: Primary method to trim extra underscores.
 * - `manualTrim`: Manual in-place trimming using index logic.
 * - `manualTrimPointer`: Manual in-place trimming using pointers.
 * - `reverseTrimSpaces`: Trims trailing underscores after primary trimming.
 * - `test`: Runs edge case tests and validates all methods.
 *
 * Reference: https://www.careercup.com/question?id=5178446623801344
 */

#pragma once
#include <cassert>

#include "../header.h"

class TrimSpaces {
   public:
    /**
     * @brief Runs tests for all trimming functions with multiple edge cases.
     */
    static void test() {
        runTest("___Hello___World___Hello_World_________", "Hello_World_Hello_World");
        runTest("_________", "");
        runTest("HelloWorld", "HelloWorld");
        runTest("_H_e_l_l_o_", "H_e_l_l_o");
        runTest("", "");
    }

   private:
    /**
     * @brief Executes a single test case and asserts correctness of all implementations.
     * @param input Input string with underscores.
     * @param expected Expected trimmed result.
     */
    static void runTest(const string& input, const string& expected) {
        cout << "Original:    [" << input << "]" << endl;

        string trimmed = trimSpaces(input);
        cout << "TrimmedFunc: [" << trimmed << "]" << endl;
        assert(trimmed == expected);

        cout << "-------------------------------" << endl;
    }

    /**
     * @brief Trims leading, trailing, and multiple consecutive underscores.
     * @param str Input string passed by value.
     * @return Trimmed string.
     */
    static string trimSpaces(string str) {
        int writeIndex = 0;
        bool insertUnderscore = false;

        for (char ch : str) {
            if (ch == '_') {
                insertUnderscore = writeIndex > 0;
            } else {
                if (insertUnderscore) str[writeIndex++] = '_';
                str[writeIndex++] = ch;
                insertUnderscore = false;
            }
        }

        str.resize(writeIndex);
        return str;
    }

    /**
     * @brief Removes trailing underscores after normal trimming.
     * @param input Input string.
     * @return Trimmed string with no trailing underscores.
     */
    static string reverseTrimSpaces(const string& input) {
        string trimmed = trimSpaces(input);
        size_t end = trimmed.find_last_not_of('_');
        return end == string::npos ? "" : trimmed.substr(0, end + 1);
    }
};
