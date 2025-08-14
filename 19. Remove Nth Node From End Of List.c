/*
QUESTION:
Given the head of a linked list, remove the nth node from the end of the list and return its head.


APPROACH:
Two Pointers (One Pass)
We can solve this in O(n) time with two pointers:
1.Create a dummy node pointing to the head (helps when removing the first node).
2.Initialize two pointers: fast and slow, both starting at the dummy node.
3.Move fast forward by n+1 steps so that the gap between fast and slow is n nodes.
4.Move both pointers one step at a time until fast reaches the end.
5.Now, slow->next is the node to remove, so we set: slow->next = slow->next->next
6.Return dummy->next as the new head.
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

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy;       // Dummy node to handle edge cases
    dummy.next = head;

    struct ListNode *fast = &dummy, *slow = &dummy;

    // Move `fast` n+1 steps ahead so there is a gap of n between fast & slow
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    
    // Move both fast and slow until fast reaches end
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }
    
    // slow is now immediately before the node to remove
    struct ListNode* temp = slow->next;         // Node to delete
    slow->next = slow->next->next;              // Bypass the node
    free(temp);                                 // Free memory

    return dummy.next; // Return possibly new head
}

/**
 * createNode - Allocates and initializes a new list node
 */
struct ListNode* createNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

/**
 * printList - Prints a linked list in "val -> val -> ... -> NULL" format
 */
void printList(struct ListNode* head) {
    while (head) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}
