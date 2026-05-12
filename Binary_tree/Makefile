#
# Makefile - Binary_tree 과제 (HW4)
# 이진트리 ADT와 Huffman 코드 구현
#

CXX    = g++
FLAGS  = -Wall -O2 -std=c++11 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/binary_tree

# ---- 빌드 전체 ----
all: $(TARGET)

$(TARGET): $(OBJ_DIR)/expr_tree.o $(OBJ_DIR)/huffman.o $(OBJ_DIR)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(FLAGS) -o $(TARGET) \
	    $(OBJ_DIR)/expr_tree.o \
	    $(OBJ_DIR)/huffman.o   \
	    $(OBJ_DIR)/main.o

# ---- 개별 컴파일 규칙 ----
$(OBJ_DIR)/expr_tree.o: $(SRC_DIR)/expr_tree.cpp include/expr_tree.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/huffman.o: $(SRC_DIR)/huffman.cpp include/huffman.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp include/expr_tree.h include/huffman.h
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

# ---- 실행 ----
run: all
	./$(TARGET)

# ---- 정리 ----
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean
