/*
QUESTION:
The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.
  For example, "ACGAATTCCG" is a DNA sequence.
When studying DNA, it is useful to identify repeated sequences within the DNA.
Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.|



APPROACH:
Sliding Window + Hash Map (O(n) time)
Steps:
1.If len(s) < 10, return empty list (no valid substrings).
2.Use a hash map (or dictionary) to count occurrences of each 10-letter substring.
3.Slide a window of size 10 over the string:
    1.Extract substring s[i : i+10].
    2.Increment its count in the map.
4.After traversal, collect all substrings whose count > 1.
5.Return as a list.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Map DNA char to 2-bit value
int code(char c) {
    switch(c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
    return 0; // default (should not happen)
}

// Simple hash set for ints
typedef struct {
    int *data;
    int size;
    int cap;
} IntSet;

IntSet* createSet(int cap) {
    IntSet* set = malloc(sizeof(IntSet));
    set->data = calloc(cap, sizeof(int));
    set->size = 0;
    set->cap = cap;
    for (int i = 0; i < cap; i++) set->data[i] = -1;
    return set;
}

int hash(IntSet *set, int val) {
    unsigned int h = (unsigned int)val;
    return h % set->cap;
}

int contains(IntSet *set, int val) {
    int idx = hash(set, val);
    while (set->data[idx] != -1) {
        if (set->data[idx] == val) return 1;
        idx = (idx + 1) % set->cap;
    }
    return 0;
}

void insert(IntSet *set, int val) {
    int idx = hash(set, val);
    while (set->data[idx] != -1 && set->data[idx] != val) {
        idx = (idx + 1) % set->cap;
    }
    if (set->data[idx] == -1) {
        set->data[idx] = val;
        set->size++;
    }
}

char** findRepeatedDnaSequences(char* s, int* returnSize) {
    int len = strlen(s);
    *returnSize = 0;
    if (len < 10) return NULL;

    int L = 10;
    int bitmask = (1 << (2 * L)) - 1; // 20 bits for 10 chars
    int hashVal = 0;

    // Hash sets for seen and repeated hashes
    IntSet *seen = createSet(len * 2);
    IntSet *repeat = createSet(len * 2);

    // Output list
    char **result = malloc(len * sizeof(char*));

    // Build first window
    for (int i = 0; i < L; i++) {
        hashVal = (hashVal << 2) | code(s[i]);
    }
    insert(seen, hashVal);

    // Slide the window
    for (int i = L; i < len; i++) {
        // shift left by 2 bits, add new char, mask to 20 bits
        hashVal = ((hashVal << 2) | code(s[i])) & bitmask;

        if (contains(seen, hashVal)) {
            if (!contains(repeat, hashVal)) {
                insert(repeat, hashVal);
                char *seq = malloc(L + 1);
                strncpy(seq, s + i - L + 1, L);
                seq[L] = '\0';
                result[*returnSize] = seq;
                (*returnSize)++;
            }
        } else {
            insert(seen, hashVal);
        }
    }

    free(seen->data); free(seen);
    free(repeat->data); free(repeat);

    return result;
}
