/*
QUESTION:
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
If target is not found in the array, return [-1, -1].
You must write an algorithm with O(log n) runtime complexity.


APPROACH:
Binary Search Twice (O(log n) time)
Steps:
1.findFirst(nums, target):
    1.Binary search that moves right = mid - 1 when nums[mid] == target to continue searching left side.
    2.Returns index of first match (or -1 if not found).
2.findLast(nums, target):
    1.Binary search that moves left = mid + 1 when nums[mid] == target to continue searching right side.
    2.Returns index of last match (or -1 if not found).
3.Return [first, last].
*/

#include <stdio.h>

// Find first index of target
int findFirst(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] >= target) right = mid - 1;
        else left = mid + 1;
        if (nums[mid] == target) ans = mid; // save and go left
    }
    return ans;
}

// Find last index of target
int findLast(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] <= target) left = mid + 1;
        else right = mid - 1;
        if (nums[mid] == target) ans = mid; // save and go right
    }
    return ans;
}

// Main function
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* res = (int*)malloc(2 * sizeof(int));
    res[0] = findFirst(nums, numsSize, target);
    res[1] = findLast(nums, numsSize, target);
    return res;
}
