#pragma once
#pragma warning(disable : 4996)

#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>
#include <mutex>
#include <time.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>
#include <sstream>
using namespace std;

mutex mut;

enum class Designation {
    NONE,
    REPRESENTATIVE,
    MANAGER,
    DIRECTOR
};

class Call
{
public:
    string message;
    int time;
    Call(string message, int time) : message(message), time(time) {}
};

class AvailabilityBoard;
class Employee
{
public:
    int id = 0;
    AvailabilityBoard& board;
    Designation designation;
    int callCapacity = 1;
    int currentActiveCalls = 0;

    Employee(AvailabilityBoard& board, int id) :board(board), designation(Designation::NONE), id(id) {}
    Employee(AvailabilityBoard& board, Designation des, int id) :board(board), designation(des), id(id) {}

    bool accept(Call c);
};

class AvailabilityBoard
{
    using Container = vector<Employee*>;
    using Mapper = map<Designation, Container>;
private:
    Mapper mapper;

public:
    AvailabilityBoard() {
        for (int i = 0; i < 10; i++) mapper[Designation::REPRESENTATIVE].push_back(new Employee(*this, Designation::REPRESENTATIVE, i));
        for (int i = 0; i < 3; i++) mapper[Designation::MANAGER].push_back(new Employee(*this, Designation::MANAGER, 10 * i));
        for (int i = 0; i < 1; i++) mapper[Designation::DIRECTOR].push_back(new Employee(*this, Designation::DIRECTOR, 100 * i));
    }

    void reset(Employee* emp) {
        mapper[emp->designation].push_back(emp);
    }

    void set(Employee* emp) {
        Container c = mapper[emp->designation];
        vector<Employee*>::iterator iter = std::find(c.begin(), c.end(), emp);
        if (iter != c.end()) {
            c.erase(iter);
        }
    }

    Employee* getNextAvailable() {
        for (auto i : mapper) {
            for (auto e : i.second) {
                return e;
            }
        }

        return nullptr;
    }
};

bool Employee::accept(Call c) {
    if (currentActiveCalls >= callCapacity) return false;

    board.set(this);
    std::thread([this, c]() {
        mut.lock();
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Employee " << id << " start processing call: " << c.message << " " << timenow << endl;
        mut.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(c.time));
        currentActiveCalls--;
        mut.lock();
        timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Employee " << id << " finished processing call: " << c.message << " " << timenow << endl;
        mut.unlock();

        board.reset(this);
        }).detach();

        return true;
}

class CallDispatcher
{
private:
    AvailabilityBoard board;

public:
    static void test()
    {
        CallDispatcher obj;
        for (int i = 0; i < 100; i++) {
            obj.dispatchCall(Call(to_string(i), 3));
        }

        std::this_thread::sleep_for(std::chrono::seconds(100));
    }

    bool dispatchCall(Call call) {
        Employee* emp = board.getNextAvailable();
        return emp->accept(call);
    }
};