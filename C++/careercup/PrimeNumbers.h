#include "../header.h"

class PrimeNumbers {
   public:
    static void test() {
        PrimeNumbers obj;

        auto res1 = obj.generatePrimes1(100);
        auto res2 = obj.generatePrimes2(100);

        assert(areEqual(res1, res2));

        cout << "Primes: " << res1 << endl;
    }

   private:
    bool isPrime(int number) {
        if (number <= 1) return false;
        if (number == 2) return true;
        if (number % 2 == 0) return false;

        for (int i = 3; i * i <= number; i += 2) {
            if (number % i == 0)
                return false;
        }

        return true;
    }

    bool isPrime2(int num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;

        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                return false;
            }
        }

        return true;
    }

   private:
    // generate first n prime numbers
    vector<int> generatePrimes1(int n) {
        vector<int> result;

        if (n < 2) return result;

        result.push_back(2);

        for (int mul = 3; mul < n; mul += 2) {
            if (isPrime(mul)) {
                result.push_back(mul);
            }
        }

        return result;
    }

   private:
    // get all primes numbers between 1..n
    vector<int> generatePrimes2(int n) {
        vector<bool> primes(n + 1, true);
        primes[0] = primes[1] = false;

        for (int i = 2; i <= n; i++) {
            if (primes[i]) {
                // if current number is prime, then mark all its multiples as non-prime
                for (int j = i * i; j <= n; j += i) {
                    primes[j] = false;
                }
            }
        }

        vector<int> result;
        for (int i = 0; i <= n; i++) {
            if (primes[i]) result.push_back(i);
        }

        return result;
    }
};