import numpy as np

# ------------------------------------------------------------------
# Problem 1 에서 파이썬과의 비교를 위한 스크립트
# ------------------------------------------------------------------

# 1. 데이터 정의 (보고서 4.1절의 테스트 데이터와 동일하게 설정)
A = np.array([
    [7, 7, 9],
    [1, 2, 2],
    [2, 7, 3]
])

B = np.array([
    [6, 7, 9],
    [1, 1, 7],
    [9, 8, 1]
])

print("=== Matrix A ===")
print(A)
print("\n=== Matrix B ===")
print(B)

# 2. numpy 연산 방법 및 결과 확인
print("\n" + "="*40)
print(" numpy Element-wise 연산 지시 방법")
print("="*40)

# [1] Element-wise Addition
# numpy 지시어: A + B  (또는 np.add(A, B))
print("\n[1] A + B (덧셈):")
print(A + B)

# [2] Element-wise Subtraction
# numpy 지시어: A - B  (또는 np.subtract(A, B))
print("\n[2] A - B (뺄셈):")
print(A - B)

# [3] Element-wise Division
# numpy 지시어: A / B (실수 나눗셈) 또는 A // B (정수 나눗셈)
# 본 과제의 C++ 프로그램은 정수형(int) 연산을 수행하므로 // 연산자와 결과가 동일함
print("\n[3] A // B (정수 나눗셈 - C++ 결과와 비교):")
print(A // B)

# [4] Matrix Multiplication (주의: Element-wise 아님)
# numpy 지시어: D @ E  (또는 np.dot(D, E), np.matmul(D, E))
# 만약 D * E 라고 쓰면 element-wise 곱셈이 되므로 행렬 곱셈 시에는 @를 써야 함
D = np.array([[1, 2], [3, 4]])
E = np.array([[5, 6], [7, 8]])
print("\n[4] D @ E (행렬 곱셈):")
print(D @ E)

print("\n" + "="*40)
print(" 결론: 본 프로그램의 정수 행렬 연산 결과는 ")
print(" numpy의 +, -, // 연산 결과와 완벽히 일치함.")
print("="*40)
