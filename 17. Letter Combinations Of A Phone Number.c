/*
QUESTION:
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.
A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.



APPROACH:
We will use DFS / backtracking:
1.Create a mapping of digits to corresponding letters.
2.Start from the first digit and explore all possible letters for it.
3.Append each letter to the current path and recurse for the next digit.
4.When we reach the end of the digits string, add the built combination to results.
5.Handle empty input by returning an empty list immediately.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mapping digits to corresponding letters on a phone keypad
// Index corresponds to digit character '0'..'9'
char *mapping[] = {
    "",     "",     "abc",  "def",   // 0, 1, 2, 3
    "ghi",  "jkl",  "mno",  "pqrs",  // 4, 5, 6, 7
    "tuv",  "wxyz"                  // 8, 9
};

/**
 * backtrack - Builds all possible combinations by exploring each letter choice.
 *
 * @digits: Input digit string (e.g., "23")
 * @index: Current position in digits we are processing
 * @current: Buffer holding the current partial combination
 * @result: Array of result strings (all combinations)
 * @returnSize: Pointer to integer tracking how many combinations are stored
 */
void backtrack(char *digits, int index, char *current, char **result, int *returnSize) {
    // Base case: if we've processed all digits
    if (digits[index] == '\0') {  
        current[index] = '\0';                 // Null-terminate the current combination
        result[*returnSize] = strdup(current); // Copy the current combination into result array
        (*returnSize)++;                       // Increase number of combinations found
        return;
    }

    // Get the possible letters for the current digit
    char *letters = mapping[digits[index] - '0'];

    // Try each letter for this position
    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i]; // Place chosen letter in current position
        backtrack(digits, index + 1, current, result, returnSize); // Recurse to next digit
    }
}

char **letterCombinations(char *digits, int *returnSize) {
    *returnSize = 0;

    // Edge case: empty input → no combinations
    if (digits == NULL || *digits == '\0') {
        return NULL;
    }

    int len = strlen(digits);

    // Compute the maximum number of combinations possible based on keypad mapping
    int maxComb = 1;
    for (int i = 0; i < len; i++) {
        if (digits[i] == '7' || digits[i] == '9')
            maxComb *= 4;  // '7' and '9' have 4 letters
        else
            maxComb *= 3;  // All other valid digits have 3 letters
    }

    // Allocate result array
    char **result = (char **)malloc(maxComb * sizeof(char *));
    if (!result) return NULL;

    // Allocate buffer for current combination being built
    char *current = (char *)malloc(len + 1);
    if (!current) {
        free(result);
        return NULL;
    }

    // Recursively build combinations
    backtrack(digits, 0, current, result, returnSize);

    free(current); // Buffer no longer needed

    return result; // Caller must free each string and the array itself
}
