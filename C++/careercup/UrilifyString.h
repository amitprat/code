#include "../header.h"

class UrilifyString
{
public:
    static void test()
    {
        char str1[18] = {'\0'};
        strcpy(str1, "Mr John Smith");
        UrilifyString obj;
        obj.urilify1(str1);
        cout << "Urilified string 1: " << str1 << endl;

        char str2[] = "Mr John Smith";
        char *str2_res = obj.urilify2(str2);
        cout << "Urilified string 2: " << str2_res << endl;

        string str3 = "Mr John Smith    ";
        string str3_res = obj.urilify3(str3);
        cout << "Urilified string 3: " << str3_res << endl;

        string str4 = "Mr John Smith";
        string str4_res = obj.urilify4(str4);
        cout << "Urilified string 4: " << str4_res << endl;
    }

private:
    void urilify1(char str[])
    {
        int n = strlen(str);

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (str[i] == ' ')
                cnt++;
        }

        int newLen = n + 2 * cnt;
        int j = newLen - 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (str[i] == ' ')
            {
                str[j--] = '0';
                str[j--] = '2';
                str[j--] = '%';
            }
            else
            {
                str[j--] = str[i];
            }
        }
    }

    char *urilify2(char str[])
    {
        int n = strlen(str);

        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (str[i] == ' ')
                cnt++;
        }

        int newLen = n + 2 * cnt;
        char *newStr = (char *)malloc(newLen * sizeof(char));
        int j = newLen - 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (str[i] == ' ')
            {
                newStr[j--] = '0';
                newStr[j--] = '2';
                newStr[j--] = '%';
            }
            else
            {
                newStr[j--] = str[i];
            }
        }

        return newStr;
    }

    string urilify3(string str)
    {
        int n = str.length();
        int cnt = 0;
        for (auto ch : str)
            if (ch == ' ')
                cnt++;
        int m = n + 2 * cnt;
        int j = m - 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (str[i] == ' ')
            {
                str[j--] = '0';
                str[j--] = '2';
                str[j--] = '0%';
            }
            else
            {
                str[j--] = str[i];
            }
        }

        return str;
    }

    string urilify4(string str)
    {
        int n = str.length();
        int cnt = 0;
        for (auto ch : str)
            if (ch == ' ')
                cnt++;
        int m = n + 2 * cnt;
        string newStr(m, '\0');
        int j = m - 1;
        for (int i = n - 1; i >= 0; i--)
        {
            if (str[i] == ' ')
            {
                newStr[j--] = '0';
                newStr[j--] = '2';
                newStr[j--] = '0%';
            }
            else
            {
                newStr[j--] = str[i];
            }
        }

        return newStr;
    }
};