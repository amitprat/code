using namespace std;
#include "../header.h"

class Solution {
   public:
    bool isNumber(string s) {
        bool numSeen = false, expSeen = false, dotSeen = false, signSeen = false;

        int i = 0;
        for (auto& ch : s) {
            if (ch == '-' || ch == '+') {
                if (signSeen || numSeen || dotSeen) return false;
                signSeen = true;
            } else if (isdigit(ch)) {
                numSeen = true;
            } else if (ch == '.') {
                if (dotSeen || expSeen) return false;
                dotSeen = true;
            } else if (tolower(ch) == 'e') {
                if (!numSeen || expSeen) return false;
                expSeen = true;
                numSeen = false;
                signSeen = false;
                dotSeen = false;
            } else {
                return false;
            }
        }

        return numSeen;
    }
};