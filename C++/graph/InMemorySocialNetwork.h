#pragma once
#include "../Header.h"

class InMemorySocialNetwork
{
    class Person {
    public:
        string id;
        string name;

        string to_string() {
            return "{" + id + ", " + name + "}";
        }
    };

    class Graph {
        unordered_map<string, vector<string>> personsGraph;
        unordered_map<string, Person> persons;
    public:
        void add(Person person) {
            persons.insert({ person.id, person });
        }

        Person get(string id) {
            return persons[id];
        }

        void addFriend(string id1, string id2) {
            if (!exists(id1)) { cout << "Id : " << id1 << " doesn't exists!" << endl; }
            if (!exists(id2)) { cout << "Id : " << id2 << " doesn't exists!" << endl; }

            personsGraph[id1].push_back(id2);
            personsGraph[id2].push_back(id1);
        }

        void print() {
            for (auto person : persons) {
                auto l = getFriends(person.first);
                cout << person.first << " : " << to_string(l) << endl;
            }
        }

        vector<string> getFriends(string id) {
            return personsGraph[id];
        }

        bool exists(string id) {
            return persons.find(id) != persons.end();
        }
    };
public:
    Graph graph;

    static void test() {
        InMemorySocialNetwork obj;
        obj.handleUserInput();
    }

    void handleUserInput() {
        cout << "1) Show current graph" << endl;
        cout << "2) Show friends" << endl;
        cout << "3) Join site" << endl;
        cout << "4) Show suggestions" << endl;
        cout << "5) Add friend" << endl;
        cout << "0) Exit" << endl;

        int choice = 0;

        while (true) {
            cout << "Enter Choice: ";
            cin >> choice;
            cout << endl;

            switch (choice) {
                case 0:
                    cout << "Exiting..." << endl;
                    return;
                case 1:
                    printGraph();
                    break;
                case 2:
                    showFriends();
                    break;
                case 3:
                    joinSite();
                    break;
                case 4:
                    showSuggestion();
                    break;
                case 5:
                    addFriend();
                    break;
                default:
                    break;
            }
        }
    }

    void printGraph() {
        this->graph.print();
        cout << endl;
    }

    void showFriends() {
        string id;
        cout << "Enter id: ";
        cin >> id;
        cout << endl;

        auto res = this->graph.getFriends(id);

        cout << to_string(res) << endl;
    }

    void joinSite() {
        Person person;
        cout << "Person.id: ";
        cin >> person.id;
        cout << endl;

        cout << "Person.name: ";
        cin >> person.name;
        cout << endl;

        this->graph.add(person);
    }

    void addFriend() {
        string id1, id2;

        cout << "Enter id1: ";
        cin >> id1;
        cout << endl;

        cout << "Enter id2: ";
        cin >> id2;
        cout << endl;

        this->graph.addFriend(id1, id2);
    }

    void showSuggestion() {
        string id;
        cout << "Person.id: ";
        cin >> id;
        cout << endl;

        queue<string> q;
        unordered_set<string> visited;
        q.push(id);
        visited.insert(id);

        bool done = false;
        while (!done) {
            auto f = this->graph.getFriends(q.front());  q.pop();
            auto res = getCommonFriends(f);
            cout << to_string(res) << endl;

            for (auto l : f) {
                if (visited.find(l) == visited.end()) {
                    q.push(l);
                    visited.insert(l);
                }
            }

            bool choice = false;
            cout << "Should show more suggestions? ";
            cin >> choice;
            cout << endl;

            if (!choice || q.empty()) done = true;
        }
    }

    vector<Person> getCommonFriends(vector<string> friends) {
        unordered_map<string, int> freq;
        for (auto f : friends) {
            vector<string> res = this->graph.getFriends(f);
            for (auto e : res) freq[e]++;
        }

        vector<pair<int, string>> sortedList;
        for (auto e : freq) sortedList.push_back({ e.second, e.first });
        sort(sortedList.begin(), sortedList.end(), [](const auto& f, const auto& s) {return f.first < s.first; });

        vector<Person> result;
        int cnt = 0;
        for (auto e : sortedList) {
            if (cnt > 3) break;
            cnt++;

            result.push_back(this->graph.get(e.second));
        }

        return result;
    }
};