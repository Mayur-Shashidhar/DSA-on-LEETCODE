/*QUESTION:
Given a string s, find the length of the longest substring without duplicate characters.

APPROACH:
Sliding Window:
We can solve it in O(n) time using a sliding window and an array/map to store the last index where each character appeared.
Steps:
1.Have two pointers, start (start of current window) and i (current char index).
2.Keep a lookup table (lastIndex for ASCII) storing the last seen position of each char.
3.If the current char was seen inside the current window, move start to lastIndex[ch] + 1.
4.Update lastIndex[ch] to the current index.
5.Track maxLen as the max window length found so far.
*/


#include <stdio.h>
#include <string.h>

int lengthOfLongestSubstring(char *s) {
    int lastIndex[256];  // Array to store last seen index for each possible ASCII character

    // Initialize all last indices to -1 (meaning not seen yet)
    for (int i = 0; i < 256; i++)
        lastIndex[i] = -1;

    int maxLen = 0; // Maximum length found so far
    int start = 0;  // Start index of the current sliding window

    // Iterate over the string character by character
    for (int i = 0; s[i] != '\0'; i++) {
        unsigned char ch = s[i]; // Cast to unsigned char to avoid negative indexing issues

        // If this character was seen inside the current window, move start just after its last occurrence
        if (lastIndex[ch] >= start)
            start = lastIndex[ch] + 1;

        // Update the last seen index of the current character
        lastIndex[ch] = i;

        // Calculate the length of the current window
        int windowLen = i - start + 1;

        // Update maxLen if current window is longer
        if (windowLen > maxLen)
            maxLen = windowLen;
    }

    return maxLen; // Return the maximum length found
}
