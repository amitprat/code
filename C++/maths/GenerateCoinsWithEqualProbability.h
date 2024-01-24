#include "../header.h"

/*
https://careercup.com/question?id=5678403979051008

You are given a function bool rand_bit_p() that returns true with some unknown probability p and false with probability 1 - p.
Write function rand_bit() using rand_bit_p that will return true and false with equal probability (that is, implement a fair coin, given unfair coin)

while(true)
{
        p1 = rand_bit_p();
        p2 = rand_bit_p();

        if(p1 && (!p2)) return true;   // prob = p * (1-p)
        if((!p1) && p2) return false; // prob = (1-p) * p
}
*/