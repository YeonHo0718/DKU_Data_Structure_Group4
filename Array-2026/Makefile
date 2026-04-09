# Makefile - Array-2026 과제

# 컴파일러와 옵션 설정
CXX = g++
CC = gcc
FLAGS = -Wall -O2 -Iinclude

# 실행 파일 이름
TARGET = matrix_ops

# 빌드 규칙: 실행 파일 만들기
all: $(TARGET)

$(TARGET): common.o matrix.o main.o
	$(CXX) $(FLAGS) -o $(TARGET) common.o matrix.o main.o

# 각 소스 파일 컴파일
common.o: src/common.c
	$(CC) $(FLAGS) -c src/common.c

matrix.o: src/matrix.cpp
	$(CXX) $(FLAGS) -c src/matrix.cpp

main.o: src/main.cpp
	$(CXX) $(FLAGS) -c src/main.cpp

# 테스트 실행용
run: all
	./$(TARGET)
run1: all
	./$(TARGET) 1
run2: all
	./$(TARGET) 2
run3: all
	./$(TARGET) 3
run4: all
	./$(TARGET) 4

# 정리
clean:
	rm -f $(TARGET) *.o

.PHONY: all run run1 run2 run3 run4 clean