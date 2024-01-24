#include "../header.h"

class ShuffleArray {
   private:
    void shuffle(vector<int>& arr) {
        int n = arr.size();
        for (int i = n - 1; i >= 0; i--) {
            int r = rand() % (i + 1);
            swap(arr[i], arr[r]);
        }
    }
};