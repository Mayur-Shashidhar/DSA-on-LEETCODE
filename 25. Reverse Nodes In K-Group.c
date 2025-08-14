/*
QUESTION:
Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.
k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.
You may not alter the values in the list's nodes, only nodes themselves may be changed.



APPROACH:
Iterative with Group Reversal
We can solve this in O(n) time using pointer manipulation:
Steps:
1.Count nodes in list to know how many complete groups of k exist.
2.Use a dummy node pointing to head for easier head management after reversal.
3.Keep a pointer prevGroup which points to the node before the current group to reverse.
4.For each complete group:
  Let groupStart = prevGroup->next
  Let groupEnd = prevGroup->next advanced k times
  Reverse the nodes in that group in-place
  Connect:
  prevGroup->next -> new head of reversed group
  end of reversed group -> next group's start
  Move prevGroup to the end of the reversed group.
5.Stop when fewer than k nodes remain.
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

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    // Quick return for trivial cases
    if (!head || k == 1) return head;

    // Step 1: Count total nodes in the list
    int count = 0;
    struct ListNode* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }

    // Step 2: Dummy node before head to handle head changes easily
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prevGroup = &dummy; // Points to node before current group

    // Step 3: Process while there are at least k nodes remaining
    while (count >= k) {
        // Start of the group to reverse
        struct ListNode* curr = prevGroup->next;
        // Next node after curr (will be moved to front during reversal)
        struct ListNode* next = curr->next;

        // Reverse k nodes by repeated front-insert technique
        for (int i = 1; i < k; i++) {
            // Remove 'next' from chain and insert after prevGroup
            curr->next = next->next;         // Skip over 'next'
            next->next = prevGroup->next;    // Point 'next' to group's head
            prevGroup->next = next;          // Move 'next' to front of group
            next = curr->next;               // Advance 'next'
        }

        // Move prevGroup to end of this reversed group
        prevGroup = curr;
        // Reduce count by k — processed one full group
        count -= k;
    }

    // Step 4: Return new head (dummy.next might have changed)
    return dummy.next;
}
