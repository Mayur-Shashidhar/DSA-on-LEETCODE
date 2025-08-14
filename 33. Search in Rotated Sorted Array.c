/*
QUESTION:
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.



APPROACH:
Modified Binary Search
We can still use binary search, but we must account for the rotation.
Steps:
1.Initialize left = 0, right = n-1.
2.While left <= right:
    1.Find middle: mid = (left + right) / 2.
    2.If nums[mid] == target → return mid.
    3.Determine which half is sorted:
        1.If left half is sorted (nums[left] <= nums[mid]):
            1.If target is within [nums[left], nums[mid]), search left half: right = mid - 1.
            2.Else search right half: left = mid + 1.
        2.Else right half is sorted (nums[mid] <= nums[right]):
            1.If target is within (nums[mid], nums[right]], search right half: left = mid + 1.
            2.Else search left half: right = mid - 1.
3.If not found, return -1.
This works because in a rotated sorted array, at least one half is always fully sorted.
*/

#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Found target
        if (nums[mid] == target)
            return mid;

        // Left half is sorted
        if (nums[left] <= nums[mid]) {
            if (target >= nums[left] && target < nums[mid])
                right = mid - 1; // target in left half
            else
                left = mid + 1;  // target in right half
        }
        // Right half is sorted
        else {
            if (target > nums[mid] && target <= nums[right])
                left = mid + 1;  // target in right half
            else
                right = mid - 1; // target in left half
        }
    }
    return -1; // not found
}
