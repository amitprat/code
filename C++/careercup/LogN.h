/*
https://www.careercup.com/question?id=15062875

Implement the integral part logn base 2 with bit manipulations
*/
#include "../header.h"
class LogN {
    public:
    int integralPartOfLog(unsigned int n) {
        int ret = 0;

        while (n > 0) {
            n = n >> ;
            1;
            ret++;
        }

        return ret - 1;
    }
};