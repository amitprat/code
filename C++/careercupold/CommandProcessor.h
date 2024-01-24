#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct File {
	string name;

	File(string name) :name(name) {}
};

struct Directory {
	string name;
	vector<Directory> childDirs;
	vector<File> childFiles;

	Directory() {}
	Directory(string name) :name(name) {}
};

class Filesystem {
	Directory rootDirectory;
	unordered_map<string, Directory*> directoryLinks;
	stack<string> curPath;

public:
	Filesystem() {
		curPath.push("root");
		rootDirectory = Directory("root");
		directoryLinks.insert({ "root", &rootDirectory });
	}

	void pwd() {
		cout << toPath(curPath) << endl;
	}

	void ls(string path, bool recursive) {
		string cur;

		if (path == "/") cur = curPath.top();
		else {
			vector<string> paths = split(path);
			for (auto path : paths) {
				if (directoryLinks.find(path) == directoryLinks.end()) {
					cout << "Invalid path" << endl;
					return;
				}
			}
			cur = paths.back();
		}
		Directory dir = *directoryLinks[cur];

		if (recursive) {
			printRec(dir, "");
		}
		else {
			cout << "/" << dir.name << endl;
			for (auto chdir : dir.childDirs) cout << "/" << dir.name << chdir.name << endl;
			for (auto chfie : dir.childFiles) cout << chfie.name << endl;
		}
	}

	void mkdir(string dirName) {
		if (directoryLinks.find(dirName) != directoryLinks.end()) {
			cout << "Directory already exists" << endl;
			return;
		}
		if (dirName.length() > 100) {
			cout << "Invalid File or Folder Name" << endl;
		}

		Directory* dir = directoryLinks[curPath.top()];
		dir->childDirs.push_back(Directory(dirName));
		directoryLinks.insert({ dirName, &dir->childDirs.back() });
	}

	void changeDirectory(string dirName) {
		if (dirName == "..") {
			curPath.pop();
			return;
		}

		vector<string> paths = split(dirName);
		for (auto& path : paths) {
			if (directoryLinks.find(path) == directoryLinks.end()) {
				cout << "Directory not found";
				return;
			}
		}
		for (auto& path : paths) curPath.push(path);
	}

	void createFile(string fileName) {
		if (fileName.length() > 100) {
			cout << "Invalid File or Folder Name" << endl;
		}

		Directory* dir = directoryLinks[curPath.top()];
		unordered_set<string> fileNames;
		for (auto e : dir->childFiles) fileNames.insert(e.name);
		if (fileNames.count(fileName) > 0) {
			return;
		}
		dir->childFiles.push_back(File(fileName));
	}

private:
	string toPath(stack<string> st) {
		string res;
		while (!st.empty()) {
			res = st.top() + "/" + res;
			st.pop();
		}
		res = "/" + res;
		if (res.back() == '/') res.pop_back();
		return res;
	}

	vector<string> split(string str) {
		vector<string> res;
		size_t start = 0;
		size_t pos = string::npos;
		while ((pos = str.find("/", start)) != string::npos) {
			res.push_back(str.substr(start, pos));
			start = pos + 1;
		}

		if (start < str.length() && !str.substr(start).empty()) {
			res.push_back(str.substr(start));
		}

		//print(res);

		return res;
	}

	void printRec(Directory dir, string parent) {
		cout << parent << "/" << dir.name << endl;
		for (auto chfile : dir.childFiles) cout << chfile.name << endl;
		for (auto chdir : dir.childDirs) printRec(chdir, parent + "/" + dir.name);
	}
};

enum class Action {
	InvalidCommand,
	Quit,
	Mkdir,
	ListDir,
	WorkingDir,
	CreateFile,
	ChangeDir
};

class CommandProcessor {
	Filesystem filesystem;

public:
	void handleCommand() {
		bool breakApplication = false;
		do {
			string cmd;
			getline(cin, cmd);

			//cout << "Input: " << cmd << endl;
			pair<Action, vector<string>> splitCmd = parse(cmd);
			switch (splitCmd.first) {
			case Action::Quit:
				breakApplication = true;
				break;
			case Action::Mkdir:
				if (splitCmd.second.size() > 1 || splitCmd.second.empty()) {
					cout << "Invalid command" << endl;
					break;
				}

				filesystem.mkdir(splitCmd.second.front());
				break;
			case Action::ListDir:
				if (splitCmd.second.size() > 2) {
					cout << "Invalid command" << endl;
					break;
				}

				if (splitCmd.second.size() == 0) {
					filesystem.ls("/", false);
				}
				else if (splitCmd.second.size() == 1) {
					bool rec = false;
					string path;
					if (splitCmd.second.front() == "-r") rec = true;
					else path = splitCmd.second.front();

					filesystem.ls(path, rec);
				}
				else if (splitCmd.second.size() == 2) {
					string path = splitCmd.second[0];
					if (path == "-r") path = splitCmd.second[1];
					filesystem.ls(path, true);
				}
				break;
			case Action::ChangeDir:
				if (splitCmd.second.empty()) {
					cout << "Invalid command" << endl;
					break;
				}
				filesystem.changeDirectory(splitCmd.second.front());
				break;
			case Action::CreateFile:
				if (splitCmd.second.size() > 1 || splitCmd.second.empty()) {
					cout << "Invalid command" << endl;
					break;
				}
				filesystem.createFile(splitCmd.second.front());
				break;
			case Action::WorkingDir:
				if (!splitCmd.second.empty()) {
					cout << "Invalid command" << endl;
					break;
				}
				filesystem.pwd();
				break;
			case Action::InvalidCommand:
				cout << "Unrecognized command" << endl;
				break;
			}
		} while (!breakApplication);
	}

private:
	pair<Action, vector<string>> parse(string cmd) {
		vector<string> parts = split(cmd);

		if (parts.empty()) return { Action::InvalidCommand, {} };

		string cmdPart = parts[0];
		parts.erase(parts.begin());

		if (cmdPart == "ls") {
			return { Action::ListDir, parts };
		}
		else if (cmdPart == "cd") {
			return { Action::ChangeDir, parts };
		}
		else if (cmdPart == "touch") {
			return { Action::CreateFile, parts };
		}
		else if (cmdPart == "mkdir") {
			return { Action::Mkdir, parts };
		}
		else if (cmdPart == "ls") {
			return { Action::ListDir, parts };
		}
		else if (cmdPart == "pwd") {
			return { Action::WorkingDir, parts };
		}
		else if (cmdPart == "quit") {
			return { Action::Quit, parts };
		}
		else {
			return { Action::InvalidCommand, parts };
		}

		return { Action::InvalidCommand, {} };
	}

	vector<string> split(string str) {
		vector<string> res;
		size_t start = 0;
		size_t pos = string::npos;
		while ((pos = str.find(" ", start)) != string::npos) {
			res.push_back(str.substr(start, pos));
			start = pos + 1;
		}

		if (start < str.length() && !str.substr(start).empty()) {
			res.push_back(str.substr(start));
		}

		//print(res);

		return res;
	}

	void print(vector<string> str) {
		for (auto s : str) {
			cout << s << " ";
		}
		cout << endl;
	}
};

int test() {
	CommandProcessor processor;
	processor.handleCommand();

	return 0;
}