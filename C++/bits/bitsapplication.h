#pragma once
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
#include <queue>
#include <bitset>
#include <string>
#include <sstream>
#include <future>
using namespace std;

class BitSet
{
public:
    bool isset(int a, int index) {
        return a & (1 << index);
    }

    int Union(int a, int b) {
        return a | b;
    }

    int insersection(int a, int b) {
        return a & b;
    }

    int substraction(int a, int b) {
        return a & ~b;
    }

    int negation(int a) {
        return ~a;
    }

    int set(int a, int index) {
        a |= 1 << index;
        return a;
    }

    int clear(int a, int index) {
        a &= ~(1 << index);
        return a;
    }

    int extractLastSetBit(int a) {
        a = a & ~(a - 1);
        return a;
    }

    int removeLastSetBit(int a) {
        a = a & ~(a - 1);
        return a;
    }

    int getAllOnes() {
        return ~0;
    }

    bool isPowerOf4(int n) {
        return ~(n & (n - 1)) && (n & 0x55555555);
    }
};