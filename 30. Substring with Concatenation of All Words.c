/*
QUESTION:
You are given a string s and an array of strings words. All the strings of words are of the same length.
A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.
    For example, if words = ["ab","cd","ef"], then "abcdef", "abefcd", "cdabef", "cdefab", "efabcd", and "efcdab" are all concatenated strings. "acdbef" is not a concatenated string because it is not the concatenation of any permutation of words.
Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.



APPROACH:
Sliding Window + Hash Map
Since all words have the same length, we can solve this efficiently by:

Key points:
1.Let
  wordLen = length of each word
  numWords = length of words array
  windowLen = wordLen * numWords
→ Any valid substring must have length = windowLen.
2.Build a frequency map (wordCount) that counts how many times each word appears in words.
3.For each possible word alignment within the string s (i.e., starting from offsets 0 to wordLen-1):
  1.Use a sliding window of length windowLen moving in steps of wordLen.
  2.Maintain a map seenCount to track words seen in the current window.
  3.If we see a word NOT in wordCount → reset window and start again after this word.
  4.If we see a word too many times (seen > expected) → shrink the window from the left until it's valid.
  5.When matchedWords == numWords → record the start index.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple array-based hashmap struct for small datasets
typedef struct {
    char **keys; // words
    int *vals;   // counts
    int size;    // current key count
} HashMap;

// Return index of key in map or -1
int findKey(HashMap *map, char *key) {
    for (int i = 0; i < map->size; i++)
        if (strcmp(map->keys[i], key) == 0)
            return i;
    return -1;
}

// Insert new key or add to count
void insertKey(HashMap *map, char *key, int val) {
    int idx = findKey(map, key);
    if (idx == -1) {
        map->keys[map->size] = key;
        map->vals[map->size] = val;
        map->size++;
    } else {
        map->vals[idx] += val;
    }
}

// Find starting indices of substrings that are concatenation of all words
int* findSubstring(char *s, char **words, int wordsSize, int *returnSize) {
    *returnSize = 0;
    if (wordsSize == 0) return NULL;

    int wordLen = strlen(words[0]);
    int totalLen = strlen(s);
    int windowLen = wordLen * wordsSize;
    if (totalLen < windowLen) return NULL;

    // Build frequency map for given words
    HashMap wordMap;
    wordMap.size = 0;
    wordMap.keys = malloc(wordsSize * sizeof(char*));
    wordMap.vals = calloc(wordsSize, sizeof(int));
    for (int i = 0; i < wordsSize; i++)
        insertKey(&wordMap, words[i], 1);

    int *result = malloc(totalLen * sizeof(int));

    // Try each starting offset within a word length
    for (int offset = 0; offset < wordLen; offset++) {
        int left = offset, count = 0;

        HashMap seen;
        seen.size = 0;
        seen.keys = malloc(wordsSize * sizeof(char*));
        seen.vals = calloc(wordsSize, sizeof(int));

        // Expand window step by step
        for (int right = offset; right + wordLen <= totalLen; right += wordLen) {
            char *word = strndup(s + right, wordLen);
            int idx = findKey(&wordMap, word);

            if (idx != -1) {
                // Found target word, record in seen
                int pos = findKey(&seen, word);
                if (pos == -1) {
                    seen.keys[seen.size] = word;
                    seen.vals[seen.size] = 1;
                    pos = seen.size;
                    seen.size++;
                } else {
                    seen.vals[pos]++;
                    free(word);
                }
                count++;

                // Shrink from left if this word count is too high
                while (seen.vals[pos] > wordMap.vals[idx]) {
                    char *leftWord = strndup(s + left, wordLen);
                    int leftPos = findKey(&seen, leftWord);
                    seen.vals[leftPos]--;
                    free(leftWord);
                    left += wordLen;
                    count--;
                }

                // All words matched — record index
                if (count == wordsSize) {
                    result[*returnSize] = left;
                    (*returnSize)++;
                }
            } else {
                // Not a target word — reset window
                for (int k = 0; k < seen.size; k++)
                    free(seen.keys[k]);
                seen.size = 0;
                memset(seen.vals, 0, wordsSize * sizeof(int));
                count = 0;
                left = right + wordLen;
                free(word);
            }
        }

        // Free window hashmap memory
        for (int k = 0; k < seen.size; k++)
            free(seen.keys[k]);
        free(seen.keys);
        free(seen.vals);
    }

    // Free target map memory
    free(wordMap.keys);
    free(wordMap.vals);

    return result;
}
