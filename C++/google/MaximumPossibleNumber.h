#include "../Header.h"

/*
Given a number M (N-digit integer) and K-swap operations(a swap
operation can swap 2 digits), devise an algorithm to get the maximum possible integer?
Examples:
M = 132 K = 1 output = 312
M = 132 K = 2 output = 321
M = 7899 k = 2 output = 9987
M = 8799 and K = 2 output = 9987
*/

#include <iostream>
#include <vector>
using namespace std;
void getMax(vector<int> &input, int k, int &maxNum, vector<int> &output)
{
    if (k == 0)
    {
        int sum = 0;
        for (auto v : input)
        {
            sum *= 10;
            sum += v;
        } //calculate the number after several swaps
        if (sum > maxNum)
        {
            maxNum = sum;
            output = input;
        } //update the results
        return;
    }

    for (int i = 0; i < input.size() - 1; i++)
    {
        for (int j = i + 1; j < input.size(); j++)
        {
            swap(input[i], input[j]);             //try to swap input[i] with input[j]
            getMax(input, k - 1, maxNum, output); //takecare of the other k - 1 swaps
            swap(input[i], input[j]);             //swap back
        }
    }
    return;
}
void swap2max(vector<int> input, int k)
{
    if (input.size() < 2)
    {
        cout << "invalid input" << endl;
    }
    int maxNum = INT_MIN;
    vector<int> maxVec;
    getMax(input, k, maxNum, maxVec); //DFS function to call

    //print out the results here
    cout << "{ ";
    for (int i = 0; i < maxVec.size(); i++)
    {
        cout << maxVec[i] << " ";
    }
    cout << " }" << endl;
    return;
}

int main(int argc, const char *argv[])
{

    vector<int> input1 = {1, 3, 2};
    swap2max(input1, 1);

    vector<int> input2 = {1, 3, 2};
    swap2max(input2, 2);

    vector<int> input3 = {7, 8, 9, 9};
    swap2max(input3, 2);

    vector<int> input4 = {8, 7, 9, 9};
    swap2max(input4, 2);
    return 0;
}

// Mine
void makeMax(string str, int k, int index, string &res)
{
    if (k == 0 || index == str.length())
    {
        if (stoi(str) > stoi(res))
            res = str;
        return;
    }

    for (int i = index; i <= str.length() - 1; i++)
    {
        swap(str[index], str[i]);
        makeMax(str, k - 1, index + 1, res);
        swap(str[index], str[i]);
    }
}

string makeMax(string str, int k)
{
    string res = "0";

    makeMax(str, k, 0, res);

    return res;
}

int main()
{
    {
        string str = "132";
        int k = 1;
        auto res = makeMax(str, k);

        cout << str << " = " << res << endl;
    }

    {
        string str = "7899";
        int k = 2;
        auto res = makeMax(str, k);

        cout << str << " = " << res << endl;
    }

    return 0;
}