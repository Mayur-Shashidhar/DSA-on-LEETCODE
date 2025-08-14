/*
QUESTION:
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.
The algorithm for myAtoi(string s) is as follows:
Whitespace: Ignore any leading whitespace (" ").
Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
Return the integer as the final result.


APPROACH:
1.Skip leading spaces.
2.Check optional sign ('-' or '+').
3.Read digits while ignoring non-digit characters after that.
4.Handle overflow/underflow on the fly
        If number > INT_MAX, return INT_MAX.
    If number < INT_MIN, return INT_MIN.
We’ll do range checking before actually multiplying and adding the next digit to avoid 64-bit operations.
*/

#include <stdio.h>
#include <limits.h>  // For INT_MAX and INT_MIN
#include <ctype.h>   // For isspace() and isdigit()

int myAtoi(char *s) {
    int i = 0;             // Current index in the string
    int sign = 1;          // Sign of the number (+1 or -1)
    long result = 0;       // Store result as long to detect overflow before returning

    // 1. Skip leading whitespace characters
    while (isspace((unsigned char)s[i])) {
        i++;
    }
    
    // 2. Optional '+' or '-' sign
    if (s[i] == '+' || s[i] == '-') {
        if (s[i] == '-') 
            sign = -1;  // Negative number
        i++;
    }
    
    // 3. Convert digits to integer
    while (isdigit((unsigned char)s[i])) {
        int digit = s[i] - '0';

        /**
         * Overflow detection:
         * If result > (INT_MAX - digit) / 10, adding this digit will overflow.
         * This works because:
         *   result * 10 + digit > INT_MAX
         * rearranges to:
         *   result > (INT_MAX - digit) / 10
         */
        if (result > (INT_MAX - digit) / 10) {
            // Return clamped value on overflow
            return sign == 1 ? INT_MAX : INT_MIN;
        }

        // Append digit to result
        result = result * 10 + digit;
        i++;
    }

    // 4. Apply sign and return integer
    return (int)(result * sign);
}
