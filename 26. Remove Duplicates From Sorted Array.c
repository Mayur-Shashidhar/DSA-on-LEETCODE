/*
QUESTION:
Given an integer array nums sorted in non-decreasing order, remove the duplicates in-place such that each unique element appears only once. The relative order of the elements should be kept the same. Then return the number of unique elements in nums.
Consider the number of unique elements of nums to be k, to get accepted, you need to do the following things:
  Change the array nums such that the first k elements of nums contain the unique elements in the order they were present in nums initially. The remaining elements of nums are not important as well as the size of nums.
  Return k.



APPROACH:
Two Pointers (O(n) time, O(1) space)
Since the array is sorted, all duplicates are next to each other.
We can use two indices to overwrite duplicates:
1.Pointer i → Points to the position of the last unique element found.
2.Pointer j → Scans the array from left to right.



ALGORITHM:
Start i = 0
For each j from 1 to n-1:
  If nums[j] != nums[i] → found a new unique element:
    Move i++
    Set nums[i] = nums[j]
Return i + 1 as the count k (since i is index-based)
*/

#include<stdio.h>
#include<stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) return 0;  // No elements, return length 0

    int i = 0; // Slow pointer: index for writing unique elements

    // Fast pointer `j` scans through all elements
    for (int j = 1; j < numsSize; j++) {
        // If current number is different from the last unique one
        if (nums[j] != nums[i]) {
            i++;               // Move slow pointer forward
            nums[i] = nums[j]; // Copy unique element into position i
        }
    }

    // i is the index of the last unique element,
    // so length = i + 1
    return i + 1;
}
