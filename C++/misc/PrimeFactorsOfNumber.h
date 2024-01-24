#include "../header.h"

class PrimeFactorsOfNumber {
    void printFactors(int number) {
        // print factor 2 of number
        while (!(number % 2)) {
            cout << "2"
                 << "\t";
            number /= 2;
        }

        // print rest of factors
        int sqNum = sqrt(number);
        for (int i = 3; i <= sqNum; i += 2)  // check for all possible prime numbers which can devide this number
        {
            int div = i;
            while (number % div == 0) {
                cout << i << "\t";
                div *= i;
            }
        }

        // print last remaining prime number
        if (n > 2) cout << n << " ";
    }
};