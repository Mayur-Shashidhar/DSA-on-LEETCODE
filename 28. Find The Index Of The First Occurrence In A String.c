/*
QUESTION:
Given two strings needle and haystack, return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.



APPROACH:
Naive Search (Simple, O(n·m))
We can simply check every possible starting position in haystack until:
  The remaining characters are fewer than needle length → stop.
  Compare the substring with needle.
If they match → return index.
If no match found → return -1.
*/

#include <string.h>

int strStr(char *haystack, char *needle) {
    int n = strlen(haystack);  // Length of haystack
    int m = strlen(needle);    // Length of needle

    // If needle is empty, convention is to return 0
    if (m == 0) return 0;

    // Loop over each starting position where needle could fit
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        // Check if substring starting at i matches needle
        while (j < m && haystack[i + j] == needle[j]) {
            j++;
        }
        // If we matched all characters of needle, return current index
        if (j == m) return i;
    }

    // No match found
    return -1;
}
