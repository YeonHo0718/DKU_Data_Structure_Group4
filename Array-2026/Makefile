# Makefile - Array-2026 과제

# 컴파일러와 옵션 설정
CXX = g++
CC = gcc
FLAGS = -Wall -O2 -Iinclude

# 폴더 및 실행 파일 이름
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/matrix_ops

# 빌드 규칙: 실행 파일 만들기
all: $(TARGET)

# bin 폴더를 만들고, obj 폴더에 있는 부품들을 모아서 조립
$(TARGET): $(OBJ_DIR)/common.o $(OBJ_DIR)/matrix.o $(OBJ_DIR)/main.o
	mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJ_DIR)/common.o $(OBJ_DIR)/matrix.o $(OBJ_DIR)/main.o

# 각각의 소스 파일을 obj 폴더 안에 컴파일 (-o 옵션으로 저장 위치 지정)
$(OBJ_DIR)/common.o: src/common.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c src/common.c -o $(OBJ_DIR)/common.o

$(OBJ_DIR)/matrix.o: src/matrix.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c src/matrix.cpp -o $(OBJ_DIR)/matrix.o

$(OBJ_DIR)/main.o: src/main.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c src/main.cpp -o $(OBJ_DIR)/main.o

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

# 폴더째로 깔끔하게 정리
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# .PHONY란?
# all, clean, run 등은 진짜 파일 이름이 아니라 임의로 만든 명령어니까,
# 혹시 폴더 안에 똑같은 이름의 파일이 있더라도 무시하고  
# 그냥 이 명령어를 실행하라고 Make에게 알려주는 안전장치
.PHONY: all run run1 run2 run3 run4 clean