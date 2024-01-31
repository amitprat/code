#pragma once
#include "../header.h"

mutex mut;

enum class Designation {
    NONE,
    REPRESENTATIVE,
    MANAGER,
    DIRECTOR
};

class Call {
   public:
    string message;
    int time;
    Call(string message, int time) : message(message), time(time) {}

    string to_string() const {
        stringstream ss;
        ss << "{";
        ss << "message: " << message << ", ";
        ss << "time: " << time << ", ";
        ss << "}";

        return ss.str();
    }
};

class CallCenter;

class Employee {
   public:
    int id = 0;
    Designation designation;
    const int callCapacity = 1;
    atomic<int> currentActiveCalls = 0;

    CallCenter& callCenter;

    Employee(CallCenter& callCenter, int id) : callCenter(callCenter), designation(Designation::NONE), id(id) {}
    Employee(CallCenter& callCenter, Designation des, int id) : callCenter(callCenter), designation(des), id(id) {}

    bool accept(Call c);

    string to_string() {
        stringstream ss;
        ss << "{";
        ss << "id: " << id << ", ";
        ss << "designation: " << static_cast<std::underlying_type<Designation>::type>(designation) << ", ";
        ss << "}";

        return ss.str();
    }
};

class CallCenter {
    using Container = vector<Employee*>;
    using Mapper = map<Designation, Container>;

   private:
    Mapper mapper;
    shared_mutex m;
    using WriteLock = unique_lock<shared_mutex>;
    using ReadLock = shared_lock<shared_mutex>;

   public:
    CallCenter() {
        for (int i = 0; i < 10; i++) mapper[Designation::REPRESENTATIVE].push_back(new Employee(*this, Designation::REPRESENTATIVE, i));
        for (int i = 0; i < 3; i++) mapper[Designation::MANAGER].push_back(new Employee(*this, Designation::MANAGER, 10 + i));
        for (int i = 0; i < 1; i++) mapper[Designation::DIRECTOR].push_back(new Employee(*this, Designation::DIRECTOR, 13 + i));
    }

    void endCall(Employee* emp) {
        mapper[emp->designation].push_back(emp);

        cout << emp->to_string() << " ended the call." << endl;
    }

    void acceptCall(Employee* emp) {
        WriteLock writeLock(m);

        Container& c = mapper[emp->designation];
        vector<Employee*>::iterator iter = std::find_if(c.begin(), c.end(), [emp](const Employee* cur) { return cur->id == emp->id; });
        if (iter != c.end()) {
            c.erase(iter);
            cout << emp->to_string() << " accepted the call." << endl;
        }
    }

    Employee* getNextAvailableRepresentative() {
        ReadLock readLock(m);

        for (auto i : mapper) {
            for (auto e : i.second) {
                cout << "Available representative: " << e->to_string() << endl;
                return e;
            }
            cout << format("No {} is available, escalating call to next level.", static_cast<std::underlying_type<Designation>::type>(i.first)) << endl;
        }

        return nullptr;
    }
};

bool Employee::accept(Call c) {
    if (currentActiveCalls >= callCapacity) return false;

    callCenter.acceptCall(this);
    this->currentActiveCalls++;

    std::thread([this, c]() {
        auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Employee: " << this->to_string() << " start processing call: " << c.to_string() << " at " << timenow << endl;

        // call processing time.
        std::this_thread::sleep_for(std::chrono::seconds(c.time));

        callCenter.endCall(this);
        currentActiveCalls--;
        timenow = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Employee " << this->to_string() << " finished processing call: " << c.to_string() << " at " << timenow << endl;
    }).detach();

    return true;
}

class CallDispatcher {
   private:
    CallCenter callCenter;

   public:
    static void test() {
        CallDispatcher obj;
        for (int i = 0; i < 20; i++) {
            cout << "---------------Dispatching call: " << i << "---------" << endl;
            auto canAccept = obj.dispatchCall(Call(to_string(i), 10));
            assert(canAccept);

            cout << "-----------------------------------------------------" << endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(100));
    }

    bool dispatchCall(Call call) {
        Employee* emp = nullptr;
        do {
            emp = callCenter.getNextAvailableRepresentative();

            if (emp == nullptr) {
                cout << "No available representative at this moment, will be retrying in some time";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } while (emp == nullptr);

        return emp->accept(call);
    }
};