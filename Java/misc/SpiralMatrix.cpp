#include "../Header.h"

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int left=0,right=matrix[0].size()-1;
        int top=0,bot=matrix.size()-1;
        while(true)
        {
            if(left>right || top>bot)
                break;
            if(left==right)
            {
                for(int i=top;i<=bot;i++)
                    ans.push_back(matrix[i][left]);
                break;
            }
            if(top==bot)
            {
                for(int i=left;i<=right;i++)
                    ans.push_back(matrix[top][i]);
                break;
            }
            for(int i=left;i<=right;i++)
            {
                ans.push_back(matrix[top][i]);
            }
            for(int i=top+1;i<=bot;i++)
            {
                ans.push_back(matrix[i][right]);
            }
            for(int i=right-1;i>=left;i--)
            {
                ans.push_back(matrix[bot][i]);
            }
            for(int i=bot-1;i>=top+1;i--)
            {
                ans.push_back(matrix[i][left]);
            }
            left++,right--;
            top++,bot--;
        }
        return ans;
    }
};