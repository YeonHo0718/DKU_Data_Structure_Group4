#include "sorting.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

/* ============================================================
 * sorting.cpp
 *  — SortArray 클래스 구현
 *    메모리는 malloc/free (sort_funcs.c 와 동일 방식)
 *    정렬은 sort_funcs.c 의 C 함수 직접 호출
 * ============================================================ */

SortArray::SortArray( int n ) : size(n) {
    data = (int *) malloc( sizeof(int) * size );
}

SortArray::SortArray( const SortArray& o ) : size(o.size) {
    data = (int *) malloc( sizeof(int) * size );
    memcpy( data, o.data, sizeof(int) * size );
}

SortArray& SortArray::operator=( const SortArray& o ) {
    if( this == &o ) return *this;
    free( data );
    size = o.size;
    data = (int *) malloc( sizeof(int) * size );
    memcpy( data, o.data, sizeof(int) * size );
    return *this;
}

SortArray::~SortArray() {
    free( data );
}

void SortArray::fillRandom( int lower, int upper ) {
    for( int i = 0; i < size; i++ )
        data[i] = lower + rand() % (upper - lower + 1);
}

void SortArray::copyFrom( const SortArray& o ) {
    int n = (size < o.size) ? size : o.size;
    memcpy( data, o.data, sizeof(int) * n );
}

void SortArray::print( const char *msg, int maxShow ) const {
    printf("%s (size=%d): ", msg, size);
    if( size <= maxShow ){
        for( int i = 0; i < size; i++ ) printf("%d ", data[i]);
    } else {
        int half = maxShow / 2;
        for( int i = 0; i < half; i++ ) printf("%d ", data[i]);
        printf("... ");
        for( int i = size-half; i < size; i++ ) printf("%d ", data[i]);
    }
    printf("\n");
}

double SortArray::measureMs( std::function<long long()> func, long long& comps ) {
    auto t0 = std::chrono::high_resolution_clock::now();
    comps   = func();
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count() / 1000.0;
}
