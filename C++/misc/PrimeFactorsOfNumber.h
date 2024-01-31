#pragma once
#include "../header.h"

class PrimeFactorsOfNumber {
   public:
    static void test() {
        PrimeFactorsOfNumber obj;
        int number = 100;

        auto res1 = obj.getPrimeFactors(number);
        cout << format("Prime factors of number = {0} are {1}", number, to_string(res1)) << endl;
    }

   private:
    vector<int> getPrimeFactors(int number) {
        vector<int> primeFactors;

        // print factor 2 of number
        while (!(number % 2)) {
            primeFactors.push_back(2);
            number /= 2;
        }

        // print rest of factors
        for (int div = 3; div * div <= number; div += 2)  // check for all possible prime numbers which can devide this number
        {
            while (number % div == 0) {
                primeFactors.push_back(div);
                number /= div;
            }
        }

        // print last remaining prime number
        if (number > 2) {
            primeFactors.push_back(number);
        }

        return primeFactors;
    }
};