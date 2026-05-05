#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <iostream>

// ── Circular Queue ─────────────────────────────────────────────────────────────
const int MAX_SIZE = 21;  // one slot wasted to distinguish full from empty

struct CircularQueue {
    char data[MAX_SIZE];
    int  front;
    int  rear;
    int  capacity;  // max number of elements = MAX_SIZE - 1 = 20
};

// Initialize
void initQueue(CircularQueue& q);
bool isEmpty(const CircularQueue& q);
bool isFull(const CircularQueue& q);
int size(const CircularQueue& q);
void enqueue(CircularQueue& q, char c);
char dequeue(CircularQueue& q);
char peek(const CircularQueue& q);
void printQueue(const CircularQueue& q);

#endif // CIRCULAR_QUEUE_H
