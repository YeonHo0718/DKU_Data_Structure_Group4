#include "matrix.h"
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

/* ============================================================
 * Problem 1: 소규모 행렬 연산 결과 확인
 * ============================================================ */
void testProblem1(){
    puts("========================================");
    puts(" Problem 1: 행렬 연산 테스트");
    puts("========================================\n");

    srand(42);
    int m = 3, n = 3;

    Matrix A(m, n);  A.fillRandom(1, 9);
    Matrix B(m, n);  B.fillRandom(1, 9);

    A.print("A");
    B.print("B");
    Matrix::add(A, B).print("A + B");
    Matrix::subtract(A, B).print("A - B");
    Matrix::divideElemWise(A, B).print("A ./ B (element-wise)");

    /* 곱셈 */
    Matrix D(3,4); D.fillRandom(1,4);
    Matrix E(4,2); E.fillRandom(1,4);
    D.print("D (3x4)");
    E.print("E (4x2)");
    Matrix::multiply(D, E).print("D * E");

    puts("--- numpy element-wise 비교 ---");
    puts("  C = A + B   →  np: C = A + B");
    puts("  C = A - B   →  np: C = A - B");
    puts("  C = A ./ B  →  np: C = A // B  (정수 나눗셈)");
    puts("  C = D * E   →  np: C = D @ E\n");
}

/* ============================================================
 * Problem 2: 다양한 크기별 실행시간 측정
 * ============================================================ */
void testProblem2(){
    puts("========================================");
    puts(" Problem 2: 시간 복잡도 분석 (행렬 연산)");
    puts("========================================\n");

    /* 덧셈/뺄셈/나눗셈 테스트 크기 */
    int sizes_add[][2] = {
        {10,10},{50,50},{100,100},{200,200},{300,300},
        {400,400},{500,500},{700,700},{1000,1000},{1500,1500}
    };
    int na = sizeof(sizes_add)/sizeof(sizes_add[0]);

    printf("%-8s %-8s %14s %14s %14s\n","M","N","Add(ms)","Sub(ms)","Div(ms)");
    printf("%s\n", string(58,'-').c_str());
    for(int t=0; t<na; t++){
        int m=sizes_add[t][0], n=sizes_add[t][1];
        srand(t+1);
        Matrix A(m,n); A.fillRandom(1,99);
        Matrix B(m,n); B.fillRandom(1,99);
        double ta = Matrix::measureMs([&]{Matrix::add(A,B);});
        double ts = Matrix::measureMs([&]{Matrix::subtract(A,B);});
        double td = Matrix::measureMs([&]{Matrix::divideElemWise(A,B);});
        printf("%-8d %-8d %14.3f %14.3f %14.3f\n",m,n,ta,ts,td);
    }

    /* 곱셈 테스트 크기 */
    int sizes_mul[][2] = {
        {10,10},{50,50},{100,100},{200,200},{300,300},
        {400,400},{500,500},{700,700},{1000,1000},{50,500}
    };
    int nm = sizeof(sizes_mul)/sizeof(sizes_mul[0]);

    printf("\n%-8s %-8s %14s\n","M","K","Mul(ms)");
    printf("%s\n", string(30,'-').c_str());
    for(int t=0; t<nm; t++){
        int m=sizes_mul[t][0], k=sizes_mul[t][1];
        srand(t+100);
        Matrix A(m,k); A.fillRandom(1,9);
        Matrix B(k,m); B.fillRandom(1,9);
        double tm = Matrix::measureMs([&]{Matrix::multiply(A,B);});
        printf("%-8d %-8d %14.3f\n",m,k,tm);
    }
    puts("");
}

/* ============================================================
 * Problem 3: 희소·전치 행렬 확인
 * ============================================================ */
