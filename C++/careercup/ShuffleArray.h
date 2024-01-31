#include "../header.h"

class ShuffleArray {
   private:
    void shuffle(vector<int>& arr) {
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) {
            int r = rand() % (i + 1);  // generate random number between {0, i}
            swap(arr[i], arr[r]);
        }
    }

   private:
    /*
    Given array A of size N, using function Random(returns random number between 0 and 1) implement function that will return array of size N with randomly shuffled elements of the array A.
    You shoul give only algo.
    */
    void fun(int a[], int n) {
        for (int i = n - 1; i >= 0; i--) {
            int index = (int)(i * rand());  // where rand() - generates between 0-1
            swap(a[i], a[index]);
        }
    }

   private:
    // Fisher Yates Shuffle :
    void shuffle(vector<int>& arr) {
        for (int i = 0; i < arr.size() - 1; i++) {
            int j = randInt(arr, i, arr.size() - 1);  // randInt generates random number between [i to size]
            swap(arr[i], arr[j]);                     // swap i to j.
        }
    }

    int randInt(vector<int>& arr, int s, int e) {
        return rand() % (e - s) + s;
    }
};