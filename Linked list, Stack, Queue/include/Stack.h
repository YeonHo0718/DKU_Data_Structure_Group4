#ifndef STACK_H
#define STACK_H

#include <stack>
#include <vector>

struct MatchPair {
    int openPos;
    int closePos;
    char openChar;
    char closeChar;
};

// Common Stack class for both Problem 4 and 5
template <typename T>
class Stack {
    std::stack<T> s;
public:
    void push(const T& val) { s.push(val); }
    
    // Pop that returns value (to support OpStack style in problem 5)
    T pop() { 
        T val = s.top(); 
        s.pop(); 
        return val; 
    }
    
    T& top() { return s.top(); }
    const T& top() const { return s.top(); }
    bool empty() const { return s.empty(); }
    int size() const { return (int)s.size(); }
};

#endif // STACK_H
