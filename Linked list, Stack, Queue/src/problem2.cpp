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
#include "Polynomial.h"

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
