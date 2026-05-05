/*
 * Problem 2: Polynomial Addition and Subtraction
 *
 * Two representations:
 *   (A) Array-based  : coeffs[i] = coefficient of x^i  (index = degree)
 *   (B) Linked-list  : each node stores (coefficient, degree)
 *
 * Operations: add, subtract, print, evaluate
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

// ══════════════════════════════════════════════════════════════════════════════
//  (A) Array-based Polynomial
// ══════════════════════════════════════════════════════════════════════════════

struct ArrayPoly {
    std::vector<double> coeffs;  // coeffs[i] = coefficient of x^i

    ArrayPoly() {}
    ArrayPoly(std::initializer_list<double> c) : coeffs(c) {}
    // e.g. ArrayPoly({-2, 1, -1, 3.2, 6.7}) → 6.7x^4 + 3.2x^3 - x^2 + x - 2

    int degree() const { return (int)coeffs.size() - 1; }

    void print(const std::string& name) const {
        std::cout << "  " << name << "(x) = ";
        bool first = true;
        for (int i = (int)coeffs.size() - 1; i >= 0; i--) {
            if (coeffs[i] == 0.0) continue;
            if (!first && coeffs[i] > 0) std::cout << " + ";
            else if (coeffs[i] < 0)      std::cout << " - ";
            double val = std::abs(coeffs[i]);
            if (first && coeffs[i] < 0) { std::cout << "-"; }
            if (i == 0)      std::cout << val;
            else if (i == 1) std::cout << val << "x";
            else             std::cout << val << "x^" << i;
            first = false;
        }
        if (first) std::cout << "0";
        std::cout << "\n";
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (int i = (int)coeffs.size() - 1; i >= 0; i--)
            result = result * x + coeffs[i];
        // Horner's method but coeffs[0] is constant term, so:
        // Actually redo: result = sum coeffs[i]*x^i
        result = 0.0;
        double xi = 1.0;
        for (int i = 0; i < (int)coeffs.size(); i++) {
            result += coeffs[i] * xi;
            xi *= x;
        }
        return result;
    }
};

// Resize to match, then add element-wise
ArrayPoly arrayAdd(const ArrayPoly& a, const ArrayPoly& b) {
    int sz = std::max(a.coeffs.size(), b.coeffs.size());
    ArrayPoly result;
    result.coeffs.resize(sz, 0.0);
    for (int i = 0; i < (int)a.coeffs.size(); i++) result.coeffs[i] += a.coeffs[i];
    for (int i = 0; i < (int)b.coeffs.size(); i++) result.coeffs[i] += b.coeffs[i];
    return result;
}

ArrayPoly arraySub(const ArrayPoly& a, const ArrayPoly& b) {
    int sz = std::max(a.coeffs.size(), b.coeffs.size());
    ArrayPoly result;
    result.coeffs.resize(sz, 0.0);
    for (int i = 0; i < (int)a.coeffs.size(); i++) result.coeffs[i] += a.coeffs[i];
    for (int i = 0; i < (int)b.coeffs.size(); i++) result.coeffs[i] -= b.coeffs[i];
    return result;
}

// ══════════════════════════════════════════════════════════════════════════════
//  (B) Linked-list Polynomial
// ══════════════════════════════════════════════════════════════════════════════

struct PolyNode {
    double coeff;
    int    degree;
    PolyNode* next;
    PolyNode(double c, int d) : coeff(c), degree(d), next(nullptr) {}
};

struct ListPoly {
    PolyNode* head;  // sorted by degree (descending)

    ListPoly() : head(nullptr) {}
    ~ListPoly() {
        while (head) { PolyNode* tmp = head; head = head->next; delete tmp; }
    }
    // Copy constructor
    ListPoly(const ListPoly& o) : head(nullptr) {
        PolyNode* cur = o.head;
        PolyNode** tail = &head;
        while (cur) {
            *tail = new PolyNode(cur->coeff, cur->degree);
            tail = &((*tail)->next);
            cur = cur->next;
        }
    }

    // Insert term in descending degree order
    void insert(double coeff, int degree) {
        if (coeff == 0.0) return;
        PolyNode* node = new PolyNode(coeff, degree);
        if (!head || head->degree < degree) {
            node->next = head; head = node; return;
        }
        PolyNode* cur = head;
        while (cur->next && cur->next->degree >= degree) {
            if (cur->next->degree == degree) {
                cur->next->coeff += coeff;
                delete node;
                if (cur->next->coeff == 0.0) {
                    PolyNode* del = cur->next;
                    cur->next = del->next;
                    delete del;
                }
                return;
            }
            cur = cur->next;
        }
        node->next = cur->next;
        cur->next  = node;
    }

    void print(const std::string& name) const {
        std::cout << "  " << name << "(x) = ";
        if (!head) { std::cout << "0\n"; return; }
        PolyNode* cur = head;
        bool first = true;
        while (cur) {
            if (!first && cur->coeff > 0) std::cout << " + ";
            else if (cur->coeff < 0)      std::cout << " - ";
            if (first && cur->coeff < 0)  std::cout << "-";
            double val = std::abs(cur->coeff);
            if (cur->degree == 0)      std::cout << val;
            else if (cur->degree == 1) std::cout << val << "x";
            else                       std::cout << val << "x^" << cur->degree;
            first = false;
            cur = cur->next;
        }
        std::cout << "\n";
    }

    double evaluate(double x) const {
        double result = 0.0;
        PolyNode* cur = head;
        while (cur) {
            result += cur->coeff * std::pow(x, cur->degree);
            cur = cur->next;
        }
        return result;
    }
};

ListPoly listAdd(const ListPoly& a, const ListPoly& b) {
    ListPoly result;
    PolyNode* cur = a.head;
    while (cur) { result.insert(cur->coeff,  cur->degree); cur = cur->next; }
    cur = b.head;
    while (cur) { result.insert(cur->coeff,  cur->degree); cur = cur->next; }
    return result;
}

ListPoly listSub(const ListPoly& a, const ListPoly& b) {
    ListPoly result;
    PolyNode* cur = a.head;
    while (cur) { result.insert( cur->coeff, cur->degree); cur = cur->next; }
    cur = b.head;
    while (cur) { result.insert(-cur->coeff, cur->degree); cur = cur->next; }
    return result;
}

// ══════════════════════════════════════════════════════════════════════════════
//  main
// ══════════════════════════════════════════════════════════════════════════════
int main() {
    std::cout << "============================================================\n";
    std::cout << "  Problem 2: Polynomial Addition & Subtraction\n";
    std::cout << "============================================================\n\n";

    // ── Test polynomials ──────────────────────────────────────────────────────
    // P(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2
    // Q(x) = x^3 + 2x^2 - 3x + 5

    // ── (A) Array-based ───────────────────────────────────────────────────────
    std::cout << "── (A) Array-based Representation ──────────────────────\n";
    ArrayPoly P_arr({-2.0, 1.0, -1.0, 3.2, 6.7});   // index = degree
    ArrayPoly Q_arr({5.0, -3.0, 2.0, 1.0});          // x^3 + 2x^2 - 3x + 5

    P_arr.print("P");
    Q_arr.print("Q");
    std::cout << "\n";

    ArrayPoly PplusQ_arr  = arrayAdd(P_arr, Q_arr);
    ArrayPoly PminusQ_arr = arraySub(P_arr, Q_arr);

    PplusQ_arr .print("P + Q");
    PminusQ_arr.print("P - Q");

    std::cout << "\n  Verification at x = 1:\n";
    std::cout << "    P(1)        = " << P_arr.evaluate(1.0)         << "\n";
    std::cout << "    Q(1)        = " << Q_arr.evaluate(1.0)         << "\n";
    std::cout << "    (P+Q)(1)    = " << PplusQ_arr.evaluate(1.0)    << "\n";
    std::cout << "    (P-Q)(1)    = " << PminusQ_arr.evaluate(1.0)   << "\n";

    std::cout << "\n";

    // ── (B) Linked-list based ─────────────────────────────────────────────────
    std::cout << "── (B) Linked-list Representation ──────────────────────\n";
    ListPoly P_lst, Q_lst;
    // P(x) = 6.7x^4 + 3.2x^3 - x^2 + x - 2
    P_lst.insert(6.7,  4);
    P_lst.insert(3.2,  3);
    P_lst.insert(-1.0, 2);
    P_lst.insert(1.0,  1);
    P_lst.insert(-2.0, 0);
    // Q(x) = x^3 + 2x^2 - 3x + 5
    Q_lst.insert(1.0,  3);
    Q_lst.insert(2.0,  2);
    Q_lst.insert(-3.0, 1);
    Q_lst.insert(5.0,  0);

    P_lst.print("P");
    Q_lst.print("Q");
    std::cout << "\n";

    ListPoly PplusQ_lst  = listAdd(P_lst, Q_lst);
    ListPoly PminusQ_lst = listSub(P_lst, Q_lst);

    PplusQ_lst .print("P + Q");
    PminusQ_lst.print("P - Q");

    std::cout << "\n  Verification at x = 1:\n";
    std::cout << "    P(1)        = " << P_lst.evaluate(1.0)        << "\n";
    std::cout << "    Q(1)        = " << Q_lst.evaluate(1.0)        << "\n";
    std::cout << "    (P+Q)(1)    = " << PplusQ_lst.evaluate(1.0)   << "\n";
    std::cout << "    (P-Q)(1)    = " << PminusQ_lst.evaluate(1.0)  << "\n";

    std::cout << "\n";

    // ── Cross-check: both methods agree ──────────────────────────────────────
    std::cout << "── Cross-check (both representations agree) ─────────────\n";
    for (int x = -2; x <= 2; x++) {
        double a_add = PplusQ_arr.evaluate(x);
        double l_add = PplusQ_lst.evaluate(x);
        double a_sub = PminusQ_arr.evaluate(x);
        double l_sub = PminusQ_lst.evaluate(x);
        std::cout << "  x=" << x
                  << "  (P+Q)_arr=" << std::setw(10) << std::fixed << std::setprecision(2) << a_add
                  << "  (P+Q)_lst=" << std::setw(10) << l_add
                  << "  match=" << (std::abs(a_add - l_add) < 1e-9 ? "YES" : "NO")
                  << "   (P-Q)_arr=" << std::setw(10) << a_sub
                  << "  (P-Q)_lst=" << std::setw(10) << l_sub
                  << "  match=" << (std::abs(a_sub - l_sub) < 1e-9 ? "YES" : "NO")
                  << "\n";
    }
    std::cout << "\n";

    return 0;
}
