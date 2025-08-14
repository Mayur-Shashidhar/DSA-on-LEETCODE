/*
QUESTION:
A permutation of an array of integers is an arrangement of its members into a sequence or linear order.
  For example, for arr = [1,2,3], the following are all the permutations of arr: [1,2,3], [1,3,2], [2, 1, 3], [2, 3, 1], [3,1,2], [3,2,1].
The next permutation of an array of integers is the next lexicographically greater permutation of its integer. More formally, if all the permutations of the array are sorted in one container according to their lexicographical order, then the next permutation of that array is the permutation that follows it in the sorted container. If such arrangement is not possible, the array must be rearranged as the lowest possible order (i.e., sorted in ascending order).
  For example, the next permutation of arr = [1,2,3] is [1,3,2].
  Similarly, the next permutation of arr = [2,3,1] is [3,1,2].
  While the next permutation of arr = [3,2,1] is [1,2,3] because [3,2,1] does not have a lexicographical larger rearrangement.
Given an array of integers nums, find the next permutation of nums.
The replacement must be in place and use only constant extra memory.


APPROACH:
In-Place O(n)
This is a classical algorithm that works in three steps:
1.Find the pivot index i (rightmost ascending pair)
    Scan from right to left and find the first i such that:
    nums[i] < nums[i+1]
    If no such index exists → array is the last permutation → reverse to make ascending and return.
2.Find swap index j (rightmost element larger than nums[i])
    Again scan from right and find the first index j such that:
    nums[j] > nums[i]
3.Swap nums[i] and nums[j], then reverse the suffix
    Swap the pivot and the found element.
    Reverse the part from i+1 to the end to get the smallest possible suffix.
*/

#include <stdio.h>

// Swap two integers in-place
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Reverse a subarray in-place
void reverse(int* nums, int start, int end) {
    while (start < end) {
        swap(&nums[start], &nums[end]);
        start++;
        end--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    int i = numsSize - 2;

    // Step 1: Find rightmost index i where nums[i] < nums[i+1]
    while (i >= 0 && nums[i] >= nums[i+1]) {
        i--;
    }

    if (i >= 0) { 
        // Step 2: Find rightmost index j > i where nums[j] > nums[i]
        int j = numsSize - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            j--;
        }
        // Step 3: Swap nums[i] and nums[j]
        swap(&nums[i], &nums[j]);
    }

    // Step 4: Reverse suffix starting at i+1
    reverse(nums, i + 1, numsSize - 1);
}
