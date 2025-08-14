/*
QUESTION:
Given an integer numRows, return the first numRows of Pascal's triangle.
In Pascal's triangle, each number is the sum of the two numbers directly above.
*/

#include <stdio.h>
#include <stdlib.h>

// Generate Pascal's Triangle
int** generate(int numRows, int* returnSize, int** returnColumnSizes) {
    *returnSize = numRows;

    // Allocate space for return arrays
    int **triangle = (int **)malloc(numRows * sizeof(int *));
    *returnColumnSizes = (int *)malloc(numRows * sizeof(int));

    for (int i = 0; i < numRows; i++) {
        (*returnColumnSizes)[i] = i + 1; // number of elements in row i
        triangle[i] = (int *)malloc((i + 1) * sizeof(int));

        triangle[i][0] = 1;        // first element is always 1
        triangle[i][i] = 1;        // last element is always 1

        // Fill middle elements (sum of two above)
        for (int j = 1; j < i; j++) {
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        }
    }

    return triangle;
}
