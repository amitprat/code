#pragma once
/*
Given three arrays A,B,C containing unsorted numbers. Find three numbers a, b, c from each of array A, B, C such that |a-b|, |b-c| and |c-a| are minimum
Please provide as efficient code as you can.
Can you better than this ???
*/

/*
sort all three arrys and take 1st element from each array
a,b,c calculate min ( |a-b|+ |b-c| +c-a| ,ans)
then take next element from min(a,b,c) and then again repeat above step
time -O(nlogn) +O(n)
just think of this as sorting and then merging all 3 arrays and calculating |a-b|+ |b-c| +c-a| for each consecutive triplet..
u ll have the correct ans
*/