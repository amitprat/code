#include "../header.h"

class FindMagicNumber {
   public:
    static void test() {
        FindMagicNumber obj;

        {
            vector<int> arr = {-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13};
            //                  0    1    2  3  4  5  6  7  8  9   10
            int pos = obj.magicNumber(arr);
            cout << "Magic index is : " << pos << endl;
        }

        {
            vector<int> arr = {-10, -5, 2, 2, 2, 3, 4, 7, 9, 12, 13};
            //                  0    1  2  3  4  5  6  7  8  9   10
            int pos = obj.magicNumberWithDuplicates(arr);
            cout << "Magic index is : " << pos << endl;
        }
    }

    int magicNumber(vector<int> arr) {
        int l = 0, r = arr.size() - 1;

        while (l <= r) {
            int m = (l + r) / 2;
            if (arr[m] == m) return m;
            // if mid element is less than mid index, then its not possible to match index = element on left side as
            // elements are all distict and sorted so element on left must decrease by atleast on left side, if so
            // it will never match the index.
            else if (arr[m] < m)
                l = m + 1;
            // same as above. if mid element is larger than mid position, then element on right side should atleast increase
            // by one and hence position and element will never be able to catch-up.
            else if (arr[m] > m)
                r = m - 1;
        }

        return -1;
    }

    int magicNumberWithDuplicates(vector<int> arr) {
        int l = 0, r = arr.size() - 1;
        return magicNumberWithDuplicates(arr, l, r);
    }
    int magicNumberWithDuplicates(vector<int> arr, int l, int r) {
        if (l > r) return -1;
        int m = (l + r) / 2;

        if (arr[m] == m) return m;
        // if arr[m] < m, then its possible to have element on both left or right as elements are duplicates
        // for ex: 1 2 2 2 3 4 5
        //         0 1 2 3 4 5 6
        // Here, even though arr[3] = 2 is less than 3 but still we have element on left.
        // Because, elements are sorted so elements between arr[2] and arr[3] can't be greater than arr[m]
        if (arr[m] < m) {
            int left = magicNumberWithDuplicates(arr, l, min(m - 1, arr[m]));
            if (left != -1) return left;
            return magicNumberWithDuplicates(arr, m + 1, r);
        } else if (arr[m] > m) {
            return magicNumberWithDuplicates(arr, m + 1, r);
        }
    }
};