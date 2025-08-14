/* OUESTION:
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order, and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

APPROACH:
1.Initialize a dummy head node to simplify list building.
2.Keep two pointers: one for each linked list (l1, l2).
3.Maintain a carry variable for sums greater than 9.
4.In each step:
    1.Get the value from l1 and l2 (or 0 if one list is shorter).
    2.Sum them with the carry.
    3.Create a new node with sum % 10.
    4.Update carry to sum / 10.
5.After processing both lists, if there's a remaining carry, add a new node for it.
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list:
 * struct ListNode {
 *     int val;               // Value of the current node (a digit)
 *     struct ListNode *next; // Pointer to the next node
 * };
 */


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;      // Dummy head to simplify result list construction
    dummy.next = NULL;          // Start with an empty list
    struct ListNode *tail = &dummy; // Tail pointer to append nodes easily
    int carry = 0;              // Carry for values over 9

    // Continue looping while there are still nodes to process or a carry exists
    while (l1 != NULL || l2 != NULL || carry > 0) {
        int sum = carry;        // Start sum with the carry from the previous step

        // Add value from l1, if available
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;      // Move to the next node
        }

        // Add value from l2, if available
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;      // Move to the next node
        }

        // Determine the new carry (will be 1 if sum >= 10)
        carry = sum / 10;

        // Create a new node with the digit value (sum modulo 10)
        struct ListNode* newNode = malloc(sizeof(struct ListNode));
        newNode->val = sum % 10;
        newNode->next = NULL;

        // Append the new node to the result list
        tail->next = newNode;
        tail = newNode; // Move the tail pointer forward
    }

    // Return the next node of dummy (actual head of the result list)
    return dummy.next;
}
