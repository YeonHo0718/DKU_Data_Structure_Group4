#ifndef _SORTING_H_
#define _SORTING_H_

/* ============================================================
 * sorting.h  — sort_funcs.c(1-Gobhagi 기반) 위에 올라가는
 *              C++ SortArray 클래스 선언
 * ============================================================ */

#include "sort_funcs.h"    /* C 정렬 함수 포함 */

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <string>
#include <vector>

/* ============================================================
 * SortArray 클래스
 *  - 내부 배열은 malloc/free (sort_funcs.c 와 동일 방식)
 *  - 실제 정렬은 sort_funcs.c 의 C 함수를 직접 호출
 * ============================================================ */
class SortArray {
public:
    int  *data;   /* malloc 할당 — sort_funcs.c 와 동일한 메모리 방식 */
    int   size;

    SortArray( int n );
    SortArray( const SortArray& o );
    SortArray& operator=( const SortArray& o );
    ~SortArray();

    void fillRandom( int lower, int upper );
    void copyFrom( const SortArray& o );
    void print( const char *msg, int maxShow = 20 ) const;

    /* ---- 정렬: sort_funcs.c(1-Gobhagi) 직접 호출 ---- */
    long long bubbleSort()    { return ::bubble   ( data, size ); }
    long long insertionSort() { return ::insertion( data, size ); }
    long long selectionSort() { return ::selection( data, size ); }

    bool isSorted() const { return ::is_sorted( data, size ) != 0; }

    /* ---- 시간 측정 ---- */
    static double measureMs( std::function<long long()> func, long long& comps );
};

struct BenchResult {
    std::string algorithm;
    int   dataSize;
    double timeMs;
    long long comparisons;
};

#endif /* _SORTING_H_ */
