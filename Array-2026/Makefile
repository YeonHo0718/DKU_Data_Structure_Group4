#
# Makefile - Array-2026 과제
# 1-Gobhagi 기반 모듈라 구조: C 레이어(common.c) + C++ 레이어(matrix.cpp)
#

CXX      := g++
CC       := gcc
CXXFLAGS := -Wall -O2 -std=c++17 -Iinclude
CFLAGS   := -Wall -O2 -std=c11   -Iinclude

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/matrix_ops

# C 소스 (1-Gobhagi common.c 포함)
C_SRCS   := $(SRC_DIR)/common.c
# C++ 소스
CXX_SRCS := $(SRC_DIR)/matrix.cpp $(SRC_DIR)/main.cpp

C_OBJS   := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CXX_OBJS := $(CXX_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJECTS  := $(C_OBJS) $(CXX_OBJS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# C 컴파일 (common.c)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# C++ 컴파일
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:  $(TARGET) ; ./$(TARGET)
run1: $(TARGET) ; ./$(TARGET) 1
run2: $(TARGET) ; ./$(TARGET) 2
run3: $(TARGET) ; ./$(TARGET) 3
run4: $(TARGET) ; ./$(TARGET) 4

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run run1 run2 run3 run4 clean
