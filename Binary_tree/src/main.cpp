#include "expr_tree.h"
#include "huffman.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>

/* ============================================================
 * main.cpp
 *  - 자료구조 과제 #4: 산술식의 이진트리와 Huffman 코드의 활용
 *
 *  Problem 1: 연산자 우선순위를 반영하는 산술식 이진트리
 *    - 최소 5개 산술식 (각 5개 이상 연산자, 1개 이상 괄호)
 *    - Infix / Prefix / Postfix / Level-order 출력
 *    - 사용자 입력 산술식도 지원
 *
 *  Problem 2: Huffman 트리를 이용한 문자열 압축
 *    - 50 단어 이상 문단 입력 → Huffman 트리 구성
 *    - 선택된 5개 단어의 Huffman 코드 출력
 *    - ASCII vs Huffman 코드 크기 비교
 *    - 인코딩 → 디코딩 검증
 *    - 사용자가 비트열을 입력받아 디코딩 지원
 * ============================================================ */

/* ============================================================
 * Problem 1
 * ============================================================ */

static void testExprTree(bool interactive) {
    puts("========================================");
    puts(" Problem 1: 산술식의 이진트리 구현");
    puts("========================================\n");

    /* 테스트 산술식 5개
     * 각 식: 5개 이상 연산자 + 1개 이상 괄호 포함 */
    const char *exprs[] = {
        /* 식 1: +,-,*,/,+,- (6 operators, 1 paren) */
        "a + b * c - d / e + (f - g)",

        /* 식 2: +,*,-,/,+,* (6 operators, 2 paren) */
        "(a + b) * (c - d) / e + f * g",

        /* 식 3: *,+,*,-,/,+ (6 operators, 2 paren) */
        "a * (b + c * d) - e / (f + g)",

        /* 식 4: +,*,-,+,*,- (6 operators, 3 paren) */
        "(a + b) * c - (d + e) * (f - g)",

        /* 식 5: /,-,+,*,+,-,* (7 operators, 2 paren) */
        "a / (b - c) + d * (e + f) - g * h"
    };
    const int N = 5;

    ExprTree tree;
    for (int i = 0; i < N; ++i) {
        printf("--------------------------------------------------\n");
        printf("식 %d) %s\n", i + 1, exprs[i]);
        printf("--------------------------------------------------\n");
        tree.build(exprs[i]);
        printf("  Infix     : "); tree.printInfix();
        printf("  Prefix    : "); tree.printPrefix();
        printf("  Postfix   : "); tree.printPostfix();
        printf("  Level     : "); tree.printLevelOrder();
        putchar('\n');
    }

    if (interactive) {
        /* 사용자 입력 산술식 */
        puts("--------------------------------------------------");
        puts(" 사용자 입력 산술식 (빈 줄 입력 시 종료)");
        puts("--------------------------------------------------");

        std::string line;
        while (true) {
            printf("산술식 입력> ");
            fflush(stdout);
            if (!std::getline(std::cin, line) || line.empty()) break;
            try {
                tree.build(line);
                printf("  Infix     : "); tree.printInfix();
                printf("  Prefix    : "); tree.printPrefix();
                printf("  Postfix   : "); tree.printPostfix();
                printf("  Level     : "); tree.printLevelOrder();
                putchar('\n');
            } catch (const std::exception &e) {
                printf("  오류: %s\n\n", e.what());
            }
        }
        putchar('\n');
    }
}

/* ============================================================
 * Problem 2  — 50 단어 이상 문단
 * ============================================================ */

static const std::string DEFAULT_PARAGRAPH =
    "Data structures are fundamental building blocks of computer science "
    "and software engineering. A data structure is a way of organizing "
    "and storing data in a computer so that it can be accessed and "
    "modified efficiently. Different data structures are suited to "
    "different kinds of problems. Some data structures are useful for "
    "simple general problems while others are highly specialized for "
    "specific tasks. Trees are hierarchical data structures with a root "
    "node and subtrees of children. Binary trees are trees where each "
    "node has at most two children. Huffman coding uses binary trees to "
    "compress data efficiently by assigning shorter codes to more "
    "frequent characters and longer codes to less frequent ones.";

/* 단어 수 세기 */
static int countWords(const std::string &s) {
    std::istringstream iss(s);
    std::string word;
    int cnt = 0;
    while (iss >> word) ++cnt;
    return cnt;
}

