#pragma once
#include "../header.h"

class Subscriber {
public:
    string name;
    Subscriber(string name) : name(name) {}
    void update(string who, string message) {
        cout << "Listening " << name << "::" << who << " published message " << message << endl;
    }
};

class Publisher {
    string label;
    unordered_map<string, string> map;
    vector<Subscriber> subscribers;
    unordered_map<string, vector<string>> subscriberTopics;
public:
    Publisher(string label) {
        this->label = label;
    }

    void subscribe(Subscriber& sub, const string& topic) {
        subscribers.push_back(sub);
        subscriberTopics.insert({ sub.name,{topic} });
    }

    void unscribe(Subscriber& sub) {

    }

    void notify(Subscriber& who, string topic, string what) {
        for (auto& sub : subscribers) {
            auto topics = subscriberTopics[sub.name];
            if (std::find(topics.begin(), topics.end(), topic) == topics.end()) continue;
            sub.update(who.name, what);
        }
    }
};

class PubSub {
public:
    static void test() {
        Publisher pub1("pub1");
        Subscriber sub1("sub1");
        Subscriber sub2("sub2");
        Subscriber sub3("sub3");

        pub1.subscribe(sub1, "topic1");
        pub1.subscribe(sub2, "topic2");
        pub1.subscribe(sub3, "topic1");

        pub1.notify(sub1, "topic1", "hellow from sub1 on topic1");
        pub1.notify(sub2, "topic2", "hellow from sub2 on topic2");
    }
};