/*
QUESTION:
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.



APPROACH:
Sorting + Two Pointers (O(n²))
We can solve it efficiently with:
1.Sort the array → makes duplicate handling easier and allows two-pointer search.
2.Loop i from 0 → n-3 (fix the first element).
3.Skip duplicates for the first element (avoid repeating same triplet).
4.Use two-pointer technique (left at i+1 and right at n-1) to find pairs that sum to -nums[i].
5.Move pointers:
    1.If sum is less than target → move left forward.
    2.If sum is greater than target → move right backward.
    3.Else → record the triplet and skip duplicates.
6.Continue until all unique triplets are found.
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * cmp - Comparison function for qsort to sort integers in ascending order.
 */
int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0; // Initially no triplets found
    if (numsSize < 3) return NULL; // Fewer than 3 numbers → no triplet possible

    // Sort the array — necessary for the two-pointer technique and duplicate skipping
    qsort(nums, numsSize, sizeof(int), cmp);
    
    // Allocate maximum possible capacity (over-allocated for simplicity)
    int capacity = numsSize * numsSize;
    int **res = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));

    // Iterate over each number, treating nums[i] as the first number of the triplet
    for (int i = 0; i < numsSize - 2; i++) {
        
        // Skip duplicates for the first number
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1;              // Left pointer
        int right = numsSize - 1;      // Right pointer

        // Two-pointer search for remaining two numbers
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                // Allocate memory for a triplet
                res[*returnSize] = (int*)malloc(3 * sizeof(int));
                res[*returnSize][0] = nums[i];
                res[*returnSize][1] = nums[left];
                res[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3; // Each triplet has length 3
                (*returnSize)++;

                // Skip duplicates for left pointer
                while (left < right && nums[left] == nums[left + 1]) left++;
                // Skip duplicates for right pointer
                while (left < right && nums[right] == nums[right - 1]) right--;

                // Move both pointers inward after recording a triplet
                left++;
                right--;
            } 
            else if (sum < 0) {
                // Sum too small → increase by moving left pointer right
                left++;
            } 
            else {
                // Sum too large → decrease by moving right pointer left
                right--;
            }
        }
    }
    return res;
}
