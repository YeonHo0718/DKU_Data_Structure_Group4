#include "huffman.h"

/* ============================================================
 * huffman.cpp
 *  - Huffman 트리 구현
 *
 *  알고리즘:
 *   1) 문자 빈도 계산
 *   2) 최소 힙(priority_queue)에 리프 노드 삽입
 *   3) 힙에서 두 노드를 꺼내 부모 내부 노드로 합치는 과정 반복
 *   4) 최종 루트에서 DFS로 각 문자의 비트 코드 생성
 *      (왼쪽 = '0', 오른쪽 = '1')
 * ============================================================ */

#include <cstdio>
#include <queue>
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>

/* ---- 생성자 / 소멸자 ---- */

HuffmanTree::HuffmanTree() : root_(nullptr) {}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

void HuffmanTree::destroy(HuffNode *node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

/* ---- build: 텍스트 → Huffman 트리 ---- */

void HuffmanTree::build(const std::string &text) {
    destroy(root_);
    root_ = nullptr;
    codes_.clear();
    freqs_.clear();

    /* 1) 빈도 계산 */
    for (char c : text) freqs_[c]++;

    if (freqs_.empty()) return;

    /* 2) 최소 힙 구성 */
    auto cmp = [](HuffNode *a, HuffNode *b) {
        if (a->freq != b->freq) return a->freq > b->freq;
        return a->ch > b->ch;  /* 빈도 동일 시 문자 오름차순으로 안정 정렬 */
    };
    std::priority_queue<HuffNode *, std::vector<HuffNode *>, decltype(cmp)> pq(cmp);

    for (auto &p : freqs_)
        pq.push(new HuffNode(p.first, p.second));

    /* 3) 트리 구성 */
    if (pq.size() == 1) {
        /* 단일 문자: 루트에 더미 내부 노드 */
        HuffNode *only = pq.top(); pq.pop();
        root_ = new HuffNode('\0', only->freq, only, nullptr);
    } else {
        while (pq.size() > 1) {
            HuffNode *a = pq.top(); pq.pop();
            HuffNode *b = pq.top(); pq.pop();
            HuffNode *merged = new HuffNode('\0', a->freq + b->freq, a, b);
            pq.push(merged);
        }
        root_ = pq.top();
    }

    /* 4) 코드 생성 */
    generateCodes(root_, "");
}

void HuffmanTree::generateCodes(HuffNode *node, const std::string &prefix) {
    if (!node) return;
    /* 리프 노드 */
    if (!node->left && !node->right) {
        codes_[node->ch] = prefix.empty() ? "0" : prefix;
        return;
    }
    generateCodes(node->left,  prefix + "0");
    generateCodes(node->right, prefix + "1");
}

/* ---- encode: 텍스트 → 비트열 ---- */

std::string HuffmanTree::encode(const std::string &text) const {
    std::string bits;
    bits.reserve(text.size() * 4);
    for (char c : text) {
        auto it = codes_.find(c);
        if (it == codes_.end())
            throw std::runtime_error(
                std::string("인코딩 오류 - 코드 없는 문자: ") + c);
        bits += it->second;
    }
    return bits;
}

/* ---- decode: 비트열 → 텍스트 ---- */

std::string HuffmanTree::decode(const std::string &bits) const {
    if (!root_) return "";
    std::string result;
    HuffNode *cur = root_;
    for (char b : bits) {
        cur = (b == '0') ? cur->left : cur->right;
        if (!cur)
            throw std::runtime_error("디코딩 오류 - 잘못된 비트열");
        if (!cur->left && !cur->right) {
            result += cur->ch;
            cur = root_;
        }
    }
    return result;
}

/* ---- printCodes: 문자별 빈도와 Huffman 코드 출력 ---- */

void HuffmanTree::printCodes() const {
    /* 빈도 내림차순 정렬을 위해 벡터로 변환 */
    std::vector<std::pair<char, int>> sorted(freqs_.begin(), freqs_.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const std::pair<char,int> &a, const std::pair<char,int> &b) {
                  return a.second > b.second;
              });

    printf("  %-8s  %-8s  %-6s  %s\n", "문자", "빈도", "코드길이", "Huffman 코드");
    printf("  %-8s  %-8s  %-6s  %s\n",
           "--------", "--------", "------", "-----------");

    for (auto &p : sorted) {
        char c = p.first;
        const std::string &code = codes_.at(c);
        char display[16];
        if      (c == ' ')  snprintf(display, sizeof(display), "SPACE");
        else if (c == '\n') snprintf(display, sizeof(display), "\\n");
        else if (c == '\t') snprintf(display, sizeof(display), "\\t");
        else                snprintf(display, sizeof(display), "%c", c);

        printf("  %-8s  %-8d  %-6d  %s\n",
               display, p.second, (int)code.size(), code.c_str());
    }
}

/* ---- printWordCodes: 선택된 단어들의 Huffman 코드 출력 ---- */

void HuffmanTree::printWordCodes(const std::string words[], int n) const {
    printf("\n  %-12s  %-10s  %s\n", "단어", "ASCII bits", "Huffman 코드 (문자별)");
    printf("  %-12s  %-10s  %s\n",
           "------------", "----------", "--------------------");

    for (int i = 0; i < n; ++i) {
        const std::string &w = words[i];
        int asciiBits = (int)w.size() * 8;

        std::string huffBits;
        int huffLen = 0;
        bool valid = true;
        for (char c : w) {
            auto it = codes_.find(c);
            if (it == codes_.end()) { valid = false; break; }
            huffBits += it->second + "|";
            huffLen  += (int)it->second.size();
        }
        if (!huffBits.empty()) huffBits.pop_back(); /* trailing '|' 제거 */

        if (valid)
            printf("  %-12s  %-10d  [%d bits] %s\n",
                   w.c_str(), asciiBits, huffLen, huffBits.c_str());
        else
            printf("  %-12s  (코드 없음 - 텍스트에 없는 문자 포함)\n",
                   w.c_str());
    }
}

/* ---- compareASCII: ASCII vs Huffman 크기 비교 ---- */

void HuffmanTree::compareASCII(const std::string &text) const {
    int ascii8  = (int)text.size() * 8;
    int ascii7  = (int)text.size() * 7;
    int huffLen = 0;
    for (char c : text) {
        auto it = codes_.find(c);
        if (it != codes_.end())
            huffLen += (int)it->second.size();
    }

    printf("  문자열 길이          : %d 문자\n", (int)text.size());
    printf("  ASCII-8 코드 크기    : %d bits\n", ascii8);
    printf("  ASCII-7 코드 크기    : %d bits\n", ascii7);
    printf("  Huffman 코드 크기    : %d bits\n", huffLen);
    printf("  압축률 (vs ASCII-8)  : %.1f%%\n",
           (1.0 - (double)huffLen / ascii8) * 100.0);
    printf("  압축률 (vs ASCII-7)  : %.1f%%\n",
           (1.0 - (double)huffLen / ascii7) * 100.0);
}
