#include "expr_tree.h"

/*
 * expr_tree.cpp  -  산술식 이진트리 구현
 *
 * 파서 문법:
 *   expr   ::= term   { ('+' | '-') term   }
 *   term   ::= factor { ('*' | '/') factor }
 *   factor ::= OPERAND | '(' expr ')'
 *
 * 우선순위: 문법 계층으로 자연 반영.
 * term 이 먼저 묶이므로 mult/div 가 add/sub 보다 강하다.
 * 괄호는 factor 에서 parseExpr() 를 재귀 호출해 처리한다.
 */

#include <cstdio>
#include <cctype>
#include <queue>
#include <stdexcept>

ExprTree::ExprTree() : root(nullptr), pos_(nullptr) {}

ExprTree::~ExprTree() {
    destroy(root);
}

void ExprTree::destroy(BTreeNode *node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void ExprTree::build(const std::string &infix_expr) {
    destroy(root);
    root = nullptr;
    pos_ = infix_expr.c_str();
    root = parseExpr();
}

void ExprTree::skipSpace() {
    while (*pos_ == ' ' || *pos_ == '\t') ++pos_;
}

BTreeNode *ExprTree::parseExpr() {
    skipSpace();
    BTreeNode *left = parseTerm();
    skipSpace();
    while (*pos_ == '+' || *pos_ == '-') {
        char op = *pos_++;
        skipSpace();
        BTreeNode *right = parseTerm();
        left = new BTreeNode(std::string(1, op), left, right);
        skipSpace();
    }
    return left;
}

BTreeNode *ExprTree::parseTerm() {
    skipSpace();
    BTreeNode *left = parseFactor();
    skipSpace();
    while (*pos_ == '*' || *pos_ == '/') {
        char op = *pos_++;
        skipSpace();
        BTreeNode *right = parseFactor();
        left = new BTreeNode(std::string(1, op), left, right);
        skipSpace();
    }
    return left;
}

BTreeNode *ExprTree::parseFactor() {
    skipSpace();
    if (*pos_ == '(') {
        ++pos_;
        BTreeNode *node = parseExpr();
        skipSpace();
        if (*pos_ == ')') ++pos_;
        return node;
    }
    if (!isalnum((unsigned char)*pos_))
        throw std::runtime_error(
            std::string("파서 오류 - 예상치 못한 문자: ") + *pos_);
    std::string val;
    while (isalnum((unsigned char)*pos_)) val += *pos_++;
    return new BTreeNode(val);
}

/* ---- Infix (중위 순회): 연산자 노드에 괄호를 추가 ---- */
void ExprTree::printInfixHelper(BTreeNode *node) const {
    if (!node) return;
    bool isOp = (node->val == "+" || node->val == "-" ||
                 node->val == "*" || node->val == "/");
    if (isOp) {
        putchar('(');
        printInfixHelper(node->left);
        printf(" %s ", node->val.c_str());
        printInfixHelper(node->right);
        putchar(')');
    } else {
        printf("%s", node->val.c_str());
    }
}

void ExprTree::printInfix() const {
    printInfixHelper(root);
    putchar('\n');
}

/* ---- Prefix (전위 순회) ---- */
void ExprTree::printPrefixHelper(BTreeNode *node) const {
    if (!node) return;
    printf("%s ", node->val.c_str());
    printPrefixHelper(node->left);
    printPrefixHelper(node->right);
}

void ExprTree::printPrefix() const {
    printPrefixHelper(root);
    putchar('\n');
}

/* ---- Postfix (후위 순회) ---- */
void ExprTree::printPostfixHelper(BTreeNode *node) const {
    if (!node) return;
    printPostfixHelper(node->left);
    printPostfixHelper(node->right);
    printf("%s ", node->val.c_str());
}

void ExprTree::printPostfix() const {
    printPostfixHelper(root);
    putchar('\n');
}

/* ---- Level-order (레벨 순회, BFS) ---- */
void ExprTree::printLevelOrder() const {
    if (!root) return;
    std::queue<BTreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        BTreeNode *cur = q.front(); q.pop();
        printf("%s ", cur->val.c_str());
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    putchar('\n');
}
