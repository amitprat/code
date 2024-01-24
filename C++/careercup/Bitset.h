#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
using namespace std;

class Bitmap
{
private:
    vector<int> bitset;
    int sz;

public:
    Bitmap() { sz = 4 * 8; }
    void setTrue(int index)
    {
        resize(index);
        set(bitset[pos(index)], offset(index), true);
    }
    void setFalse(int index)
    {
        resize(index);
        set(bitset[pos(index)], offset(index), false);
    }
    void setAllTrue()
    {
        for (int i = 0; i < bitset.size(); i++)
        {
            bitset[i] = -1;
        }
    }
    void setAllFalse()
    {
        for (int i = 0; i < bitset.size(); i++)
        {
            bitset[i] = 0;
        }
    }
    bool getIndex(int index)
    {
        return bitset[pos(index)] & (1 << offset(index));
    }
    string to_string()
    {
        stringstream ss;
        for (auto e : bitset)
        {
            ss << to_bin(e) << " ";
        }
        return ss.str();
    }
    void toggle(int index)
    {
        resize(index);
        toggle(bitset[pos(index)], offset(index));
    }

private:
    void resize(int index)
    {
        while (bitset.size() < pos(index) + 1)
        {
            bitset.push_back(0);
        }
    }
    void set(int &elem, int index, bool state)
    {
        if (state)
        {
            elem |= (1 << index);
        }
        else
        {
            elem &= ~(1 << index);
        }
    }
    void toggle(int &elem, int off)
    {
        elem ^= (1 << off);
    }
    string to_bin(int e)
    {
        string cur;
        for (int i = sz - 1; i >= 0; i--)
        {
            if (e & (1 << i))
                cur += "1";
            else
                cur += "0";
            if (i % 8 == 0)
                cur += " ";
        }
        return cur;
    }
    int pos(int index) { return index / sz; }
    int offset(int index) { return index % sz; }
};

int main()
{
    Bitmap obj;
    for (int i = 0; i < 21; i++)
    {
        obj.setTrue(i);
        cout << "state = " << obj.to_string() << endl;
        cout << "Index State = " << obj.getIndex(i) << endl;

        obj.setFalse(i);
        cout << "state = " << obj.to_string() << endl;
        cout << "Index State = " << obj.getIndex(i) << endl;

        obj.setAllTrue();
        cout << "state = " << obj.to_string() << endl;

        obj.setAllFalse();
        cout << "state = " << obj.to_string() << endl;
    }
    return 0;
}
