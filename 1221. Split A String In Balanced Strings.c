/*
QUESTION:
Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
Given a balanced string s, split it into some number of substrings such that:
  Each substring is balanced.
Return the maximum number of balanced strings you can obtain.


APPROACH:
Greedy Counting (O(n) time, O(1) space)
Idea:
This works because any time we get equal L and R counts, we can cut here — this maximizes splits.
Keep a running balance:
    +1 for 'R'
    -1 for 'L'
    (or vice versa — just be consistent)
Each time the balance becomes 0, we’ve found one balanced substring, so increment count.
*/

#include <stdio.h>
#include <string.h>

int balancedStringSplit(char * s) {
    int count = 0;    // number of balanced substrings
    int balance = 0;  // net count of R (+1) and L (-1)

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'R')
            balance++;
        else
            balance--;

        // When counts of R and L are equal, split here
        if (balance == 0)
            count++;
    }
    return count;
}
