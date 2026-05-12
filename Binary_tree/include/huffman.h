#ifndef HUFFMAN_H
#define HUFFMAN_H

/* ============================================================
 * huffman.h
 *  - Huffman 트리 기반 문자열 압축 ADT 선언
 *  - 빈도 기반 최소 힙으로 트리 구성 → 코드 생성 → 인코딩/디코딩
 * ============================================================ */

#include <string>
#include <map>

/* ---- Huffman 트리 노드 ---- */
struct HuffNode {
    char      ch;     /* 리프 노드의 문자 (내부 노드는 '\0') */
    int       freq;   /* 문자 빈도 */
    HuffNode *left;
    HuffNode *right;

    HuffNode(char c, int f,
             HuffNode *l = nullptr, HuffNode *r = nullptr)
        : ch(c), freq(f), left(l), right(r) {}
};

/* ---- Huffman 트리 클래스 ---- */
class HuffmanTree {
public:
    HuffmanTree();
    ~HuffmanTree();

    /* 입력 텍스트로부터 Huffman 트리 구성 */
    void build(const std::string &text);

    /* 인코딩: 텍스트 → 비트열 */
    std::string encode(const std::string &text) const;

    /* 디코딩: 비트열 → 텍스트 */
    std::string decode(const std::string &bits) const;

    /* 출력 함수 */
    void printCodes()                                          const;
    void printWordCodes(const std::string words[], int n)      const;
    void compareASCII(const std::string &text)                 const;

private:
    HuffNode                   *root_;
    std::map<char, std::string> codes_;   /* 문자 → Huffman 코드 */
    std::map<char, int>         freqs_;   /* 문자 → 빈도 (출력용) */

    void destroy(HuffNode *node);
    void generateCodes(HuffNode *node, const std::string &prefix);
};

#endif /* HUFFMAN_H */
