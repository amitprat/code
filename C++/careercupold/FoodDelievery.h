#pragma once
#include "../Header.h"

class FoodDelievery {
public:
    static void test() {
        FoodDelievery obj;
        {
            obj.addRestuarent(new Restaurent(name, type, menu));
        }
        {
            obj.addRestuarent(new Restaurent(name, type, menu));
        }
        {
            obj.addRestuarent(new Restaurent(name, type, menu));
        }
        obj.startServingUsers();
    }
};