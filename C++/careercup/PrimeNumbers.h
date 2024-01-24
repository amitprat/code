#include "../header.h"

class PrimeNumbers {
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
    vector<int> generatePrimes(int n) {
        if (n <= 0) return {};

        vector<int> result(n);
        result[0] = 2;
        int cnt = 1;
        for (int i = 3; cnt <= n; i += 2) {
            if (isPrime(i)) {
                result[cnt] = i;
                cnt++;
            }
        }

        return result;
    }

    // get all primes numbers between 1..n
    vector<int> getAllPrimes(int n) {
        vector<bool> primes(n + 1, true);
        primes[0] = primes[1] = false;

        for (int i = 2; i <= n; i++) {
            if (primes[i]) {  // if current number is prime, then mark all its multiples as non-prime
                for (int j = i * i; j <= n; j += i) primes[j] = false;
            }
        }

        vector<int> result;
        for (int i = 0; i <= n; i++) {
            if (primes[i]) result.push_back(i);
        }

        return result;
    }
};