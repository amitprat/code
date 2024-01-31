#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=17686666
char * CreateEmptyString(int len);

function should return an pointer to an empty string of length len
*/

class CreateEmptyString {
   public:
    char* createEmptyString(int len) {
        if (len < 0) return nullptr;

        char* ptr = (char*)malloc(len + 1);
        memset(ptr, 0, len + 1);

        return ptr;
    }
};