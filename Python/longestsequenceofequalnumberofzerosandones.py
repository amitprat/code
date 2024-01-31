# https://www.careercup.com/question?id=15886674

# Given an array of 0s and 1s, find out:
# 1. all the subsequences where number of 0s = number of 1s
# 2. max length subsequence where number of 0s = number of 1s

# Update:
# We need to find subarrays, not subsequences. Sorry for the confusion.

# Assuming by subsequence you actually meant _subarray_, an O(n) time algorithm is possible.
# Traverse the array from left to right, and maintain a running sum of number of ones - number of zeroes.
# You also have a hashtable keyed on the running sum, and which contains information regarding the number
# of times that running sum appears, and also the leftmost index for which that sum appears.
# Note: Even though the code uses hashtable below, as Eugene pointed out, since the running_sum is between -n and n,
# we can always use an array, guaranteeing O(1) lookups.
# Using this structure, we can compute the answers for both 1 and 2.
# For instance, to compute the number, we check if the running sum appeared before. If it appeared k times before,
# then we get k new sub-arrays with equal number of zeroes and ones.

# The max length uses the left most such idx.
# Here is sample code in python (with random test cases). The O(n) method is named equal_count.

def equal_count(lst):
    bits = [-1,1] # -1 for zero and 1 for one.
    counts = {0: (1,-1)} # hashmap for count and start index
    run_sum, total_count, max_len = 0,0,0
    cur_idx = -1

    for bit in lst:
        cur_idx += 1 # keep track of current index
        run_sum += bits[bit]

        if run_sum in counts:
            c, idx = counts[run_sum] # [count, last position - index]
            total_count += c # keep track of all subsequences

            if cur_idx - idx > max_len: # keep track of max_len of subsequences where number of zeros == number of ones
                max_len = cur_idx - idx

            counts[run_sum] = c+1, idx
        else:
            counts[run_sum] = 1, cur_idx
    return total_count, max_len    


def equal_count_brute(lst):
    n = len(lst)
    total_count, max_len = 0,0

    for i in range(0,n):
        for j in range(i+1, n+1):
            count = sum (map (lambda x: -1 if x == 0 else 1, lst[i:j]))
            if count == 0:
                total_count += 1
                if j-i  > max_len:
                    max_len = j-i
                    
    return total_count, max_len            


def main():
    lsts = [[0], [1], [1,1], [1,0], [1,0,1],[1,0,0,1], [0,1,0,1,0,1]]
    for lst in lsts:
        print (equal_count(lst), equal_count_brute(lst))
       
if __name__ == "__main__":
    main()