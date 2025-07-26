#pragma once
#include "../header.h"

class StringHelper {
   public:
    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);  // Create an input string stream from the original string

        while (std::getline(tokenStream, token, delimiter)) {  // Read tokens separated by the delimiter
            tokens.push_back(token);
        }
        return tokens;
    }

    static vector<string> split(const string& str, const string& delimiter) {
        vector<string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);

        while (end != string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        tokens.push_back(str.substr(start));
        return tokens;
    }

    static vector<string> splitWhitespace(const string& str) {
        vector<string> tokens;
        istringstream iss(str);
        string token;

        while (iss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // Join vector of strings with delimiter
    static string join(const vector<string>& strings, const string& delimiter) {
        if (strings.empty()) return "";

        string result = strings[0];
        for (size_t i = 1; i < strings.size(); i++) {
            result += delimiter + strings[i];
        }
        return result;
    }

    // ==================== TRIMMING ====================
    // Trim whitespace from left
    static string trimLeft(const string& str) {
        auto it = find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !isspace(ch);
        });
        return string(it, str.end());
    }

    // Trim whitespace from right
    static string trimRight(const string& str) {
        auto it = find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !isspace(ch);
        });
        return string(str.begin(), it.base());
    }

    // Trim whitespace from both ends
    static string trim(const string& str) {
        return trimLeft(trimRight(str));
    }

    // Trim specific characters from both ends
    static string trim(const string& str, const string& chars) {
        size_t start = str.find_first_not_of(chars);
        if (start == string::npos) return "";
        size_t end = str.find_last_not_of(chars);
        return str.substr(start, end - start + 1);
    }

    // ==================== CASE CONVERSION ====================
    // Convert to lowercase
    static string toLower(string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    // Convert to uppercase
    static string toUpper(string str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    // Capitalize first letter
    static string capitalize(string str) {
        if (!str.empty()) {
            str[0] = toupper(str[0]);
        }
        return str;
    }

    // Title case (capitalize first letter of each word)
    static string toTitleCase(const string& str) {
        string result = str;
        bool capitalizeNext = true;

        for (char& ch : result) {
            if (isspace(ch)) {
                capitalizeNext = true;
            } else if (capitalizeNext) {
                ch = toupper(ch);
                capitalizeNext = false;
            } else {
                ch = tolower(ch);
            }
        }
        return result;
    }

    // Toggle case
    static string toggleCase(string str) {
        for (char& ch : str) {
            if (isupper(ch)) {
                ch = tolower(ch);
            } else if (islower(ch)) {
                ch = toupper(ch);
            }
        }
        return str;
    }

    // ==================== SEARCH & REPLACE ====================
    // Check if string contains substring
    static bool contains(const string& str, const string& substr) {
        return str.find(substr) != string::npos;
    }

    // Count occurrences of substring
    static int countOccurrences(const string& str, const string& substr) {
        if (substr.empty()) return 0;

        int count = 0;
        size_t pos = 0;

        while ((pos = str.find(substr, pos)) != string::npos) {
            count++;
            pos += substr.length();
        }
        return count;
    }

    // Replace first occurrence
    static string replaceFirst(string str, const string& from, const string& to) {
        size_t pos = str.find(from);
        if (pos != string::npos) {
            str.replace(pos, from.length(), to);
        }
        return str;
    }

    // Replace all occurrences
    static string replaceAll(string str, const string& from, const string& to) {
        if (from.empty()) return str;

        size_t pos = 0;
        while ((pos = str.find(from, pos)) != string::npos) {
            str.replace(pos, from.length(), to);
            pos += to.length();
        }
        return str;
    }

    // Remove all occurrences of substring
    static string removeAll(const string& str, const string& substr) {
        return replaceAll(str, substr, "");
    }

    // ==================== PREFIX & SUFFIX ====================
    // Check if string starts with prefix
    static bool startsWith(const string& str, const string& prefix) {
        return str.size() >= prefix.size() &&
               str.compare(0, prefix.size(), prefix) == 0;
    }

    // Check if string ends with suffix
    static bool endsWith(const string& str, const string& suffix) {
        return str.size() >= suffix.size() &&
               str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }

    // Remove prefix if present
    static string removePrefix(const string& str, const string& prefix) {
        if (startsWith(str, prefix)) {
            return str.substr(prefix.length());
        }
        return str;
    }

    // Remove suffix if present
    static string removeSuffix(const string& str, const string& suffix) {
        if (endsWith(str, suffix)) {
            return str.substr(0, str.length() - suffix.length());
        }
        return str;
    }

    // ==================== PADDING ====================
    // Pad left with character
    static string padLeft(const string& str, size_t width, char padChar = ' ') {
        if (str.length() >= width) return str;
        return string(width - str.length(), padChar) + str;
    }

    // Pad right with character
    static string padRight(const string& str, size_t width, char padChar = ' ') {
        if (str.length() >= width) return str;
        return str + string(width - str.length(), padChar);
    }

    // Center string with padding
    static string center(const string& str, size_t width, char padChar = ' ') {
        if (str.length() >= width) return str;

        size_t totalPad = width - str.length();
        size_t leftPad = totalPad / 2;
        size_t rightPad = totalPad - leftPad;

        return string(leftPad, padChar) + str + string(rightPad, padChar);
    }

    // ==================== VALIDATION ====================
    // Check if string is numeric
    static bool isNumeric(const string& str) {
        if (str.empty()) return false;

        size_t start = 0;
        if (str[0] == '-' || str[0] == '+') start = 1;
        if (start >= str.length()) return false;

        bool hasDecimal = false;
        for (size_t i = start; i < str.length(); i++) {
            if (str[i] == '.') {
                if (hasDecimal) return false;
                hasDecimal = true;
            } else if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    // Check if string is alphabetic
    static bool isAlpha(const string& str) {
        return !str.empty() && all_of(str.begin(), str.end(), ::isalpha);
    }

    // Check if string is alphanumeric
    static bool isAlphaNumeric(const string& str) {
        return !str.empty() && all_of(str.begin(), str.end(), ::isalnum);
    }

    // Check if string is all whitespace
    static bool isWhitespace(const string& str) {
        return all_of(str.begin(), str.end(), ::isspace);
    }

    // Check if string is empty or whitespace
    static bool isBlank(const string& str) {
        return str.empty() || isWhitespace(str);
    }

    // ==================== REVERSE & REPEAT ====================
    // Reverse string
    static string reverse(string str) {
        std::reverse(str.begin(), str.end());
        return str;
    }

    // Repeat string n times
    static string repeat(const string& str, int n) {
        if (n <= 0) return "";

        string result;
        result.reserve(str.length() * n);

        for (int i = 0; i < n; i++) {
            result += str;
        }
        return result;
    }

    // ==================== SUBSTRING OPERATIONS ====================
    // Get substring between two delimiters
    static string substringBetween(const string& str, const string& start, const string& end) {
        size_t startPos = str.find(start);
        if (startPos == string::npos) return "";

        startPos += start.length();
        size_t endPos = str.find(end, startPos);

        if (endPos == string::npos) return "";
        return str.substr(startPos, endPos - startPos);
    }

    // Get all substrings between delimiters
    static vector<string> allSubstringsBetween(const string& str, const string& start, const string& end) {
        vector<string> results;
        size_t pos = 0;

        while (pos < str.length()) {
            size_t startPos = str.find(start, pos);
            if (startPos == string::npos) break;

            startPos += start.length();
            size_t endPos = str.find(end, startPos);
            if (endPos == string::npos) break;

            results.push_back(str.substr(startPos, endPos - startPos));
            pos = endPos + end.length();
        }
        return results;
    }

    // ==================== COMPARISON ====================
    // Case-insensitive comparison
    static bool equalsIgnoreCase(const string& str1, const string& str2) {
        return toLower(str1) == toLower(str2);
    }

    // Check if strings are equal (wrapper for clarity)
    static bool equals(const string& str1, const string& str2) {
        return str1 == str2;
    }

    // ==================== CHARACTER OPERATIONS ====================
    // Count specific character
    static int countChar(const string& str, char ch) {
        return count(str.begin(), str.end(), ch);
    }

    // Remove all whitespace
    static string removeWhitespace(const string& str) {
        string result;
        copy_if(str.begin(), str.end(), back_inserter(result), [](unsigned char ch) {
            return !isspace(ch);
        });
        return result;
    }

    // Keep only alphanumeric characters
    static string keepAlphaNumeric(const string& str) {
        string result;
        copy_if(str.begin(), str.end(), back_inserter(result), ::isalnum);
        return result;
    }

    // Remove duplicates (keep first occurrence)
    static string removeDuplicates(const string& str) {
        string result;
        unordered_set<char> seen;

        for (char ch : str) {
            if (seen.find(ch) == seen.end()) {
                result += ch;
                seen.insert(ch);
            }
        }
        return result;
    }

    // ==================== ENCODING & ESCAPING ====================
    // Escape special characters for regex
    static string escapeRegex(const string& str) {
        static const regex specialChars{R"([-[\]{}()*+?.,\^$|#\s])"};
        return regex_replace(str, specialChars, R"(\$&)");
    }

    // URL encode (basic implementation)
    static string urlEncode(const string& str) {
        ostringstream escaped;
        escaped.fill('0');
        escaped << hex;

        for (char ch : str) {
            if (isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
                escaped << ch;
            } else {
                escaped << uppercase;
                escaped << '%' << setw(2) << int((unsigned char)ch);
                escaped << nouppercase;
            }
        }
        return escaped.str();
    }

    // ==================== WORD OPERATIONS ====================
    // Count words (separated by whitespace)
    static int wordCount(const string& str) {
        return splitWhitespace(str).size();
    }

    // Get nth word (0-indexed)
    static string getNthWord(const string& str, int n) {
        auto words = splitWhitespace(str);
        if (n >= 0 && n < words.size()) {
            return words[n];
        }
        return "";
    }

    // ==================== STRING DISTANCE ====================
    // Levenshtein distance (edit distance)
    static int levenshteinDistance(const string& str1, const string& str2) {
        int m = str1.length();
        int n = str2.length();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                }
            }
        }
        return dp[m][n];
    }

    // ==================== FORMAT & CONVERSION ====================
    // Convert to camelCase
    static string toCamelCase(const string& str) {
        auto words = splitWhitespace(str);
        if (words.empty()) return "";

        string result = toLower(words[0]);
        for (size_t i = 1; i < words.size(); i++) {
            result += capitalize(toLower(words[i]));
        }
        return result;
    }

    // Convert to snake_case
    static string toSnakeCase(const string& str) {
        auto words = splitWhitespace(str);
        for (auto& word : words) {
            word = toLower(word);
        }
        return join(words, "_");
    }

    // Convert to kebab-case
    static string toKebabCase(const string& str) {
        auto words = splitWhitespace(str);
        for (auto& word : words) {
            word = toLower(word);
        }
        return join(words, "-");
    }

    // Truncate string to length with ellipsis
    static string truncate(const string& str, size_t maxLength, const string& suffix = "...") {
        if (str.length() <= maxLength) return str;

        if (maxLength <= suffix.length()) {
            return str.substr(0, maxLength);
        }
        return str.substr(0, maxLength - suffix.length()) + suffix;
    }

    // Abbreviate to show start and end with ellipsis in middle
    static string abbreviate(const string& str, size_t maxLength) {
        if (str.length() <= maxLength) return str;
        if (maxLength < 3) return str.substr(0, maxLength);

        size_t halfLength = (maxLength - 3) / 2;
        return str.substr(0, halfLength) + "..." + str.substr(str.length() - halfLength);
    }

    // ==================== METHOD 1: SORTED STRING AS KEY ====================
    // Time: O(n log n), Space: O(n)
    // Most common and reliable method
    static string getSortedKey(const string& str) {
        string key = str;
        sort(key.begin(), key.end());
        return key;
    }

    // ==================== METHOD 2: CHARACTER FREQUENCY MAP ====================
    // Time: O(n), Space: O(1) - fixed 26 letters
    // More efficient for grouping anagrams
    static string getFrequencyKey(const string& str) {
        vector<int> count(26, 0);

        for (char ch : str) {
            if (isalpha(ch)) {
                count[tolower(ch) - 'a']++;
            }
        }

        // Build key as "a2b1c3..." format
        string key;
        for (int i = 0; i < 26; i++) {
            if (count[i] > 0) {
                key += char('a' + i);
                key += to_string(count[i]);
            }
        }
        return key;
    }

    // ==================== METHOD 3: PRIME NUMBER HASH ====================
    // Time: O(n), Space: O(1)
    // Unique product for each anagram group (can overflow for long strings)
    static unsigned long long getPrimeHash(const string& str) {
        // Prime numbers for a-z
        static const int primes[26] = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97, 101};

        unsigned long long hash = 1;
        for (char ch : str) {
            if (isalpha(ch)) {
                hash *= primes[tolower(ch) - 'a'];
            }
        }
        return hash;
    }

    // ==================== METHOD 4: CHARACTER SUM (WEAK) ====================
    // Time: O(n), Space: O(1)
    // Fast but has collisions (e.g., "abc" and "bca" have same sum, but so do "aac" and "bb")
    static int getCharSum(const string& str) {
        int sum = 0;
        for (char ch : str) {
            if (isalpha(ch)) {
                sum += tolower(ch) - 'a';
            }
        }
        return sum;
    }

    // ==================== METHOD 5: XOR HASH (WEAK) ====================
    // Time: O(n), Space: O(1)
    // Very fast but many collisions
    static int getXORHash(const string& str) {
        int hash = 0;
        for (char ch : str) {
            if (isalpha(ch)) {
                hash ^= tolower(ch);
            }
        }
        return hash;
    }

    // ==================== METHOD 6: POLYNOMIAL HASH ====================
    // Time: O(n), Space: O(1)
    // Better distribution than sum, but can still have collisions
    static unsigned long long getPolynomialHash(const string& str) {
        const unsigned long long BASE = 31;
        const unsigned long long MOD = 1e9 + 7;

        vector<int> count(26, 0);
        for (char ch : str) {
            if (isalpha(ch)) {
                count[tolower(ch) - 'a']++;
            }
        }

        unsigned long long hash = 0;
        unsigned long long power = 1;

        for (int i = 0; i < 26; i++) {
            hash = (hash + (count[i] * power) % MOD) % MOD;
            power = (power * BASE) % MOD;
        }
        return hash;
    }

    // ==================== ANAGRAM CHECKING METHODS ====================

    // Check if two strings are anagrams using sorted comparison
    static bool areAnagrams(const string& str1, const string& str2) {
        return getSortedKey(str1) == getSortedKey(str2);
    }

    // Check if two strings are anagrams using frequency count
    static bool areAnagramsFrequency(const string& str1, const string& str2) {
        vector<int> count(26, 0);

        for (char ch : str1) {
            if (isalpha(ch)) {
                count[tolower(ch) - 'a']++;
            }
        }

        for (char ch : str2) {
            if (isalpha(ch)) {
                count[tolower(ch) - 'a']--;
            }
        }

        return all_of(count.begin(), count.end(), [](int c) { return c == 0; });
    }

    // ==================== GROUP ANAGRAMS ====================

    // Group anagrams using sorted key
    static vector<vector<string>> groupAnagramsSorted(const vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& str : strs) {
            string key = getSortedKey(str);
            groups[key].push_back(str);
        }

        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        return result;
    }

    // Group anagrams using frequency key (more efficient)
    static vector<vector<string>> groupAnagramsFrequency(const vector<string>& strs) {
        unordered_map<string, vector<string>> groups;

        for (const string& str : strs) {
            string key = getFrequencyKey(str);
            groups[key].push_back(str);
        }

        vector<vector<string>> result;
        for (auto& [key, group] : groups) {
            result.push_back(group);
        }
        return result;
    }

    // ==================== FIND ALL ANAGRAMS IN STRING ====================

    // Find all anagram occurrences of pattern in text
    static vector<int> findAnagrams(const string& text, const string& pattern) {
        vector<int> result;
        if (text.length() < pattern.length()) return result;

        vector<int> patternCount(26, 0);
        vector<int> windowCount(26, 0);

        // Count pattern characters
        for (char ch : pattern) {
            patternCount[ch - 'a']++;
        }

        int windowSize = pattern.length();

        // Initialize first window
        for (int i = 0; i < windowSize; i++) {
            windowCount[text[i] - 'a']++;
        }

        // Check first window
        if (patternCount == windowCount) {
            result.push_back(0);
        }

        // Slide window
        for (int i = windowSize; i < text.length(); i++) {
            // Add new character
            windowCount[text[i] - 'a']++;
            // Remove old character
            windowCount[text[i - windowSize] - 'a']--;

            if (patternCount == windowCount) {
                result.push_back(i - windowSize + 1);
            }
        }

        return result;
    }
};