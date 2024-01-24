#pragma once
#include "../header.h"

class ReverseWordsInSentence
{
public:
    static void test()
    {
        ReverseWordsInSentence obj;
        string str = "this is a sentence";
        string out = obj.reverse(str);
        cout << "Revered string: " << out << endl;
    }

private:
    string reverse(const string &input)
    {
        string result = input;

        int s = 0;
        int e = 0;
        for (int i = 0; i <= input.size(); i++)
        {
            if (isspace(input[i]))
            {
                reverse(result, s, i - 1);
                s = i + 1;
            }
        }

        return result;
    }

    void reverse(string &input, int s, int e)
    {
        while (s < e)
        {
            swap(input[s++], input[e--]);
        }
    }
};