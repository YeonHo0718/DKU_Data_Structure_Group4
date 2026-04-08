#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common.h"

/* ============================================================
 * common.c  — 1-Gobhagi 기반 (교수님 제공 코드 그대로 유지)
 *             + SparseMatrix 유틸리티 추가
 * ============================================================ */

/* ---- 2차원 배열 동적 할당 (1-Gobhagi 원본) ---- */
int **array( int rows, int cols ){
    int **arr;
    int i;

    arr = (int **) malloc( sizeof(int *) * rows );
    for( i = 0; i < rows; i++ )
        arr[i] = (int *) malloc( sizeof(int) * cols );

    return arr;
}

/* ---- 1차원 배열 동적 할당 (1-Gobhagi 원본) ---- */
int *vector( int rows ){
    int *vec;
    vec = (int *) malloc( sizeof(int) * rows );
    return vec;
}

/* ---- 2차원 배열 해제 (1-Gobhagi 원본) ---- */
void freeArray( int **arr, int rows ){
    int r;
    for( r = 0; r < rows; r++ )
        freeVector( arr[r] );
    free( arr );
}

/* ---- 1차원 배열 해제 (1-Gobhagi 원본) ---- */
void freeVector( int *vec ){
    free( vec );
}

/* ---- 2차원 배열 출력 (1-Gobhagi 원본) ---- */
void printArray( int **arr, int rows, int cols, char *msg ){
    int r, c;
    printf("%s\n", msg);
    for( r = 0; r < rows; r++ ){
        for( c = 0; c < cols; c++ )
            printf("\t%d", arr[r][c]);
        printf("\n");
    }
}

/* ---- 1차원 배열 출력 (1-Gobhagi 원본) ---- */
void printVector( int *arr, int rows, char *msg ){
    int r;
    printf("%s\n", msg);
    for( r = 0; r < rows; r++ )
        printf("\t%d", arr[r]);
    printf("\n");
}

/* ---- 난수 생성 (1-Gobhagi 원본) ---- */
int mrand( int range ){
    return rand() % range;
}

/* ---- 시간 측정 (1-Gobhagi gettime.c 통합) ---- */
long get_runtime(void){
    clock_t start;
    start = clock();
    return (long)((double)start * 100.0 / (double)CLOCKS_PER_SEC);
}

/* ============================================================
 * SparseMatrix 유틸리티 (Problem 3 추가)
 * ============================================================ */

SparseMatrix *createSparse( int rows, int cols, int maxTerms ){
    SparseMatrix *sp = (SparseMatrix *) malloc( sizeof(SparseMatrix) );
    sp->rows     = rows;
    sp->cols     = cols;
    sp->numTerms = 0;
    sp->terms    = (SparseElement *) malloc( sizeof(SparseElement) * maxTerms );
    return sp;
}

void freeSparse( SparseMatrix *sp ){
    if( sp ){
        free( sp->terms );
        free( sp );
    }
}

void printSparse( SparseMatrix *sp, char *msg ){
    int i;
    printf("%s (Sparse %dx%d, non-zero: %d)\n",
           msg, sp->rows, sp->cols, sp->numTerms);
    printf("%6s %6s %8s\n", "Row", "Col", "Value");
    for( i = 0; i < sp->numTerms; i++ )
        printf("%6d %6d %8d\n",
               sp->terms[i].row, sp->terms[i].col, sp->terms[i].value);
    printf("\n");
}
