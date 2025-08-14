/*
QUESTION:
You are given a string num representing a large integer. An integer is good if it meets the following conditions:
It is a substring of num with length 3.
It consists of only one unique digit.
Return the maximum good integer as a string or an empty string "" if no such integer exists.
Note:
A substring is a contiguous sequence of characters within a string.
There may be leading zeroes in num or a good integer.


APPROACH:
1.Iterate through num from index 0 to len(num) - 3.
2.For each position i, check substring num[i : i+3]:
    1.If num[i] == num[i+1] == num[i+2] → it is a good integer.
    2.Track the maximum such substring found so far.
3.Return:
    1.The maximum substring (lexicographically largest, since digits compare as chars correctly)
    2.Or "" if none found.
Why lexicographic comparison works:
    Digits '0'…'9': '9' > '8' … > '0', so comparing "777" with "666" works directly.
*/

#include <string.h>
#include <stdio.h>

char* largestGoodInteger(char* num) {
    // Static buffer to hold result (3 digits + null terminator)
    static char best[4];
    best[0] = '\0';  // Initially no result found

    int len = strlen(num);

    // Iterate up to len - 3 so we can safely check triples [i, i+1, i+2]
    for (int i = 0; i <= len - 3; i++) {
        // Check if this triple has the same digit
        if (num[i] == num[i+1] && num[i] == num[i+2]) {
            // Create a temporary triple string
            char temp[4] = {num[i], num[i], num[i], '\0'};

            // If we haven't stored any triple yet OR current triple is larger lexicographically
            if (best[0] == '\0' || strcmp(temp, best) > 0) {
                strcpy(best, temp); // Update the best triple
            }
        }
    }

    // If no triple found, return empty string
    if (best[0] == '\0')
        return "";

    // Else return the best triple
    return best;
}
