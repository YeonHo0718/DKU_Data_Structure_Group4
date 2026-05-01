/*
 * Problem 5: Infix to Postfix Conversion using Stack
 *
 * Algorithm (Shunting-yard):
 *   - Operand   → output immediately
 *   - '('       → push to stack
 *   - ')'       → pop to output until '(' found
 *   - Operator  → pop operators of >= precedence to output, then push
 *
 * Tested with 5+ infix expressions of 5+ operands/operators each.
 */

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>

// ── Stack class for operators ─────────────────────────────────────────────────
class OpStack {
    std::stack<char> s;
public:
    void   push(char c)       { s.push(c); }
    char   pop()              { char c = s.top(); s.pop(); return c; }
    char   top()  const       { return s.top(); }
    bool   empty()const       { return s.empty(); }
    int    size() const       { return (int)s.size(); }
};

// ── Operator precedence ───────────────────────────────────────────────────────
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^')              return 3;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isRightAssoc(char op) {
    return op == '^';
}

// ── Core conversion function ──────────────────────────────────────────────────
std::string infixToPostfix(const std::string& infix) {
    OpStack    stk;
    std::string output;

    for (int i = 0; i < (int)infix.size(); i++) {
        char c = infix[i];

        if (c == ' ') continue;

        // Multi-character operand (letters or digits run)
        if (std::isalnum(c)) {
            if (!output.empty() && output.back() != ' ') output += ' ';
            while (i < (int)infix.size() && std::isalnum(infix[i]))
                output += infix[i++];
            i--;  // loop will increment
            output += ' ';
        }
        else if (c == '(') {
            stk.push(c);
        }
        else if (c == ')') {
            while (!stk.empty() && stk.top() != '(')
                output += stk.pop(), output += ' ';
            if (!stk.empty()) stk.pop();  // remove '('
        }
        else if (isOperator(c)) {
            while (!stk.empty() && stk.top() != '(' &&
                   (precedence(stk.top()) > precedence(c) ||
                    (precedence(stk.top()) == precedence(c) && !isRightAssoc(c)))) {
                output += stk.pop();
                output += ' ';
            }
            stk.push(c);
        }
    }

    // Drain remaining operators
    while (!stk.empty()) {
        output += stk.pop();
        output += ' ';
    }

    // Remove trailing space
    while (!output.empty() && output.back() == ' ') output.pop_back();

    return output;
}

// ── Evaluate postfix (for numeric expressions) ────────────────────────────────
double evalPostfix(const std::string& postfix) {
    std::stack<double> s;
    int i = 0;
    while (i < (int)postfix.size()) {
        if (postfix[i] == ' ') { i++; continue; }

        // Number (possibly multi-digit)
        if (std::isdigit(postfix[i]) || (postfix[i] == '-' && std::isdigit(postfix[i+1]))) {
            double num = 0;
            bool neg = false;
            if (postfix[i] == '-') { neg = true; i++; }
            while (i < (int)postfix.size() && std::isdigit(postfix[i]))
                num = num * 10 + (postfix[i++] - '0');
            s.push(neg ? -num : num);
        } else if (isOperator(postfix[i])) {
            if (s.size() < 2) { i++; continue; }
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            char op = postfix[i++];
            if      (op == '+') s.push(a + b);
            else if (op == '-') s.push(a - b);
            else if (op == '*') s.push(a * b);
            else if (op == '/') s.push(a / b);
            else if (op == '^') {
                double r = 1;
                for (int k = 0; k < (int)b; k++) r *= a;
                s.push(r);
            }
        } else i++;
    }
    return s.empty() ? 0.0 : s.top();
}

// ── main ──────────────────────────────────────────────────────────────────────
int main() {
    std::cout << "============================================================\n";
    std::cout << "  Problem 5: Infix to Postfix Conversion\n";
    std::cout << "============================================================\n\n";

    // 5+ expressions, each with 5+ operators & operands
    struct TestCase { std::string infix; std::string note; };
    std::vector<TestCase> tests = {
        { "a + b * c - d / e",
          "Basic precedence: * and / before + and -" },
        { "(a + b) * (c - d) / e + f",
          "Parentheses override precedence" },
        { "a * b + c * d - e + f / g",
          "Multiple same-level operators" },
        { "((a + b) * c + d - e) / (f + g) - (h + j) * (k - l)",
          "Expression 1 from Problem 4 (left half)" },
        { "(a - b * c) + d - (e - (f - g) / h) / (i * j) - k",
          "Expression 2 from Problem 4" },
        { "a ^ b ^ c + d * e - f",
          "Right-associative exponentiation" },
        { "3 + 4 * 2 - 1",
          "Numeric: result verifiable = 3 + 8 - 1 = 10" },
        { "(3 + 4) * (2 - 1)",
          "Numeric: (7)*(1) = 7" },
        { "2 ^ 3 + 4 * 5 - 6",
          "Numeric: 8 + 20 - 6 = 22" },
    };

    int width = 52;
    std::cout << std::left
              << std::setw(width) << "Infix Expression"
              << "Postfix Expression\n";
    std::cout << std::string(width + 45, '-') << "\n";

    for (auto& t : tests) {
        std::string postfix = infixToPostfix(t.infix);
        std::cout << std::setw(width) << t.infix << postfix << "\n";
        std::cout << "  [" << t.note << "]\n";
        // If all tokens are numeric, also evaluate
        bool allNumeric = true;
        for (char c : t.infix)
            if (std::isalpha(c)) { allNumeric = false; break; }
        if (allNumeric) {
            double result = evalPostfix(postfix);
            std::cout << "  Postfix evaluation result = " << result << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}
