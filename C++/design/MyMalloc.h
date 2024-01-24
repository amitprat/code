#pragma once
#include "../header.h"
#include <stdlib.h>
#include <string.h>

class MyMalloc {
private:
public:
    void* Malloc(int reqBytes, int alignment) {
        void* p1;
        void* p2;

        /*
        * allocate total memory = requested memory + (alignment-1) + size of void pointer
        */
        int offset = alignment - 1 + sizeof(void*);
        p1 = malloc(reqBytes + offset);
        if (p1 == NULL) { printf("can't allocated memory!"); return NULL; }
        printf("p1:0x%x\n", p1);

        // add offset to pointer
        printf("(size_t)p1 + offset:0x%x\n", (size_t)p1 + offset);
        p2 = (void*)(((size_t)p1 + offset) & ~(alignment - 1));
        printf("p2:0x%x\n", p2);

        // store p1
        ((void**)p2)[-1] = p1;
        printf("p2[-1]:0x%x\n", ((void**)p2)[-1]);
        return p2;
    }

    void Free(void* ptr) {
        free(((void**)ptr)[-1]);
    }
};

class MyMallocTest {
public:
    static void test() {
        MyMalloc obj;
        int* intobj = (int*)obj.Malloc(sizeof(int), 4);
        *intobj = 10;
        cout << *intobj << endl;
        obj.Free(intobj);
    }
};