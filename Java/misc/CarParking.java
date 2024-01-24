package programs.misc;

/*
https://www.careercup.com/question?id=5687257423937536

Car parking problem. An array given represents actual order of cars need to be parked.
Like for example order is 4,6,5,1,7,3,2,empty. If cars are parked in some order like empty,1,2,3,7,6,4,2.
Some person needs to get them into correct order, list out all instructions to the person to get in correct
order with least number of swaps.
 */
public class CarParking {
}

/*
We can have a linear time run for this.

First consider number of steps needed to swap two element using empty space e, it would take 3 steps

A = e 1 2 3 7 6 4 5
If we swap 2 and 5, steps would be:
1. Swap 2 and e i.e 2 1 e 3 7 6 4 5
2. Swap 5 and e i.e. 2 1 5 3 7 6 4 e
3. Swap 2 and e i.e. e 1 5 3 7 6 4 2

Now for the algo:


Walk the array A,
	1. Compare each element with its position in the original array O
 	  (this can be optimized, so that we don’t need to lookup entire array O every time)
	2. If element is not in proper position, swap it with its original position using empty space
 	3. Do not advance further yet
 	    If (current element not in proper pos){
		goto step 2
	    }
	    else {
		goto next pos
	   }
 */