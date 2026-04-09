#
# Makefile - Sort-2026 과제 (심플 버전)
#

# 컴파일러와 옵션 설정
CXX = g++
CC = gcc
FLAGS = -Wall -O2 -Iinclude

# 실행 파일 이름
TARGET = sort_bench

# 빌드 규칙
all: $(TARGET)

$(TARGET): sort_funcs.o sorting.o main.o
	$(CXX) $(FLAGS) -o $(TARGET) sort_funcs.o sorting.o main.o

# 각 소스 파일 컴파일
sort_funcs.o: src/sort_funcs.c
	$(CC) $(FLAGS) -c src/sort_funcs.c

sorting.o: src/sorting.cpp
	$(CXX) $(FLAGS) -c src/sorting.cpp

main.o: src/main.cpp
	$(CXX) $(FLAGS) -c src/main.cpp

# 실행 및 테스트용
run: all
	./$(TARGET)

test: all
	./$(TARGET) 1

bench: all
	./$(TARGET) 2

# 정리
clean:
	rm -f $(TARGET) *.o

.PHONY: all run test bench clean
