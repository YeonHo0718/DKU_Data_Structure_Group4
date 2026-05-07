#
# Makefile - Sort-2026 과제
#

# 컴파일러와 옵션 설정
CXX = g++
CC = gcc
FLAGS = -Wall -O2 -Iinclude

# 디렉토리 설정
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# 실행 파일 이름
TARGET = $(BIN_DIR)/sort_bench

# 빌드 규칙
all: $(TARGET)

$(TARGET): $(OBJ_DIR)/sort_funcs.o $(OBJ_DIR)/sorting.o $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJ_DIR)/sort_funcs.o $(OBJ_DIR)/sorting.o $(OBJ_DIR)/main.o

# 각 소스 파일 컴파일 규칙
$(OBJ_DIR)/sort_funcs.o: $(SRC_DIR)/sort_funcs.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $(SRC_DIR)/sort_funcs.c -o $(OBJ_DIR)/sort_funcs.o

$(OBJ_DIR)/sorting.o: $(SRC_DIR)/sorting.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $(SRC_DIR)/sorting.cpp -o $(OBJ_DIR)/sorting.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

# 실행 및 테스트용
run: all
	./$(TARGET)

test: all
	./$(TARGET) 1

bench: all
	./$(TARGET) 2

# 정리
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run test bench clean
