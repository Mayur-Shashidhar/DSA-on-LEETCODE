/*
QUESTION:
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.


APPROACH:
Stack Based (O(n) time, O(n) space)
We can use a stack to track indices of unmatched parentheses:
1.Push -1 initially (base index for length calculation).
2.Loop through characters:
    1.If '(' → push index onto stack.
    2.If ')' → pop top:
        1.If stack becomes empty → push current index (new base).
        2.Else → update maxLen as i - stack.top()
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char *s) {
    int len = strlen(s);
    int *stack = malloc((len + 1) * sizeof(int));
    int top = -1;
    int maxLen = 0;

    stack[++top] = -1; // base index

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++top] = i; // push index of '('
        } else {
            top--; // match with '(' if possible
            if (top == -1) {
                // no base → push new base index
                stack[++top] = i;
            } else {
                // valid length from last unmatched ')'
                int currLen = i - stack[top];
                if (currLen > maxLen) maxLen = currLen;
            }
        }
    }

    free(stack);
    return maxLen;
}
