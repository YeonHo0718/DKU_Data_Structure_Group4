#include "Polynomial.h"

// ══════════════════════════════════════════════════════════════════════════════
//  (A) Array-based Polynomial
// ══════════════════════════════════════════════════════════════════════════════

ArrayPoly::ArrayPoly() {}
ArrayPoly::ArrayPoly(std::initializer_list<double> c) : coeffs(c) {}

int ArrayPoly::degree() const { return (int)coeffs.size() - 1; }

void ArrayPoly::print(const std::string& name) const {
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

double ArrayPoly::evaluate(double x) const {
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

PolyNode::PolyNode(double c, int d) : coeff(c), degree(d), next(nullptr) {}

ListPoly::ListPoly() : head(nullptr) {}
ListPoly::~ListPoly() {
    while (head) { PolyNode* tmp = head; head = head->next; delete tmp; }
}
// Copy constructor
ListPoly::ListPoly(const ListPoly& o) : head(nullptr) {
    PolyNode* cur = o.head;
    PolyNode** tail = &head;
    while (cur) {
        *tail = new PolyNode(cur->coeff, cur->degree);
        tail = &((*tail)->next);
        cur = cur->next;
    }
}

// Insert term in descending degree order
void ListPoly::insert(double coeff, int degree) {
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

void ListPoly::print(const std::string& name) const {
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

double ListPoly::evaluate(double x) const {
    double result = 0.0;
    PolyNode* cur = head;
    while (cur) {
        result += cur->coeff * std::pow(x, cur->degree);
        cur = cur->next;
    }
    return result;
}

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
