#pragma once
#include "../Header.h"

// https://www.careercup.com/question?id=5178446623801344
class TrimSpaces
{
public:
	static void test()
	{
		string str = "___Hello___World___Hello_World_________";
		cout << trimSpaces(str) << endl;
		{
			int i = 0;
			bool prevCh = false;
			bool putGap = false;
			for (int j = 0; j < str.length(); j++)
			{
				if (str[j] != '_')
				{
					if (putGap)
						str[i++] = '_';
					str[i++] = str[j];
					prevCh = true;
					putGap = false;
				}
				else
				{
					if (prevCh)
						putGap = true;
					prevCh = false;
				}
			}
			str = str.substr(0, i);
			cout << str << endl;
		}

		{
			str = "___Hello___World___Hello_World_________";
			cout << trimSpaces(str) << endl;

			char* prev = const_cast<char*>(str.c_str());
			const char* cur = str.c_str();
			bool prevCh = false;
			bool putSpace = false;
			while (*cur != '\0')
			{
				if (*cur == '_')
				{
					if (prevCh)
						putSpace = true;
					prevCh = false;
				}
				else
				{
					if (putSpace)
						*prev++ = '_';
					*prev++ = *cur;
					putSpace = false;
					prevCh = true;
				}
				cur++;
			}
			*prev = '\0';
			cout << str.c_str() << endl;
		}
	}

	static string trimSpaces(string& str) {
		int i = 0;
		bool putGap = false;
		for (int j = 0; j < str.length(); j++) {
			if (str[j] == '_') { putGap = i > 0; }
			else {
				if (putGap) str[i++] = '_';
				str[i++] = str[j];
				putGap = false;
			}
		}

		str = str.substr(0, i);

		return str;
	}
};