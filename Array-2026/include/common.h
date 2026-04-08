#ifndef _COMMON_
#define _COMMON_

/* ============================================================
 * common.h  — 1-Gobhagi 기반 메모리/유틸리티 함수
 * (교수님 제공 코드 그대로 유지 + Sparse 구조체 추가)
 * ============================================================ */

/* ---- 동적 메모리 할당/해제 ---- */
int **array( int rows, int cols );   // 2차원 배열 할당
int  *vector( int rows );            // 1차원 배열 할당

void freeArray( int **arr, int rows );
void freeVector( int *vec );

/* ---- 출력 ---- */
void printArray( int **arr, int rows, int cols, char *msg );
void printVector( int *arr, int rows, char *msg );

/* ---- 난수 ---- */
int mrand( int range );

/* ---- 시간 측정 (gettime.c 기반) ---- */
long get_runtime(void);   /* 단위: 100분의 1초 */

/* ============================================================
 * 희소 행렬 구조체 (Problem 3 확장)
 * ============================================================ */
typedef struct {
    int row;
    int col;
    int value;
} SparseElement;

typedef struct {
    int rows;
    int cols;
    int numTerms;
    SparseElement *terms;   /* 동적 할당 배열 */
} SparseMatrix;

/* ---- 희소 행렬 함수 ---- */
SparseMatrix *createSparse( int rows, int cols, int maxTerms );
void freeSparse( SparseMatrix *sp );
void printSparse( SparseMatrix *sp, char *msg );

#endif /* _COMMON_ */
