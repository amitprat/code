#include "../header.h"

class PrintAllCombinations {
   public:
    static void test() {
        PrintAllCombinations obj;
        string str = "123";
        obj.printCombinations(str);
    }

   private:
    void printCombinations(string str) {
        unordered_map<string, list<string>> map = {
            {"1", {"A", "B", "C"}},
            {"2", {"D", "E"}},
            {"12", {"X"}},
            {"3", {"P", "Q"}}};

        vector<string> curResult;
        printCombinations(str, map, curResult);
    }
    void printCombinations(string str, unordered_map<string, list<string>>& map, vector<string>& curResult) {
        if (str.empty()) {
            cout << curResult << endl;
            return;
        }

        for (int i = 1; i <= str.size(); i++) {
            string cur = str.substr(0, i);
            string rest = str.substr(i);

            for (auto& e : map[cur]) {
                curResult.push_back(e);
                printCombinations(rest, map, curResult);
                curResult.pop_back();
            }
        }
    }
};