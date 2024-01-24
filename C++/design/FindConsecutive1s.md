# Find Consecutive 1s by turning k zeros to 1

*Given an array of 0s and 1s. find maximum no of consecutive 1s. If you have given chance to flip a bit to 1 such that it maximises the consecutive 1s. find out that flipped bit and after flipping that bit maximum no of consecutive 1s. Above question but you have options to flip k bits.*

```cpp
int zc=0,l=0,max=0;
for(int i=0;i<nums.length;i++){

	if(nums[i]==0)
		zc++;
	while(zc>k){
		if(nums[l++]==0)
			zc--;
	}
	max=Math.max(max,i-l+1);
}
```