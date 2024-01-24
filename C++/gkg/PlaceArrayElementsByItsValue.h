#pragma once
/*
write a program to give an array such that:
1. the data value is from 1 to n
2. the length of it is 2*n
3. the two elements with same value keep the same number distance.
for example, when n = 3, the length of array is 6, the array should be like: 2, 3, 1, 2, 1, 3. there are two elements between "2" pair, and three elements between "3" pair and one element between "1" pair
*/

/*
It can be solved with backtracking algorithm...Try to place values 1 after another in the array after checking that the condition is being satisfied and the array positions are available for this value to be placed. If a value could not be placed anywhere in the array try to backtrack and replace the position of the previous value.

In my simple test it did not work for n=5 and 6 etc...that means such an array could not be constructed for that value of n. Here is my java code
*/

/*
public class SpecialArray {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		createSpecialArray(7);
	}


	public static void createSpecialArray(int n){
		int [] outArr = new int[2*n];
		//place 1
		boolean ret = placeVal(1, outArr, n);
		if(!ret) {
			System.out.println("could not implement the solution.");
		} else{
			System.out.println("Array content is : ");
			for(int val :outArr) {
				System.out.print("  "+val);
			}
		}
	}

	public static boolean placeVal(int val, int [] outArr, int highest ){
		boolean ret = false;
		if(val > highest) {
			return true;
		}
		int i;
		boolean isValid = false;

		for(i= 0; i < outArr.length; i++){
			isValid = i+val+1>=outArr.length?false:(outArr[i]==0 && outArr[i+val+1]==0)?true:false;
			if(isValid) {
				outArr[i] = val;
				outArr[i+val+1] = val;
				ret= placeVal(val+1, outArr,highest);
				if(!ret){
					outArr[i] = 0;
					outArr[i+val+1] = 0;
				}else{
					return true;
				}
			}
		}

		return false;
	}
}
*/

/*
Output: for N= 7
Array content is :
1 7 1 2 5 6 2 3 4 7 5 3 6 4
*/

/*
For one who would like to use C++.


bool idistant_internal(std::vector<int>& arr, int curr) {
	if (curr == 0) return true;
	for (int pos = 0; pos < (int)arr.size() - curr - 1; ++pos) {
		if (arr[pos] == 0 && arr[pos + curr + 1] == 0) {
			arr[pos] = arr[pos + curr + 1] = curr;
			if (idistant_internal(arr, curr - 1)) return true;
			arr[pos] = arr[pos + curr + 1] = 0;
		}
	}
	return false;
}

std::vector<int> idistant(int n) {
	std::vector<int> res(2*n);
	if (idistant_internal(res, n)) return res;
	return {};
}
*/