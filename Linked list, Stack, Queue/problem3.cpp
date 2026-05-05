/*
 * Problem 3: Circular Queue for 20 alphabet characters
 *
 * Functions implemented:
 *   - initQueue()    : initialize the queue
 *   - isFull()       : check if queue is full
 *   - isEmpty()      : check if queue is empty
 *   - enqueue(char)  : insert character at rear
 *   - dequeue()      : remove and return front character
 *   - peek()         : look at front without removing
 *   - printQueue()   : display current queue contents
 *   - size()         : return number of elements
 */

#include <iostream>
#include <stdexcept>

// ── Circular Queue ─────────────────────────────────────────────────────────────
const int MAX_SIZE = 21;  // one slot wasted to distinguish full from empty

struct CircularQueue {
    char data[MAX_SIZE];
    int  front;
    int  rear;
    int  capacity;  // max number of elements = MAX_SIZE - 1 = 20
};

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

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    std::cout << "============================================================\n";
    std::cout << "  Problem 3: Circular Queue (capacity = 20 characters)\n";
    std::cout << "============================================================\n\n";

    CircularQueue q;
    initQueue(q);

    // Test 1: isEmpty on fresh queue
    std::cout << "-- Test 1: isEmpty on fresh queue --\n";
    std::cout << "  isEmpty() = " << (isEmpty(q) ? "true" : "false") << "  (expected: true)\n\n";

    // Test 2: Enqueue A–T (20 characters)
    std::cout << "-- Test 2: Enqueue 'A' through 'T' (20 chars) --\n";
    for (char c = 'A'; c <= 'T'; c++) {
        enqueue(q, c);
        std::cout << "  enqueue('" << c << "')  ";
        std::cout << "size=" << size(q) << "  ";
        std::cout << (isFull(q) ? "[FULL]" : "") << "\n";
    }
    printQueue(q);
    std::cout << "\n";

    // Test 3: Try to enqueue one more (overflow test)
    std::cout << "-- Test 3: Overflow test (enqueue 'U' when full) --\n";
    enqueue(q, 'U');
    printQueue(q);
    std::cout << "\n";

    // Test 4: peek
    std::cout << "-- Test 4: peek() --\n";
    std::cout << "  peek() = '" << peek(q) << "'  (expected: 'A')\n\n";

    // Test 5: Dequeue 5 elements
    std::cout << "-- Test 5: Dequeue 5 elements --\n";
    for (int i = 0; i < 5; i++) {
        char c = dequeue(q);
        std::cout << "  dequeue() = '" << c << "'  size=" << size(q) << "\n";
    }
    printQueue(q);
    std::cout << "\n";

    // Test 6: Enqueue more to wrap around (circular behaviour)
    std::cout << "-- Test 6: Wrap-around enqueue ('U' through 'Y') --\n";
    for (char c = 'U'; c <= 'Y'; c++) {
        enqueue(q, c);
        std::cout << "  enqueue('" << c << "')  size=" << size(q) << "\n";
    }
    printQueue(q);
    std::cout << "\n";

    // Test 7: Dequeue all
    std::cout << "-- Test 7: Dequeue all remaining elements --\n";
    std::cout << "  Order: ";
    while (!isEmpty(q))
        std::cout << dequeue(q) << " ";
    std::cout << "\n";
    std::cout << "  isEmpty() = " << (isEmpty(q) ? "true" : "false") << "\n\n";

    // Test 8: Underflow test
    std::cout << "-- Test 8: Underflow test (dequeue from empty) --\n";
    dequeue(q);

    std::cout << "\nAll tests completed.\n";
    return 0;
}
