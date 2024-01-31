#include "../header.h"

/*
Ok heres the solution. SantiagoYMG is pretty close.
The solution is O(n) in time complexity.

Make all of them stand in a row.
Lets say the people are a,b,c,d,e,f,g,h,i,j,.......n

Compare a and b.
if a knows b => a is certainly not the celebrity. Probable celebrity = b
if a doesnt know b => b is certainly not the celebrity. Probable celebrity = a

In either case compare the probable celebrity to the next person in line ie 'c' and repeat the process. Each comparison should eliminate 1 person and have another as the probable celebrity. At the end, the probable celebrity who survives is the certain celebrity.

Complexity = O(n)
*/

class CelebrityProblem {
   public:
    static void test() {
        CelebrityProblem obj;
        vector<vector<int>> mat = {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 1, 0}};

        assert(obj.findCelebrity(mat, 4) == obj.findCelebrity2(mat, 4));

        cout << obj.findCelebrity(mat, 4) << endl;
    }

   private:
    int findCelebrity(vector<vector<int>>& mat, int m) {
        int a = 0, b = m - 1;
        while (a < b) {
            if (knows(mat, a, b))
                a++;
            else
                b--;
        }

        return validateCelebrity(mat, a);
    }

    bool knows(vector<vector<int>>& mat, int a, int b) {
        return mat[a][b];
    }

    int validateCelebrity(vector<vector<int>>& mat, int a) {
        // if celerity knows anyone
        for (int j = 0; j < mat[a].size(); j++)
            if (a != j && mat[a][j]) return -1;

        // if anyone else doesn't know celeb
        for (int i = 0; i < mat[a].size(); i++)
            if (a != i && !mat[i][a]) return -1;

        return a;
    }

   private:
    int findCelebrity2(vector<vector<int>>& a) {
        int candidate = 0;
        int i = 1;

        while (i < a.size()) {
            // if either of these condition isn't true, then 0 can't be celebrity so consider next one as candidate
            if (!a[i][candidate] || a[candidate][i])
                candidate = i;
            i++;
        }

        // check
        for (int i = 0; i < a.size(); i++) {
            if (i != candidate && (!a[i][candidate] || a[candidate][i]))
                return -1;  // no celebrity exist
        }
        return candidate;
    }
};