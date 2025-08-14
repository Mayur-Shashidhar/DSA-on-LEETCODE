/*
QUESTION:
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)
P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"
Write the code that will take a string and make this conversion given a number of rows:
string convert(string s, int numRows);
 
APPROACH:
1.If numRows == 1, the zigzag is just the original string.
2.Create an array of strings (or string builders) for each row.
3.Traverse the input string character by character:
   1.Append each character to the current row's string.
   2.Change direction when you reach the top or bottom row.
4.Concatenate all row strings to get the final result.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    int len = strlen(s);

    // Special case: if only one row OR rows >= length, zigzag is just the original string
    if (numRows == 1 || numRows >= len) {
        char* res = (char*)malloc((len + 1) * sizeof(char));
        strcpy(res, s);
        return res;
    }
    
    // Allocate array of strings, one for each row
    char** rows = (char**)malloc(numRows * sizeof(char*));

    // Array to track current length (number of chars) in each row
    int* lengths = (int*)calloc(numRows, sizeof(int)); 

    // Allocate maximum possible size for each row (len + 1 for '\0')
    for (int i = 0; i < numRows; i++) {
        rows[i] = (char*)malloc((len + 1) * sizeof(char));
        rows[i][0] = '\0'; // Start each row as empty string
    }

    int currRow = 0;      // Current row we are filling
    int goingDown = 0;    // Direction flag: 1 → going down, 0 → going up
    
    // Iterate over all characters in s
    for (int i = 0; i < len; i++) {
        int l = lengths[currRow];           // Current length of this row
        rows[currRow][l] = s[i];            // Append char to this row
        rows[currRow][l + 1] = '\0';        // Null-terminate string
        lengths[currRow]++;                 // Update length

        // If at first or last row, reverse the direction
        if (currRow == 0 || currRow == numRows - 1)
            goingDown = !goingDown;

        // Move to next row based on direction
        currRow += goingDown ? 1 : -1;
    }
    
    // Now concatenate all row strings into the final result
    char* result = (char*)malloc((len + 1) * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < numRows; i++) {
        strcat(result, rows[i]);  // Append row to final string
        free(rows[i]);            // Free row buffer
    }

    // Free arrays used for book-keeping
    free(rows);
    free(lengths);

    return result; // Caller should free() after use
}
