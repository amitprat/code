#include "../Header.h"

class RemoveAAndBC
{
public:
    static void test()
    {
        RemoveAAndBC obj;
        char str1[] = "ad";
        obj.stringFilter(str1);
        cout << str1 << endl;

        char str2[] = "acbac";
        obj.stringFilter(str2);
        cout << str2 << endl;

        char str3[] = "aaac";
        obj.stringFilter(str3);
        cout << str3 << endl;

        char str4[] = "react";
        obj.stringFilter(str4);
        cout << str4 << endl;

        char str5[] = "aa";
        obj.stringFilter(str5);
        cout << str5 << endl;

        char str6[] = "ababaac";
        obj.stringFilter(str6);
        cout << str6 << endl;
    }
    void stringFilter(char str[])
    {
        int k = 0;
        bool prevB = false;
        for (int i = 0; i < strlen(str); i++)
        {
            switch (str[i])
            {
            case 'a':
                break;
            case 'b':
                if (prevB)
                    str[k++] = 'b';
                prevB = true;
                break;
            case 'c':
                if (!prevB)
                    str[k++] = 'c';
                prevB = false;
                break;
            default:
                str[k++] = str[i];
                prevB = false;
                break;
            }
        }
        str[k] = '\0';
    }
};
