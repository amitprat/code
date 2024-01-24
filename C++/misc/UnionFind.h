#pragma once
#include "../header.h"

class UnionFind
{
private:
    int* indx;
    int sz = 0;
    int* rank;

public:
    UnionFind(int sz)
    {
        indx = new int[sz];
        rank = new int[sz];
        this->sz = sz;
        for (int i = 0; i < sz; i++) {
            indx[i] = i;
            rank[i] = 0;
        }
    }

    int find(int p)
    {
        while (p != indx[p]) p = indx[p];

        return p;
    }

    bool Union(int a, int b)
    {
        int aRoot = find(a);
        int bRoot = find(b);
        if (aRoot != bRoot)
        {
            if (rank[aRoot] < rank[bRoot]) {
                indx[aRoot] = bRoot;
            }
            else if (rank[bRoot] < rank[aRoot]) {
                indx[bRoot] = aRoot;
            }
            else {
                indx[aRoot] = bRoot;
                rank[bRoot]++;
            }
            return true;
        }
        return false;
    }

    bool Connected(int a, int b)
    {
        return find(a) == find(b);
    }

    string toString(int n)
    {
        stringstream ss;
        for (int i = 0; i < sz; i++) {
            ss << "{" << indx[i] / n << "," << indx[i] % n << "} ";
        }

        return ss.str();
    }
};