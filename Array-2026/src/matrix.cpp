#include "matrix.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

/* ============================================================
 * matrix.cpp
 *  — common.c 의 array()/freeArray() 를 직접 호출하여
 *    메모리를 관리함으로써 1-Gobhagi 모듈라 설계를 계승한다.
 * ============================================================ */

/* ---- 생성자: common.c 의 array() 호출 ---- */
Matrix::Matrix( int r, int c ) : rows(r), cols(c) {
    data = ::array( r, c );      /* 1-Gobhagi common.c */
}

/* ---- 복사 생성자 ---- */
Matrix::Matrix( const Matrix& o ) : rows(o.rows), cols(o.cols) {
    data = ::array( rows, cols );
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            data[i][j] = o.data[i][j];
}

/* ---- 대입 연산자 ---- */
Matrix& Matrix::operator=( const Matrix& o ) {
    if( this == &o ) return *this;
    ::freeArray( data, rows );   /* 1-Gobhagi common.c */
    rows = o.rows; cols = o.cols;
    data = ::array( rows, cols );
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            data[i][j] = o.data[i][j];
    return *this;
}

/* ---- 소멸자: common.c 의 freeArray() 호출 ---- */
Matrix::~Matrix() {
    ::freeArray( data, rows );   /* 1-Gobhagi common.c */
}

/* ---- 랜덤 초기화: common.c 의 mrand() 활용 ---- */
void Matrix::fillRandom( int lower, int upper ) {
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            data[i][j] = lower + ::mrand( upper - lower + 1 );
}

void Matrix::fillZero() {
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            data[i][j] = 0;
}

/* ---- 출력: common.c 의 printArray() 그대로 사용 ---- */
void Matrix::print( const char *msg ) const {
    ::printArray( data, rows, cols, const_cast<char*>(msg) );
}

/* ============================================================
 * Problem 1: 행렬 연산
 * ============================================================ */

Matrix Matrix::add( const Matrix& A, const Matrix& B ) {
    if( A.rows != B.rows || A.cols != B.cols ){
        fprintf(stderr, "add: 크기 불일치 (%dx%d vs %dx%d)\n",
                A.rows, A.cols, B.rows, B.cols);
        exit(1);
    }
    Matrix C( A.rows, A.cols );
    for( int i = 0; i < A.rows; i++ )
        for( int j = 0; j < A.cols; j++ )
            C.data[i][j] = A.data[i][j] + B.data[i][j];
    return C;
}

Matrix Matrix::subtract( const Matrix& A, const Matrix& B ) {
    if( A.rows != B.rows || A.cols != B.cols ){
        fprintf(stderr, "subtract: 크기 불일치\n"); exit(1);
    }
    Matrix C( A.rows, A.cols );
    for( int i = 0; i < A.rows; i++ )
        for( int j = 0; j < A.cols; j++ )
            C.data[i][j] = A.data[i][j] - B.data[i][j];
    return C;
}

/* 곱셈 — 1-Gobhagi multiply_array.c 의 오류(+→*)를 수정 */
Matrix Matrix::multiply( const Matrix& A, const Matrix& B ) {
    if( A.cols != B.rows ){
        fprintf(stderr, "multiply: A.cols(%d) != B.rows(%d)\n", A.cols, B.rows);
        exit(1);
    }
    Matrix C( A.rows, B.cols );
    for( int r = 0; r < A.rows; r++ )
        for( int c = 0; c < B.cols; c++ ){
            int sum = 0;
            for( int k = 0; k < A.cols; k++ )
                sum += A.data[r][k] * B.data[k][c];  /* *  (원본은 + 오류) */
            C.data[r][c] = sum;
        }
    return C;
}

/* Element-wise 나눗셈 */
Matrix Matrix::divideElemWise( const Matrix& A, const Matrix& B ) {
    if( A.rows != B.rows || A.cols != B.cols ){
        fprintf(stderr, "divideElemWise: 크기 불일치\n"); exit(1);
    }
    Matrix C( A.rows, A.cols );
    for( int i = 0; i < A.rows; i++ )
        for( int j = 0; j < A.cols; j++ ){
            if( B.data[i][j] == 0 ){
                fprintf(stderr, "Warning: 0 나눗셈 (%d,%d)\n", i, j);
                C.data[i][j] = 0;
            } else {
                C.data[i][j] = A.data[i][j] / B.data[i][j];
            }
        }
    return C;
}

/* ============================================================
 * Problem 3: 희소 행렬 & 전치 행렬
 *  — common.c 의 createSparse()/freeSparse() 사용
 * ============================================================ */

SparseMatrix *Matrix::toSparse() const {
    int maxTerms = rows * cols;
    SparseMatrix *sp = ::createSparse( rows, cols, maxTerms );
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            if( data[i][j] != 0 ){
                int t = sp->numTerms++;
                sp->terms[t].row   = i;
                sp->terms[t].col   = j;
                sp->terms[t].value = data[i][j];
            }
    return sp;
}

Matrix Matrix::transpose() const {
    Matrix T( cols, rows );
    for( int i = 0; i < rows; i++ )
        for( int j = 0; j < cols; j++ )
            T.data[j][i] = data[i][j];
    return T;
}

/* ============================================================
 * 시간 측정 유틸리티
 * ============================================================ */
double Matrix::measureMs( std::function<void()> func ) {
    auto t0 = std::chrono::high_resolution_clock::now();
    func();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count() / 1000.0;
}
