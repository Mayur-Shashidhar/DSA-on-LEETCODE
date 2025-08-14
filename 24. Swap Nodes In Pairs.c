/*
QUESTION:
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)



APPROACH:
Iterative with Dummy Node
We’ll use a dummy node so even if the head changes, it’s easy to return the new head.
Steps:
1.Create a dummy node pointing to head.
2.Use a pointer prev that starts at dummy.
3.While there are at least two nodes ahead:
    
    Let:
    first = prev->next        // first node in pair
    second = prev->next->next // second node in pair
    
    Rearrange:
    prev->next = second
    first->next = second->next
    second->next = first

    Move prev forward by first (the now-second node in the pair).
4.Return dummy->next.
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list:
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* swapPairs(struct ListNode* head) {
    // Dummy node helps handle swaps at the head cleanly
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode *prev = &dummy;

    // Continue while there are at least two nodes to swap
    while (prev->next != NULL && prev->next->next != NULL) {
        // Identify the two nodes to be swapped
        struct ListNode *first = prev->next;
        struct ListNode *second = prev->next->next;

        /**
         * Perform the swap:
         * 
         * Before:
         *  prev -> first -> second -> nextPair
         *
         * After:
         *  prev -> second -> first -> nextPair
         */
        
        // Step 1: Link prev to second
        prev->next = second;

        // Step 2: Link first to the node after second
        first->next = second->next;

        // Step 3: Link second to first
        second->next = first;

        // Move prev to the end of the swapped pair
        prev = first;
    }

    // The dummy’s next now points to the new head
    return dummy.next;
}
