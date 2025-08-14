/*
QUESTION:
Write a function to find the longest common prefix string amongst an array of strings.
If there is no common prefix, return an empty string "".



APPROACH:
We can solve this in multiple ways, but the simplest and efficient approach is:
Horizontal Scanning
1.Assume the first string is the prefix.
2.Compare it with the next string → shrink the prefix until it matches the start of the next string.
3.Repeat for all strings in the array.
4.If at any step the prefix becomes empty → return "".
Time Complexity: O(S) where S is the sum of all characters in all strings (worst case).
Space Complexity: O(1) (no extra data, excluding prefix storage).
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    // Edge case: Empty array
    if (strsSize == 0) return "";

    // Allocate a buffer for the prefix (start with the first string)
    // We make a copy so we can shorten it as needed
    char* prefix = malloc(strlen(strs[0]) + 1);
    if (!prefix) return ""; // If allocation fails, return empty string
    strcpy(prefix, strs[0]);

    // Compare the prefix with each string in the array
    for (int i = 1; i < strsSize; i++) {
        // Reduce the prefix until it matches the beginning of the current string
        while (strncmp(prefix, strs[i], strlen(prefix)) != 0) {
            // Shorten the prefix by 1 character
            prefix[strlen(prefix) - 1] = '\0';
            
            // If prefix becomes empty, no common prefix exists
            if (strlen(prefix) == 0) {
                // Could free(prefix) here before returning ""
                return "";
            }
        }
    }

    // Return the longest common prefix found
    return prefix; 
}
