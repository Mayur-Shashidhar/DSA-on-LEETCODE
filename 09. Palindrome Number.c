/*
QUESTION:
Given an integer x, return true if x is a palindrome, and false otherwise.



APPROACH:
1.If x < 0 or (x % 10 == 0 and x != 0) → return false.
2.Reverse the last half of the number:
    Pop the last digit from x
    Push it into reversedHalf
    Stop when x <= reversedHalf.
3.At the end:
    If total digits are even → x == reversedHalf
    If total digits are odd → x == reversedHalf / 10 (middle digit ignored)
*/

#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
    
    // If negative OR ends with 0 but is not 0 → not a palindrome
    if (x < 0 || (x % 10 == 0 && x != 0))
        return false;

    int reversedHalf = 0; // Stores reversed digits of the second half of x

    /**
     * We only reverse digits until reversedHalf ≥ x.
     * At that point, we have processed half or more of the digits.
     */
    while (x > reversedHalf) {
        reversedHalf = reversedHalf * 10 + (x % 10); // Add last digit to reversedHalf
        x /= 10;  // Remove last digit from x
    }
    
    /**
     * For even number of digits: x == reversedHalf
     * For odd number of digits: x == reversedHalf / 10
     *   Example: 12321
     *     -> After loop: x = 12, reversedHalf = 123
     *     -> Middle digit (3) doesn't matter, so divide reversedHalf by 10
     */
    return (x == reversedHalf) || (x == reversedHalf / 10);
}
