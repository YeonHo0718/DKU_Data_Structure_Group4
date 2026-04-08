#
# Makefile - Sort-2026 과제
# 1-Gobhagi 기반 모듈라 구조: C 레이어(sort_funcs.c) + C++ 레이어(sorting.cpp)
#

CXX      := g++
CC       := gcc
CXXFLAGS := -Wall -O2 -std=c++17 -Iinclude
CFLAGS   := -Wall -O2 -std=c11   -Iinclude

SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin
TARGET   := $(BIN_DIR)/sort_bench

# C 소스 (1-Gobhagi sort-one/sort.c 기반)
C_SRCS   := $(SRC_DIR)/sort_funcs.c
# C++ 소스
CXX_SRCS := $(SRC_DIR)/sorting.cpp $(SRC_DIR)/main.cpp

C_OBJS   := $(C_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CXX_OBJS := $(CXX_SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJECTS  := $(C_OBJS) $(CXX_OBJS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:   $(TARGET) ; ./$(TARGET)
test:  $(TARGET) ; ./$(TARGET) 1
bench: $(TARGET) ; ./$(TARGET) 2

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run test bench clean
