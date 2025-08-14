/*
QUESTION:
Given a string s, return the longest palindromic substring in s.


APPROACH:
Expand Around Center
A palindrome mirrors around its center.
If we try each character as a center and expand outward (both odd length and even length), we can find all possible palindromes.
Steps:
1.Loop through each position in the string.
2.Expand outward for:
    1.Odd length center (left = i, right = i)
    2.Even length center (left = i, right = i+1)
3.If the palindrome length from expansion is longer than the best found so far, update start and max length.
4.Return s[start .. start+maxLen-1].
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For malloc()

int expandFromCenter(char *s, int left, int right) {
    int n = strlen(s);

    // Expand as long as left and right are valid indices and characters match
    while (left >= 0 && right < n && s[left] == s[right]) {
        left--;
        right++;
    }

    // When loop exits, left & right are one step outside the valid palindrome bounds
    return right - left - 1; // Length of the palindrome
}

char* longestPalindrome(char *s) {
    int n = strlen(s);
    if (n == 0) return ""; // Empty string case

    int start = 0;   // Start index of the longest palindrome found so far
    int maxLen = 1;  // Max length found so far (at least 1 char palindrome exists)

    // Iterate over each character as potential center
    for (int i = 0; i < n; i++) {
        // Odd-length palindrome (center at i)
        int len1 = expandFromCenter(s, i, i);

        // Even-length palindrome (center between i and i+1)
        int len2 = expandFromCenter(s, i, i + 1);

        // Pick the longer palindrome length
        int len = (len1 > len2) ? len1 : len2;

        // If found palindrome is longer, update start and maxLen
        if (len > maxLen) {
            maxLen = len;
            start = i - (len - 1) / 2; 
            // Formula shifts the start back to the actual beginning
        }
    }

    // Allocate memory for result + terminating null
    char *res = (char*)malloc((maxLen + 1) * sizeof(char));

    // Copy the palindrome substring into result
    strncpy(res, s + start, maxLen);
    res[maxLen] = '\0'; // Null-terminate

    return res; // Caller must free() this
}
