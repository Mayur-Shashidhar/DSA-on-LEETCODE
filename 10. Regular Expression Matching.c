/*
QUESTION:
Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:
'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).



APPROACH:
Dynamic Programming
We can solve this with 2D DP where:
dp[i][j] means: Does the first i characters of string s match the first j characters of pattern p?
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isMatch(char *s, char *p) {
    int m = strlen(s); // length of string
    int n = strlen(p); // length of pattern

    // Create DP table: dp[i][j] means s[0..i-1] matches p[0..j-1]
    bool dp[m + 1][n + 1];

    // Initialize all to false
    memset(dp, false, sizeof(dp));

    // Empty string matches empty pattern
    dp[0][0] = true; 

    /**
     * Handle patterns like a*, a*b*, a*b*c*, which can match an empty string.
     * For example:
     *  pattern = "a*" → dp[0][2] = true
     *  pattern = "a*b*" → dp[0][4] = true
     */
    for (int j = 2; j <= n; j++) {
        if (p[j - 1] == '*')
            dp[0][j] = dp[0][j - 2];
    }

    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {

            // Case 1: exact char match OR '.' wildcard => match depends on dp[i-1][j-1]
            if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }

            // Case 2: '*' wildcard
            else if (p[j - 1] == '*') {
                /**
                 * '*' can mean:
                 *  1. Zero occurrences of the preceding char → dp[i][j] = dp[i][j-2]
                 *  2. One or more occurrences → if preceding char matches current s[i-1],
                 *     then dp[i][j] |= dp[i-1][j] (extend match by one char)
                 */
                dp[i][j] = dp[i][j - 2]; // zero occurrences

                if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }
    
    // The final answer: does the entire string match the entire pattern?
    return dp[m][n];
}

