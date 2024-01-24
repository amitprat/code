#include "../header.h"

/*
https://careercup.com/question?id=6324318653382656

Given a length n, count the number of strings of length n that can be made using ‘a’, ‘b’ and ‘c’ with at-most one ‘b’ and two ‘c’s allowed.

def count_abc(n, nb, nc):
    if n == 1:
        return 1 + (1 if nb else 0) + (1 if nc else 0)

    ret = count_abc(n-1, nb, nc)
    if nb > 0:
        c2 = count_abc(n-1, nb-1, nc)
        ret += c2
    if nc > 0:
        c3 = count_abc(n-1, nb, nc-1)
        ret += c3
    return ret


if __name__ == '__main__':
    print(count_abc(1, 1, 2))
    print(count_abc(2, 1, 2))
    print(count_abc(3, 1, 2))
    print(count_abc(4, 1, 2))
    print(count_abc(5, 1, 2))
    print(count_abc(6, 1, 2))
    print(count_abc(7, 1, 2))
    print(count_abc(100, 1, 2))
*/
class CountNumberOfStringMadeOfABC {
   public:
    static void test() {
        CountNumberOfStringMadeOfABC obj;
        cout << obj.count_abc(1, 1, 2) << endl;
        cout << obj.count_abc(2, 1, 2) << endl;
        cout << obj.count_abc(3, 1, 2) << endl;
        cout << obj.count_abc(4, 1, 2) << endl;
        cout << obj.count_abc(5, 1, 2) << endl;
        cout << obj.count_abc(6, 1, 2) << endl;
        cout << obj.count_abc(7, 1, 2) << endl;
        cout << obj.count_abc(100, 1, 2) << endl;
    }

   private:
    int count_abc(int n, int nb, int nc) {
        if (n < 0 || nb < 0 || nc < 0) return 0;
        if (n == 0) return 1;

        return count_abc(n - 1, nb, nc) + count_abc(n - 1, nb - 1, nc) + count_abc(n - 1, nb, nc - 1);
    }

    privatE : int countMemo(int n, int nb, int nc) {
        vector<vector<vector<int>>> table(n + 1, vector<vector<int>>(nb + 1, vector<int>(nc + 1, -1)));

        return countMemo(n, nb, nc, table);
    }

    int countMemo(int n, int nb, int nc, vector<vector<vector<int>>>& table) {
        if (n < 0 || nb < 0 || nc < 0) return 0;
        if (n == 0) return 1;
        if (table[n][nb][nc] != -1) return table[n][nb][nc];

        table[n][nb][nc] = countMemo(n - 1, nb, nc, table) + countMemo(n - 1, nb - 1, nc, table) + countMemo(n - 1, nb, nc - 1, table);

        return table[n][nb][nc];
    }
};