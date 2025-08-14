/*
QUESTION:
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).


APPROACH:
Binary Search on the Smaller Array:
We can think of finding the median as splitting the two arrays into a left half and a right half such that:
1.All elements in the left half are ≤ all elements in the right half
2.The size of the left and right halves differ by at most 1
We can achieve this by:
1.Performing binary search on the smaller array (nums1).
2.Partitioning both arrays.
3.Adjusting the cut.
4.Then:
    If total length is even → median = (max(left1, left2) + min(right1, right2)) / 2
    If odd → median = max(left1, left2)
*/

#include <stdio.h>
#include <limits.h> // For INT_MIN and INT_MAX

double findMedianSortedArrays(int* nums1, int m, int* nums2, int n) {
    
    // Ensure nums1 is the smaller array (to minimize binary search complexity)
    if (m > n) {
        return findMedianSortedArrays(nums2, n, nums1, m);
    }
    
    int low = 0, high = m; // Binary search range over nums1
    int totalLeft = (m + n + 1) / 2; // Number of elements in the left half of merged arrays
    
    while (low <= high) {
        // Partition nums1 into: left1 (size cut1) and right1 (remaining elements)
        int cut1 = (low + high) / 2;
        
        // Partition nums2 into: left2 (size cut2) and right2 (remaining elements)
        int cut2 = totalLeft - cut1;
        
        // Get boundary values for left and right sides, using INT_MIN / INT_MAX for edges
        int left1  = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1]; // Max of left part of nums1
        int left2  = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1]; // Max of left part of nums2
        int right1 = (cut1 == m) ? INT_MAX : nums1[cut1];     // Min of right part of nums1
        int right2 = (cut2 == n) ? INT_MAX : nums2[cut2];     // Min of right part of nums2
        
        // Check if the partition is valid
        if (left1 <= right2 && left2 <= right1) {
            // Found correct partition — now calculate median
            if ((m + n) % 2 == 0) { // Even total length → average of middle two
                return ((double)((left1 > left2 ? left1 : left2) + 
                                 (right1 < right2 ? right1 : right2))) / 2.0;
            } else { // Odd total length → max of left elements
                return (double)(left1 > left2 ? left1 : left2);
            }
        }
        // If left1 is too big, shift cut1 left
        else if (left1 > right2) {
            high = cut1 - 1;
        } 
        // Else shift cut1 right
        else {
            low = cut1 + 1;
        }
    }
    
    // Should never reach here for valid sorted inputs
    return 0.0;
}
