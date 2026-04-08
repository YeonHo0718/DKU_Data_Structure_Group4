#include "sorting.h"
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

/* ============================================================
 * 소규모 테스트 — 정렬 결과 출력 (2개 이내)
 * ============================================================ */
void testSmall(){
    puts("========================================");
    puts(" 정렬 결과 확인 테스트 (소규모)");
    puts("========================================\n");

    /* 테스트 1: 역순 배열 (1-Gobhagi sort.c main 과 동일한 입력) */
    {
        puts("--- 테스트 1: 역순 배열 (n=10, 1-Gobhagi sort.c 동일 입력) ---");
        int n = 10;
        SortArray orig(n);
        for(int i=0; i<n; i++) orig.data[i] = n - i;
        orig.print("원본");

        long long comp;
        SortArray a1(orig);
        double t = SortArray::measureMs([&]{ return a1.bubbleSort(); }, comp);
        a1.print("Bubble Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a1.isSorted()?"OK":"FAIL");

        SortArray a2(orig);
        t = SortArray::measureMs([&]{ return a2.insertionSort(); }, comp);
        a2.print("Insertion Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a2.isSorted()?"OK":"FAIL");

        SortArray a3(orig);
        t = SortArray::measureMs([&]{ return a3.selectionSort(); }, comp);
        a3.print("Selection Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a3.isSorted()?"OK":"FAIL");
    }

    /* 테스트 2: 랜덤 배열 */
    {
        puts("--- 테스트 2: 랜덤 배열 (n=15) ---");
        int n = 15;
        srand(42);
        SortArray orig(n); orig.fillRandom(1, 100);
        orig.print("원본");

        long long comp;
        SortArray a1(orig);
        double t = SortArray::measureMs([&]{ return a1.bubbleSort(); }, comp);
        a1.print("Bubble Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a1.isSorted()?"OK":"FAIL");

        SortArray a2(orig);
        t = SortArray::measureMs([&]{ return a2.insertionSort(); }, comp);
        a2.print("Insertion Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a2.isSorted()?"OK":"FAIL");

        SortArray a3(orig);
        t = SortArray::measureMs([&]{ return a3.selectionSort(); }, comp);
        a3.print("Selection Sort");
        printf("  비교: %lld, 시간: %.3fms, 검증: %s\n\n", comp, t, a3.isSorted()?"OK":"FAIL");
    }
}

/* ============================================================
 * 대규모 벤치마크 — 데이터 크기별 평균 실행 시간
 * ============================================================ */
void benchmarkAll(){
    puts("========================================");
    puts(" 정렬 알고리즘 벤치마크");
    puts(" (데이터 크기: 10,000 ~ 300,000)");
    puts("========================================\n");

    int sizes[] = {10000, 20000, 50000, 80000, 100000,
                   150000, 200000, 250000, 300000};
    int numSizes = (int)(sizeof(sizes)/sizeof(sizes[0]));

    /* 결과 저장 */
    double tBubble[9], tInsert[9], tSelect[9];
    long long cBubble[9], cInsert[9], cSelect[9];

    for(int t=0; t<numSizes; t++){
        int n = sizes[t];
        srand(t + 1000);
        SortArray orig(n); orig.fillRandom(1, 1000000);

        { SortArray a(orig); tBubble[t]=SortArray::measureMs([&]{return a.bubbleSort();}, cBubble[t]);
          if(!a.isSorted()) fprintf(stderr,"ERR bubble n=%d\n",n); }
        { SortArray a(orig); tInsert[t]=SortArray::measureMs([&]{return a.insertionSort();}, cInsert[t]);
          if(!a.isSorted()) fprintf(stderr,"ERR insert n=%d\n",n); }
        { SortArray a(orig); tSelect[t]=SortArray::measureMs([&]{return a.selectionSort();}, cSelect[t]);
          if(!a.isSorted()) fprintf(stderr,"ERR select n=%d\n",n); }
    }

    /* 표 출력 */
    printf("%10s %15s %15s %15s %18s %18s %18s\n",
           "Size","Bubble(ms)","Insert(ms)","Select(ms)",
           "Bubble(comp)","Insert(comp)","Select(comp)");
    printf("%s\n", string(109,'-').c_str());
    for(int t=0; t<numSizes; t++)
        printf("%10d %15.1f %15.1f %15.1f %18lld %18lld %18lld\n",
               sizes[t], tBubble[t], tInsert[t], tSelect[t],
               cBubble[t], cInsert[t], cSelect[t]);

    /* CSV 출력 */
    puts("\n--- CSV (그래프용: Excel/Matplotlib 등) ---");
    puts("Size,Bubble(ms),Insertion(ms),Selection(ms)");
    for(int t=0; t<numSizes; t++)
        printf("%d,%.1f,%.1f,%.1f\n",
               sizes[t], tBubble[t], tInsert[t], tSelect[t]);
    puts("");
}

/* ============================================================
 * main
 * ============================================================ */
int main(int argc, char *argv[]){
    int mode = (argc>1) ? atoi(argv[1]) : 0;

    puts("============================================");
    puts(" 자료구조 과제 #2: 정렬 알고리즘의 구현과");
    puts(" 실행시간 비교 (1-Gobhagi sort.c 기반)");
    puts("============================================\n");

    if(mode==0||mode==1) testSmall();
    if(mode==0||mode==2) benchmarkAll();

    return 0;
}
