#pragma once
#include "../header.h"

/*
https://www.careercup.com/question?id=6497025214382080

Replace element of an Array with nearest bigger number at right side of the Array in O(n)
For example if the input Array is
7, 5, 6, 3, 4, 1, 2, 9, 11
output array should be
9, 6, 9, 4, 9, 2, 9, 11, 11


for( i = N-1; i>=0; i-- )  
{
    while( !S.isEmpty && a[i] >= S.checkTop() )  //try to find > a[i] element
        S.pop();

    if( S.isEmpty ) 
        result[i]= INF;  //nothing > a[i] to right  (or use a[i] instead of INF) 
    else
        result[i]= S.checkTop();    //this was > a[i] to right
 
    S.push(a[i]);  
}
*/
class BiggerElementOnRightSideInArray {

};