void testProblem3(){
    puts("========================================");
    puts(" Problem 3: 희소 행렬 & 전치 행렬");
    puts("========================================\n");

    int m=5, n=6;
    Matrix A(m,n); A.fillZero();
    /* 드문드문 값 삽입 */
    int pts[][3] = {{0,2,3},{0,4,7},{1,1,5},{2,3,8},
                    {3,0,2},{3,5,4},{4,2,1},{4,4,9}};
    for(auto &p : pts) A.data[p[0]][p[1]] = p[2];

    A.print("원본 행렬 A");

    SparseMatrix *sp = A.toSparse();
    ::printSparse(sp, (char*)"희소 행렬 A");

    /* 희소 전치: common.c의 SparseMatrix 구조 그대로 활용 */
    SparseMatrix *spT = ::createSparse(sp->cols, sp->rows, sp->numTerms);
    spT->numTerms = sp->numTerms;
    /* 열 카운트 기반 O(n+t) 전치 */
    int *colCnt   = (int*)calloc(sp->cols, sizeof(int));
    int *rowStart = (int*)calloc(sp->cols, sizeof(int));
    for(int i=0;i<sp->numTerms;i++) colCnt[sp->terms[i].col]++;
    for(int i=1;i<sp->cols;i++) rowStart[i]=rowStart[i-1]+colCnt[i-1];
    int *pos = (int*)malloc(sp->cols*sizeof(int));
    for(int i=0;i<sp->cols;i++) pos[i]=rowStart[i];
    for(int i=0;i<sp->numTerms;i++){
        int j=pos[sp->terms[i].col]++;
        spT->terms[j].row=sp->terms[i].col;
        spT->terms[j].col=sp->terms[i].row;
        spT->terms[j].value=sp->terms[i].value;
    }
    free(colCnt); free(rowStart); free(pos);
    ::printSparse(spT, (char*)"전치 희소 행렬 A^T");

    /* 일반 전치 */
    A.transpose().print("전치 행렬 A^T (일반)");

    ::freeSparse(sp);
    ::freeSparse(spT);
}

/* ============================================================
 * Problem 4: 희소·전치 시간 복잡도
 * ============================================================ */
void testProblem4(){
    puts("========================================");
    puts(" Problem 4: 시간 복잡도 분석 (희소/전치)");
    puts("========================================\n");

    int sizes[][2] = {
        {10,10},{50,50},{100,100},{200,200},{300,300},
        {400,400},{500,500},{700,700},{1000,1000},{1500,1500}
    };
    int ns = sizeof(sizes)/sizeof(sizes[0]);
    double density = 0.1;

    printf("%-8s %-8s %14s %14s %12s\n",
           "M","N","Trans(ms)","toSparse(ms)","NonZero");
    printf("%s\n", string(58,'-').c_str());

    for(int t=0;t<ns;t++){
        int m=sizes[t][0], n=sizes[t][1];
        srand(t+200);
        Matrix A(m,n); A.fillZero();
        int nz=(int)(m*n*density);
        for(int i=0;i<nz;i++) A.data[rand()%m][rand()%n]=1+mrand(99);

        double tt = Matrix::measureMs([&]{ A.transpose(); });
        SparseMatrix *sp = nullptr;
        double ts = Matrix::measureMs([&]{ sp=A.toSparse(); });
        int nonzero = sp ? sp->numTerms : 0;
        ::freeSparse(sp);

        printf("%-8d %-8d %14.3f %14.3f %12d\n",m,n,tt,ts,nonzero);
    }
    puts("");
}

/* ============================================================
 * main
 * ============================================================ */
int main(int argc, char *argv[]){
    int prob = (argc>1) ? atoi(argv[1]) : 0;

    puts("============================================");
    puts(" 자료구조 과제 #1: 배열과 행렬 연산");
    puts(" (1-Gobhagi common.c/h 기반)");
    puts("============================================\n");

    if(prob==0||prob==1) testProblem1();
    if(prob==0||prob==2) testProblem2();
    if(prob==0||prob==3) testProblem3();
    if(prob==0||prob==4) testProblem4();

    return 0;
}
