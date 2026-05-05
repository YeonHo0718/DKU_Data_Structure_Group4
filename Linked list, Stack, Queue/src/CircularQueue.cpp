#include "CircularQueue.h"

// Initialize
void initQueue(CircularQueue& q) {
    q.front    = 0;
    q.rear     = 0;
    q.capacity = MAX_SIZE - 1;  // 20
}

bool isEmpty(const CircularQueue& q) {
    return q.front == q.rear;
}

bool isFull(const CircularQueue& q) {
    return (q.rear + 1) % MAX_SIZE == q.front;
}

int size(const CircularQueue& q) {
    return (q.rear - q.front + MAX_SIZE) % MAX_SIZE;
}

void enqueue(CircularQueue& q, char c) {
    if (isFull(q)) {
        std::cout << "  [ERROR] Queue is FULL! Cannot enqueue '" << c << "'\n";
        return;
    }
    q.rear = (q.rear + 1) % MAX_SIZE;
    q.data[q.rear] = c;
}

char dequeue(CircularQueue& q) {
    if (isEmpty(q)) {
        std::cout << "  [ERROR] Queue is EMPTY! Cannot dequeue.\n";
        return '\0';
    }
    q.front = (q.front + 1) % MAX_SIZE;
    return q.data[q.front];
}

char peek(const CircularQueue& q) {
    if (isEmpty(q)) {
        std::cout << "  [ERROR] Queue is EMPTY! Cannot peek.\n";
        return '\0';
    }
    return q.data[(q.front + 1) % MAX_SIZE];
}

void printQueue(const CircularQueue& q) {
    std::cout << "  Queue [front→rear, size=" << size(q) << "/"
              << q.capacity << "]: ";
    if (isEmpty(q)) { std::cout << "(empty)\n"; return; }
    int i = (q.front + 1) % MAX_SIZE;
    std::cout << "[ ";
    while (i != (q.rear + 1) % MAX_SIZE) {
        std::cout << q.data[i] << " ";
        i = (i + 1) % MAX_SIZE;
    }
    std::cout << "]\n";
}
