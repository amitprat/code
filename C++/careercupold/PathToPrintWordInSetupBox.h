#pragma once
#include "../Header.h"

// https://www.careercup.com/question?id=5127611667709952
/*
Write code to give the character sequence given a word, For example, if the word is "CON", the function will print this:
Right//now we're at B
Right//now we're at C
OK//to select C
Down
DOwn
Right
Right
OK//to select O
Left//now at N
OK//to select N
*/
class  PathToPrintWordInSetupBox
{
public:
	static void test() {
		int colSize = 5;
		int limit = 25;

		{
			string word = "constable";
			string path1 = getPath1(colSize, limit, word);
			string path2 = getPath2(colSize, limit, word);
			string path3 = getPath3(word, colSize);
			assert(path1 == path2);
			assert(path1 == path3);
			cout << path1 << endl;
		}

		{
			string word = "zebra";
			string path1 = getPath1(colSize, limit, word);
			string path2 = getPath2(colSize, limit, word);
			string path3 = getPath3(word, colSize);
			assert(path1 == path2);
			assert(path1 == path3);
			cout << path1 << endl;
		}

		{
			string word = "answer";
			string path1 = getPath1(colSize, limit, word);
			string path2 = getPath2(colSize, limit, word);
			string path3 = getPath3(word, colSize);
			assert(path1 == path2);
			assert(path1 == path3);
			cout << path1 << endl;
		}

		{
			string word = "helloworld";
			string path1 = getPath1(colSize, limit, word);
			string path2 = getPath2(colSize, limit, word);
			string path3 = getPath3(word, colSize);
			assert(path1 == path2);
			assert(path1 == path3);
			cout << path1 << endl;
		}
	}

	static string getPath1(int colSize, int limit, string word) {
		string res;
		Point cur = { 0,0 };

		unordered_map<char, string> map;
		for (auto ch : word) {
			string curRes;
			Point des = { (ch - 'a') % 5,(ch - 'a') / 5 };
			if (des.y > cur.y) {
				curRes += string(des.y - cur.y, 'd');
				cur.y = des.y;
			}

			if (des.y < cur.y) {
				curRes += string(cur.y - des.y, 'u');
				cur.y = des.y;
			}

			if (des.x > cur.x) {
				curRes += string(des.x - cur.x, 'r');
				cur.x = des.x;
			}

			if (des.x < cur.x) {
				curRes += string(cur.x - des.x, 'l');
				cur.x = des.x;
			}

			map[ch] = curRes;
			curRes += '\n';
			res += curRes;
		}

		cout << "Result:" << to_string(map) << endl;
		return res;
	}

	static string getPath2(int colSize, int limit, string word) {
		string res;
		Point cur = { 0,0 };
		unordered_map<char, string> map;

		for (auto ch : word) {
			string curRes;
			Point des = { (ch - 'a') % 5,(ch - 'a') / 5 };
			curRes += string(abs(des.y - cur.y), des.y > cur.y ? 'd' : 'u');
			curRes += string(abs(des.x - cur.x), des.x > cur.x ? 'r' : 'l');

			map[ch] = curRes;
			curRes += '\n';
			res += curRes;
			cur = des;
		}

		cout << "Result:" << to_string(map) << endl;
		return res;
	}

	static string getPath3(string str, int rowSize)
	{
		string res;
		Point src = { 0, 0 };

		for (auto ch : str) {
			string curRes;
			Point dst = { (ch - 'a') / 5, (ch - 'a') % 5 };
			curRes += string(abs(dst.x - src.x), (dst.x > src.x ? 'd' : 'u'));
			curRes += string(abs(dst.y - src.y), (dst.y > src.y ? 'r' : 'l'));
			curRes += '\n';

			res += curRes;
			src = dst;
		}

		return res;
	}
};