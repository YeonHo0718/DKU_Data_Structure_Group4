#ifndef _MATRIX_H_
#define _MATRIX_H_

/* ============================================================
 * matrix.h  — common.h 위에 올라가는 행렬 연산 선언
 *             (C++ Matrix 클래스 + C 스타일 행렬 연산 함수)
 * ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif
#include "common.h"
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <string>

/* ============================================================
 * Matrix 클래스: common.c 의 array()/freeArray() 를 내부적으로
 *               사용하는 C++ 래퍼 (1-Gobhagi 모듈라 설계 계승)
 * ============================================================ */
class Matrix {
public:
    int   rows, cols;
    int **data;          /* common.c 의 array() 로 할당 */

    Matrix( int r, int c );
    Matrix( const Matrix& other );
    Matrix& operator=( const Matrix& other );
    ~Matrix();

    /* 초기화 */
    void fillRandom( int lower, int upper );
    void fillZero();

    /* 출력 — common.c 의 printArray() 활용 */
    void print( const char *msg ) const;

    /* ---- Problem 1: 행렬 연산 ---- */
    static Matrix add            ( const Matrix& A, const Matrix& B );
    static Matrix subtract       ( const Matrix& A, const Matrix& B );
    static Matrix multiply       ( const Matrix& A, const Matrix& B );
    static Matrix divideElemWise ( const Matrix& A, const Matrix& B );

    /* ---- Problem 3: 희소·전치 행렬 ---- */
    SparseMatrix *toSparse()  const;   /* 반환값은 freeSparse() 로 해제 */
    Matrix        transpose() const;

    /* ---- 시간 측정 유틸리티 ---- */
    static double measureMs( std::function<void()> func );
};

#endif /* __cplusplus */
#endif /* _MATRIX_H_ */
