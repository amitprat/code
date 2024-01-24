#pragma once
#include "../Header.h"

/*
https://www.careercup.com/question?id=5653839983149056

Google On-site in May

Create a class with a collection of integers.
Enable 3 APIs:
void append(int x),
int get(int idx),
void add_to_all(int x)，//add x to all numbers in collection
These methods should run in O(1) time.


Follow-up
In addition, implement
void multiply_to_all(int x)
The same required to run in O(1) time
*/
class DataStructureWithAppendGetAndAddToAll
{
    class AddToAll
    {
        struct Op {
            enum class Type {
                ADD,
                MUL
            };
            Type type;
            int val;
            Op(Type type, int val) :type(type), val(val) {}
            int value(int old) {
                if (type == Type::ADD) return old + val;
                return old * val;
            }
            double revvalue(int old) {
                if (type == Type::ADD) return old - val;
                return (double)old / (double)val;
            }
        };
        vector<int> collection;
        vector<Op> ops;
    public:
        void append(int x) {
            int val = getReverseValue(x);
            collection.push_back(val);
        }

        int get(int index) {
            if (index >= collection.size()) return -1;
            int val = getValue(collection[index]);
            return val;
        }

        void addToAll(int x) {
            ops.push_back({ Op::Type::ADD,x });
        }

        void multiplyToAll(int x) {
            ops.push_back({ Op::Type::MUL,x });
        }

        int getValue(int x)
        {
            int val = x;
            for (auto op : ops) {
                val = op.value(val);
            }

            return val;
        }

        int getReverseValue(int x)
        {
            double val = x;
            for (int i = ops.size() - 1; i >= 0; i--) {
                val = ops[i].revvalue(val);
            }

            return (int)val;
        }
    };
public:
    static void test()
    {
        AddToAll result;
        result.append(2);
        result.append(3);

        result.addToAll(3);
        result.multiplyToAll(5);
        result.addToAll(5);
        result.multiplyToAll(2);

        result.append(2);
        result.append(3);

        cout << result.get(0) << endl;
        cout << result.get(1) << endl;
        cout << result.get(2) << endl;
        cout << result.get(3) << endl;
    }
};