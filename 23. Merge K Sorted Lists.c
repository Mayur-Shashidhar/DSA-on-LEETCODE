/*
QUESTION:
You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.



APPROACH:
Min-Heap / Priority Queue – O(n·log k)
1.Put the head of each list in a min-heap (priority queue) based on node value.
2.Repeatedly pop the smallest node, then push its next node.
3.Very clean and efficient.
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

/**
 * MinHeap data structure to store pointers to list nodes.
 *
 *  - data: array of ListNode* (heap elements)
 *  - size: current number of elements in the heap
 *  - capacity: max elements (initially k, since we push at most one node from each list)
 */
typedef struct {
    struct ListNode **data;
    int size;
    int capacity;
} MinHeap;

/** 
 * heap_swap - Swaps two ListNode* elements in the heap.
 */
void heap_swap(struct ListNode **a, struct ListNode **b) {
    struct ListNode *tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * heap_push - Inserts a ListNode into the heap while maintaining min-heap property.
 *
 * @heap: pointer to MinHeap
 * @node: node to insert
 *
 * Process:
 *  1. Place node at the end of the heap.
 *  2. "Bubble up" until parent is smaller or root is reached.
 */
void heap_push(MinHeap *heap, struct ListNode *node) {
    heap->data[heap->size++] = node;
    int i = heap->size - 1;
    
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent]->val > heap->data[i]->val) {
            heap_swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        } else break;
    }
}

/**
 * heap_pop - Removes and returns the smallest node from the heap.
 *
 * @heap: pointer to MinHeap
 *
 * Process:
 *  1. Take top (index 0) as result.
 *  2. Move last element to index 0.
 *  3. "Bubble down" until children are larger or no children remain.
 */
struct ListNode* heap_pop(MinHeap *heap) {
    if (heap->size == 0) return NULL;
    
    struct ListNode *top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left]->val < heap->data[smallest]->val)
            smallest = left;
        if (right < heap->size && heap->data[right]->val < heap->data[smallest]->val)
            smallest = right;

        if (smallest != i) {
            heap_swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else break;
    }
    return top;
}

/**
 * mergeKLists - Merges k sorted linked lists into a single sorted list using a min-heap.
 *
 * @lists: array of pointers to sorted linked list heads
 * @listsSize: number of linked lists
 *
 * Return: pointer to head of merged sorted list
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;

    // Initialize heap
    MinHeap heap;
    heap.data = malloc(listsSize * sizeof(struct ListNode*)); // holds at most k elements
    heap.size = 0;
    heap.capacity = listsSize;
    
    // Push head of each non-empty list into heap
    for (int i = 0; i < listsSize; i++) {
        if (lists[i])
            heap_push(&heap, lists[i]);
    }

    // Dummy head to simplify list building
    struct ListNode dummy;
    dummy.next = NULL;
    struct ListNode *tail = &dummy;

    // Extract-min and append to merged list
    while (heap.size > 0) {
        struct ListNode *minNode = heap_pop(&heap);
        tail->next = minNode;
        tail = tail->next;

        // Push the next node from the same list into heap
        if (minNode->next)
            heap_push(&heap, minNode->next);
    }

    // Cleanup
    free(heap.data);

    return dummy.next;
}
