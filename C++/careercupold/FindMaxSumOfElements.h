/*
Given N stacks, each stack contains Si elements, find the maximum sum of the M numbers in the N stacks. To get the number of the stack, only supporting get the top number. For example, S=[1,200,1,2,3], if you want to get the number 200, you need choose 3,2,1 first.
EX:
S1=[1,1,100,3]
S2=[2000,2,3,1]
S3=[10,1,4]
the maximum sum of the 3 numbers in the above stacks is 3+100+3=107.
Any better solution for this problem?


Clear problem statement:

We are given n stacks of different sizes. We can perform k pop operations. Each operation can be done on any stack and in any order. The element popped is added to the result. What is the maximum result we can obtain after performing k operations?

EX:
S1=[1,1,100,3]
S2=[2000,2,3,1]
S3=[10,1,4]

k = 3

the maximum sum of the 3 numbers in the above stacks is 3+100+4=107.

for k = 4 the answer would have been 2000 + 2 + 3 + 1
*/

/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <iostream>
#include <vector>
using namespace std;

int findMax(vector<int> v1,vector<int> v2,vector<int> v3,vector<int> res, int index) {
    if(index < 0) return 0;
    if(res[index] != -1) return res[index];
    auto i1=findMax({v1.begin(),v1.end()-1},v2,v3,res,index-1);
    auto i2=findMax(v1,{v2.begin(),v2.end()-1},v3,res,index-1);
    auto i3=findMax(v1,v2,{v3.begin(),v3.end()-1},res,index-1);
    res[index] = max(i1+v1.back(),max(i2+v2.back(),i3+v3.back()));
    return res[index];
}

int findMax(vector<int> v1,vector<int> v2,vector<int> v3,int k) {
    vector<int> v(k,-1);
    return findMax(v1,v2,v3,v,k-1);
}


int main()
{
    vector<int> v1={1,1,100,3};
    vector<int> v2={2000,2,3,1};
    vector<int> v3={1,2001,1,4};
    int k = 4;

    int res = findMax(v1, v2, v3, k);
    cout<<res<<endl;
    
    return 0;
}
