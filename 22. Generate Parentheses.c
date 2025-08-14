/*
QUESTION:
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.



APPROACH:
Backtracking (DFS)
A valid parentheses string must satisfy:
  1.We can only place '(' if we still have some left to place.
  2.We can only place ')' if there are more '(' placed already (i.e., right > left condition cannot happen).
So, we use backtracking:
  Keep track of:
    left: how many '(' we have placed so far
    right: how many ')' we have placed so far
Base case: when left == n and right == n → we have a valid combination → store it.
Choices:
    If left < n, we can add '('
    If right < left, we can add ')'
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * backtrack - Recursively builds valid parenthesis combinations.
 *
 * @n: Total number of pairs of parentheses to generate
 * @left: Number of '(' used so far
 * @right: Number of ')' used so far
 * @current: Character buffer holding the partial combination being built
 * @result: Array of strings storing all valid combinations
 * @returnSize: Pointer to an integer tracking the count of generated combinations
 */
void backtrack(int n, int left, int right, char *current, char **result, int *returnSize) {
    // Base case: if both left and right parentheses counts reach n
    if (left == n && right == n) {
        result[*returnSize] = strdup(current); // Store a copy of current combination
        (*returnSize)++;
        return;
    }

    // If we can still add '(' → place it and recurse
    if (left < n) {
        current[left + right] = '('; // Position is determined by total chars placed so far
        backtrack(n, left + 1, right, current, result, returnSize);
    }

    // If we can place ')' without breaking validity → place it and recurse
    if (right < left) { // Can't have more ')' than '(' at any point
        current[left + right] = ')';
        backtrack(n, left, right + 1, current, result, returnSize);
    }
}

char **generateParenthesis(int n, int *returnSize) {
    // Overestimate maximum possible combinations to allocate storage
    // There are actually Catalan(n) combinations, but 4^n is a safe upper bound
    int maxComb = 1;
    for (int i = 0; i < n; i++) maxComb *= 4;

    // Allocate result array
    char **result = (char **)malloc(maxComb * sizeof(char *));
    if (!result) return NULL;

    // Allocate buffer for current combination being constructed
    char *current = (char *)malloc(2 * n + 1); // Each sequence has length 2*n + '\0'
    if (!current) {
        free(result);
        return NULL;
    }
    current[2 * n] = '\0'; // Null terminator for the string

    *returnSize = 0;

    // Start recursive backtracking
    backtrack(n, 0, 0, current, result, returnSize);

    // Current buffer is no longer needed
    free(current);

    return result;
}
