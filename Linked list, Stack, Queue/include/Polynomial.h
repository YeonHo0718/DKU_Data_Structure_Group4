#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

// ══════════════════════════════════════════════════════════════════════════════
//  (A) Array-based Polynomial
// ══════════════════════════════════════════════════════════════════════════════

struct ArrayPoly {
    std::vector<double> coeffs;  // coeffs[i] = coefficient of x^i

    ArrayPoly();
    ArrayPoly(std::initializer_list<double> c);

    int degree() const;
    void print(const std::string& name) const;
    double evaluate(double x) const;
};

// Resize to match, then add element-wise
ArrayPoly arrayAdd(const ArrayPoly& a, const ArrayPoly& b);
ArrayPoly arraySub(const ArrayPoly& a, const ArrayPoly& b);

// ══════════════════════════════════════════════════════════════════════════════
//  (B) Linked-list Polynomial
// ══════════════════════════════════════════════════════════════════════════════

struct PolyNode {
    double coeff;
    int    degree;
    PolyNode* next;
    PolyNode(double c, int d);
};

struct ListPoly {
    PolyNode* head;  // sorted by degree (descending)

    ListPoly();
    ~ListPoly();
    // Copy constructor
    ListPoly(const ListPoly& o);

    // Insert term in descending degree order
    void insert(double coeff, int degree);
    void print(const std::string& name) const;
    double evaluate(double x) const;
};

ListPoly listAdd(const ListPoly& a, const ListPoly& b);
ListPoly listSub(const ListPoly& a, const ListPoly& b);

#endif // POLYNOMIAL_H
