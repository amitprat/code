#include "../header.h"
#include "LargestAreaUnderHistogram.h"

class MaximumSizeRectangleBinarySubMatrix {
   public:
    static void test() {
        MaximumSizeRectangleBinarySubMatrix obj;
        vector<vector<int>> mat = {
            {0, 1, 1, 0},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 0, 0},
        };

        cout << "Area of maximum rectangle is "
             << obj.maxRectangle(mat);
    }

    int maxRectangle(vector<vector<int>>& mat) {
        LargestAreaUnderHistogram obj;
        int mxArea = 0;
        for (int i = 0; i < mat.size(); i++) {
            if (i > 0) {
                for (int j = 0; j < mat[i].size(); j++) {
                    if (mat[i][j]) mat[i][j] += mat[i - 1][j];
                }
            }
            mxArea = max(mxArea, obj.largestArea(mat[i]));
        }

        return mxArea;
    }
};