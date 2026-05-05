/*
 * Problem 4: Stack-based Parenthesis Matching
 *
 * For each expression:
 *   1. (((a + b) * c + d - e)/(f + g) - (h + j) * (k - l))/(m - n)
 *   2. (a - b * c) + d - (e - (f - g)/h)/(i * j) - k
 *
 * Output:
 *   - Each matched pair (position of '(' and matching ')')
 *   - Final stack state (should be empty if balanced)
 */

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>

struct MatchPair {
    int openPos;
    int closePos;
    char openChar;
    char closeChar;
};

// Returns matched pairs; also reports mismatches
std::vector<MatchPair> parenthesisMatch(const std::string& expr) {
    std::stack<std::pair<char,int>> stk;   // (char, index)
    std::vector<MatchPair> pairs;
    bool balanced = true;

    std::cout << "  Expression: " << expr << "\n";
    std::cout << "  Positions:  ";
    for (int i = 0; i < (int)expr.size(); i++) {
        if (i < 10) std::cout << i;
        else        std::cout << (char)('0' + i % 10);
    }
    std::cout << "\n\n";

    for (int i = 0; i < (int)expr.size(); i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{') {
            stk.push({c, i});
        } else if (c == ')' || c == ']' || c == '}') {
            if (stk.empty()) {
                std::cout << "  [MISMATCH] Unmatched '" << c << "' at position " << i << "\n";
                balanced = false;
            } else {
                auto [openChar, openPos] = stk.top();
                stk.pop();
                // check matching type
                bool ok = (c == ')' && openChar == '(') ||
                          (c == ']' && openChar == '[') ||
                          (c == '}' && openChar == '{');
                if (!ok) {
                    std::cout << "  [MISMATCH] '" << openChar << "' at " << openPos
                              << " does not match '" << c << "' at " << i << "\n";
                    balanced = false;
                } else {
                    pairs.push_back({openPos, i, openChar, c});
                }
            }
        }
    }

    // Report unmatched open brackets
    while (!stk.empty()) {
        auto [ch, pos] = stk.top(); stk.pop();
        std::cout << "  [MISMATCH] Unmatched '" << ch << "' at position " << pos << "\n";
        balanced = false;
    }

    // Print matched pairs
    std::cout << "  Matched pairs (" << pairs.size() << " total):\n";
    for (auto& p : pairs)
        std::cout << "    '" << p.openChar << "' at pos " << std::setw(2) << p.openPos
                  << "  <-->  '" << p.closeChar << "' at pos " << std::setw(2) << p.closePos << "\n";

    std::cout << "\n  Stack result: " << (balanced ? "BALANCED (stack empty)" : "NOT BALANCED") << "\n";
    return pairs;
}

// ── Visualize matching brackets ───────────────────────────────────────────────
void visualizeMatching(const std::string& expr, const std::vector<MatchPair>& pairs) {
    // Draw connecting arcs below the expression
    std::cout << "\n  Visual:\n";
    std::cout << "  " << expr << "\n";

    // For each nesting level, draw a line row
    int maxDepth = 0;
    std::vector<int> depth(expr.size(), 0);
    {
        int d = 0;
        for (int i = 0; i < (int)expr.size(); i++) {
            if (expr[i] == '(') { depth[i] = d; d++; maxDepth = std::max(maxDepth, d); }
            else if (expr[i] == ')') { d--; depth[i] = d; }
        }
    }

    for (int level = 0; level < std::min(maxDepth, 5); level++) {
        std::string line(expr.size(), ' ');
        for (auto& p : pairs) {
            if (depth[p.openPos] == level) {
                line[p.openPos]  = '(';
                line[p.closePos] = ')';
                for (int k = p.openPos + 1; k < p.closePos; k++)
                    if (line[k] == ' ') line[k] = '-';
            }
        }
        std::cout << "  " << line << "\n";
    }
    std::cout << "\n";
}

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    std::cout << "============================================================\n";
    std::cout << "  Problem 4: Parenthesis Matching using Stack\n";
    std::cout << "============================================================\n\n";

    std::string expr1 = "(((a + b) * c + d - e)/(f + g) - (h + j) * (k - l))/(m - n)";
    std::string expr2 = "(a - b * c) + d - (e - (f - g)/h)/(i * j) - k";

    std::cout << "── Expression 1 ─────────────────────────────────────────\n";
    auto pairs1 = parenthesisMatch(expr1);
    visualizeMatching(expr1, pairs1);

    std::cout << "── Expression 2 ─────────────────────────────────────────\n";
    auto pairs2 = parenthesisMatch(expr2);
    visualizeMatching(expr2, pairs2);

    return 0;
}
