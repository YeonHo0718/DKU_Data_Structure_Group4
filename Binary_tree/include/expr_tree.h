#ifndef EXPR_TREE_H
#define EXPR_TREE_H

/*
 * expr_tree.h
 *  - 산술식 이진트리 ADT 선언
 *  - 연산자 우선순위(mult/div > add/sub)와 괄호를 반영하는
 *    재귀 하강 파서로 트리를 구성한다.
 *
 *  파서 문법 (BNF):
 *    expr   ::= term   { ('+' | '-') term   }
 *    term   ::= factor { ('*' | '/') factor }
 *    factor ::= OPERAND | '(' expr ')'
 */

#include <string>

/* ---- 트리 노드 ---- */
struct BTreeNode {
    std::string  val;
    BTreeNode   *left;
    BTreeNode   *right;

    BTreeNode(const std::string &v,
              BTreeNode *l = nullptr,
              BTreeNode *r = nullptr)
        : val(v), left(l), right(r) {}
};

/* ---- 산술식 이진트리 클래스 ---- */
class ExprTree {
public:
    BTreeNode *root;

    ExprTree();
    ~ExprTree();

    void build(const std::string &infix_expr);

    void printInfix()      const;
    void printPrefix()     const;
    void printPostfix()    const;
    void printLevelOrder() const;

private:
    const char *pos_;

    void       destroy(BTreeNode *node);
    void       printInfixHelper(BTreeNode *node)   const;
    void       printPrefixHelper(BTreeNode *node)  const;
    void       printPostfixHelper(BTreeNode *node) const;

    void       skipSpace();
    BTreeNode *parseExpr();
    BTreeNode *parseTerm();
    BTreeNode *parseFactor();
};

#endif /* EXPR_TREE_H */
