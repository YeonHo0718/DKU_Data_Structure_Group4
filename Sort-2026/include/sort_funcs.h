#ifndef _SORT_FUNCS_H_
#define _SORT_FUNCS_H_

/* ============================================================
 * sort_funcs.h  — 1-Gobhagi sort-one/sort.c 기반
 *
 * 교수님 제공 sort.c 의 bubble/insertion/selection 함수를
 * 벤치마크에 맞게 확장:
 *   - 단계별 출력 제거 (대용량 데이터 대응)
 *   - 비교 횟수(comparisons) 반환
 * ============================================================ */

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 배열 출력 (소규모 테스트용) */
void print_array( int *a, int n );

/* Bubble Sort    — 1-Gobhagi sort.c 원본 구조 유지, 조기종료 추가 */
long long bubble   ( int *a, int n );

/* Insertion Sort — 1-Gobhagi sort.c 원본 구조 (move 플래그) 유지 */
long long insertion( int *a, int n );

/* Selection Sort — 1-Gobhagi sort.c 원본 구조 유지 */
long long selection( int *a, int n );

/* 정렬 결과 검증 */
int is_sorted( int *a, int n );

#ifdef __cplusplus
}
#endif

#endif /* _SORT_FUNCS_H_ */
