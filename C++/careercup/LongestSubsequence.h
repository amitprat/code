/*
Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7

Sorting is an obvious solution. Can this be done in O(n) time
*/
/*
"""Given an int array which might contain duplicates, find the largest subset of it which form a sequence.
Eg. {1,6,10,4,7,9,5}
then ans is 4,5,6,7
Sorting is an obvious solution. Can this be done in O(n) time"""
*/

def find(arr):
    table = {}
    first = 0
    last = 0
    for i in arr:
        beg = end = i
        if i in table:
            continue
        table[i] = 'EXISTED'
        if i - 1 in table:
            beg = table[i-1]
        if i + 1 in table:
            end = table[i+1]
        table[beg] = end
        table[end] = beg
        if end - beg > last - first:
            first = beg
            last = end
    return list(range(first, last + 1))

arr = [1,6,10,4,7,9,5, 5,8]
            
print(find(arr))