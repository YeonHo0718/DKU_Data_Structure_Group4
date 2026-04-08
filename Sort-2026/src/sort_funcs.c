#include <stdio.h>
#include "sort_funcs.h"

/* ============================================================
 * sort_funcs.c  — 1-Gobhagi sort-one/sort.c 기반
 *
 * 원본 함수 구조(변수명, 알고리즘 흐름)를 그대로 유지하되:
 *   1. printf 단계 출력 제거 (대용량 벤치마크 대응)
 *   2. 비교 횟수를 long long 으로 반환
 * ============================================================ */

#define TRUE  1
#define FALSE 0

/* ---- 배열 출력 (1-Gobhagi 원본) ---- */
void print_array( int *a, int n ){
    int i;
    for( i = 0; i < n; i++ )
        printf("%d ", a[i]);
    printf("\n");
}

/* ---- Bubble Sort (1-Gobhagi 원본 구조 유지) ----
 *  원본과의 차이:
 *    - printf 제거
 *    - swapped 플래그로 조기 종료 추가 (이미 정렬 시 O(n))
 *    - 비교 횟수 반환
 */
long long bubble( int *a, int n ){
    int i, j, val;
    int swapped;
    long long comparisons = 0;

    for( i = n-1; i > 0; i-- ){
        swapped = FALSE;
        for( j = 0; j < i; j++ ){
            comparisons++;
            if( a[j] > a[j+1] ){
                val      = a[j];
                a[j]     = a[j+1];
                a[j+1]   = val;
                swapped  = TRUE;
            }
        }
        if( !swapped ) break;   /* 조기 종료 */
    }
    return comparisons;
}

/* ---- Insertion Sort (1-Gobhagi 원본 구조 유지) ----
 *  원본의 move 플래그 방식을 그대로 사용
 */
long long insertion( int *a, int n ){
    int i, j, move;
    int val;
    long long comparisons = 0;

    for( i = 1; i < n; i++ ){
        val = a[i];
        j   = i;

        if( a[j-1] > val ) move = TRUE;
        else               move = FALSE;
        comparisons++;                  /* 첫 비교 */

        while( move ){
            a[j] = a[j-1];
            j    = j - 1;
            if( j > 0 && a[j-1] > val ){
                move = TRUE;
                comparisons++;
            } else {
                move = FALSE;
                if( j > 0 ) comparisons++;
            }
        }
        a[j] = val;
    }
    return comparisons;
}

/* ---- Selection Sort (1-Gobhagi 원본 구조 유지) ---- */
long long selection( int *a, int n ){
    int i, j, least;
    int val;
    long long comparisons = 0;

    for( i = 0; i < n-1; i++ ){
        least = i;
        for( j = i+1; j < n; j++ ){
            comparisons++;
            if( a[j] < a[least] )
                least = j;
        }
        val        = a[least];
        a[least]   = a[i];
        a[i]       = val;
    }
    return comparisons;
}

/* ---- 정렬 결과 검증 ---- */
int is_sorted( int *a, int n ){
    int i;
    for( i = 1; i < n; i++ )
        if( a[i-1] > a[i] ) return FALSE;
    return TRUE;
}
