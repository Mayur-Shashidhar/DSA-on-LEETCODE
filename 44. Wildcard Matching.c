/*
QUESTION:
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
  '?' Matches any single character.
  '*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).


APPROACH:
Dynamic Programming (DP)
1.We can use a 2D boolean DP table where:
    dp[i][j] means whether s[0..i-1] matches p[0..j-1].
2.The transitions:
    If p[j-1] is ? or equals s[i-1], then:
    dp[i][j] = dp[i-1][j-1]
    If p[j-1] is *, then:
    dp[i][j] = dp[i][j-1] (star matches zero chars) or dp[i-1][j] (star matches one or more chars)
    Otherwise, no match (dp[i][j] = false)
3.We initialize dp = true (empty pattern matches empty string) and handle leading stars in the pattern.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isMatch(char *s, char *p) {
    int m = strlen(s);
    int n = strlen(p);

    // Allocate DP table (m + 1) x (n + 1)
    bool **dp = (bool **)malloc((m + 1) * sizeof(bool *));
    for (int i = 0; i <= m; i++)
        dp[i] = (bool *)calloc(n + 1, sizeof(bool));

    dp[0][0] = true;  // empty pattern matches empty string

    // Initialize first row for patterns with leading '*'
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*')
            dp[0][j] = dp[0][j - 1];
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '?' || p[j - 1] == s[i - 1]) {
                // Match current char or '?'
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                // '*' matches zero chars (dp[i][j-1]) or one+ chars (dp[i-1][j])
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else {
                dp[i][j] = false;
            }
        }
    }

    bool result = dp[m][n];

    // Free memory
    for (int i = 0; i <= m; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}
