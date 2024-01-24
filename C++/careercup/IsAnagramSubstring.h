#include "../header.h"

/*
https://careercup.com/question?id=5389078581215232

Given two strings a and b, find whether any anagram of string a is a sub-string of string b. For eg:
if a = xyz and b = afdgzyxksldfm then the program should return true.
*/

class IsAnagramSubstring
{
public:
    static void test()
    {
        IsAnagramSubstring obj;
        string a = "xyz";
        string b = "afdgzyxksldfm";

        string anagram;
        int pos = 0;
        bool result = obj.isAnagramSubstringOptimized(a, b, anagram, pos);
        cout << "result: " << result << endl;
        cout << "a: " << a << " is found in " << b << " at position: " << pos << ", anagram: " << anagram << endl;
    }

private:
    bool isAnagramSubstring(string a, string b, string &anagram, int &pos)
    {
        int aFreq[26] = {0};
        int bFreq[26] = {0};

        int l1 = a.length();
        for (int i = 0; i < l1; i++)
        {
            char ch1 = a[i];
            char ch2 = b[i];

            aFreq[ch1 - 'a']++;
            bFreq[ch2 - 'a']++;
        }

        int l2 = b.length();
        for (int i = l1; i <= l2; i++)
        {
            if (same(aFreq, bFreq))
            {
                pos = i - l1;
                anagram = b.substr(pos, l1);
                return true;
            }

            if (i < l2)
            {
                char ch = b[i];
                bFreq[ch - 'a']++;
                bFreq[b[i - l1] - 'a']--;
            }
        }

        return false;
    }

    bool same(int aFreq[], int bFreq[])
    {
        for (int i = 0; i < 26; i++)
        {
            if (aFreq[i] != bFreq[i])
                return false;
        }

        return true;
    }

private:
    bool isAnagramSubstringOptimized(string a, string b, string &anagram, int &pos)
    {
        int l1 = a.length();
        int l2 = b.length();
        if (l2 < l1)
            return false;

        int aFreq[26] = {0};
        for (int i = 0; i < l1; i++)
        {
            char ch = a[i];
            aFreq[ch - 'a']++;
        }

        int bFreq[26] = {0};
        int cnt = 0;
        for (int i = 0; i < l2; i++)
        {
            char ch = b[i];
            bFreq[ch - 'a']++;
            if (bFreq[ch - 'a'] <= aFreq[ch - 'a'])
                cnt++;
            if (cnt == l1)
            {
                anagram = b.substr(i - l1 + 1, l1);
                pos = i - l1 + 1;
                return true;
            }

            // move left pointer
            ch = b[i - l1 + 1];
            bFreq[ch - '0']--;
        }

        return false;
    }
};