static void testHuffman(bool interactive) {
    puts("========================================");
    puts(" Problem 2: Huffman 트리 기반 문자열 압축");
    puts("========================================\n");

    std::string paragraph;
    if (interactive) {
        /* 문단 입력 선택 */
        printf("문단을 직접 입력하시겠습니까? (y/n, n=기본 문단 사용): ");
        fflush(stdout);
        std::string choice;
        std::getline(std::cin, choice);

        if (!choice.empty() && (choice[0] == 'y' || choice[0] == 'Y')) {
            puts("50 단어 이상의 문단을 입력하세요.");
            puts("(입력 종료: 빈 줄을 입력하세요)");
            std::string line;
            while (std::getline(std::cin, line) && !line.empty()) {
                if (!paragraph.empty()) paragraph += ' ';
                paragraph += line;
            }
            int wc = countWords(paragraph);
            printf("  입력된 단어 수: %d\n", wc);
            if (wc < 50) {
                printf("  경고: 50 단어 미만입니다. 기본 문단을 사용합니다.\n\n");
                paragraph = DEFAULT_PARAGRAPH;
            }
            putchar('\n');
        } else {
            paragraph = DEFAULT_PARAGRAPH;
            printf("  기본 문단 사용 (%d 단어)\n\n", countWords(paragraph));
        }
    } else {
        paragraph = DEFAULT_PARAGRAPH;
        printf("  기본 문단 사용 (%d 단어)\n\n", countWords(paragraph));
    }

    HuffmanTree ht;
    ht.build(paragraph);

    /* 문자별 빈도와 코드 출력 */
    puts("[ 문자별 빈도와 Huffman 코드 ]");
    ht.printCodes();

    /* 선택된 5개 단어의 코드 출력 */
    puts("\n[ 선택된 5개 단어의 Huffman 코드 ]");
    std::string words[5] = {
        "data", "tree", "binary", "Huffman", "computer"
    };
    ht.printWordCodes(words, 5);

    /* ASCII vs Huffman 크기 비교 */
    puts("\n[ ASCII 코드 vs Huffman 코드 크기 비교 ]");
    ht.compareASCII(paragraph);

    /* (2) 입력받은 글의 Huffman 코드를 출력 */
    puts("\n[ 문단 전체의 Huffman 인코딩 결과 ]");
    std::string encoded = ht.encode(paragraph);
    printf("  전체 비트열 길이 : %d bits\n", (int)encoded.size());
    /* 앞 120비트를 샘플로 출력 (전체 출력 시 가독성 저하) */
    int preview = (int)encoded.size() < 120 ? (int)encoded.size() : 120;
    printf("  비트열 앞 %d bits  : ", preview);
    for (int i = 0; i < preview; ++i) {
        putchar(encoded[i]);
        if ((i + 1) % 8 == 0) putchar(' ');   /* 8비트마다 공백 */
    }
    puts("...\n");

    /* (3) 출력된 코드를 입력받아 문자열을 출력 — 자동 검증 */
    puts("[ Huffman 코드 디코딩 결과 (자동 검증) ]");
    std::string decoded = ht.decode(encoded);
    printf("  복원 문자열 앞 80자 :\n  \"");
    int showLen = (int)decoded.size() < 80 ? (int)decoded.size() : 80;
    for (int i = 0; i < showLen; ++i) putchar(decoded[i]);
    puts("...\"\n");
    printf("  원본 문자열 길이 : %d\n", (int)paragraph.size());
    printf("  복원 문자열 길이 : %d\n", (int)decoded.size());
    printf("  원본 == 복원     : %s\n\n",
           (decoded == paragraph) ? "OK (완전 일치)" : "FAIL (불일치)");

    if (interactive) {
        /* (3) 출력된 코드를 입력받아 문자열을 출력 — 사용자 입력 */
        puts("[ Huffman 비트열 입력 → 디코딩 ]");
        puts("  위 인코딩 결과의 비트열 일부를 붙여넣어 디코딩을 확인할 수 있습니다.");
        puts("  (빈 줄 입력 시 건너뜀)");
        printf("비트열 입력> ");
        fflush(stdout);
        std::string userBits;
        std::getline(std::cin, userBits);

        if (!userBits.empty()) {
            /* 공백 제거: 사용자가 8비트 단위로 띄어쓴 경우 대응 */
            std::string cleanBits;
            for (char c : userBits) {
                if (c == '0' || c == '1') cleanBits += c;
            }
            try {
                std::string userDecoded = ht.decode(cleanBits);
                printf("  입력 비트 수  : %d bits\n", (int)cleanBits.size());
                printf("  디코딩 결과   : \"%s\"\n\n", userDecoded.c_str());
            } catch (const std::exception &e) {
                printf("  디코딩 오류: %s\n\n", e.what());
            }
        } else {
            puts("  (건너뜀)\n");
        }
    }
}

/* ============================================================
 * main
 * ============================================================ */

int main(int argc, char *argv[]) {
    bool interactive = false;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-i") == 0 ||
            std::strcmp(argv[i], "--interactive") == 0) {
            interactive = true;
        }
    }

    puts("============================================================");
    puts(" 자료구조 과제 #4: 산술식의 이진트리와 Huffman 코드의 활용");
    if (interactive)
        puts(" (대화형 모드: 사용자 입력 활성화)");
    puts("============================================================\n");

    testExprTree(interactive);
    testHuffman(interactive);

    return 0;
}
