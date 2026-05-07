# Makefile for HW #3 - Linked List, Stack, Queue, and Computation
# Usage:
#   make all       - build all problems
#   make run       - build and run all
#   make clean     - remove binaries and object files
#   make problem1  - build only problem 1
#   (similarly problem2 .. problem5)

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude
SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin

# Shared modules (only those with .cpp implementation)
MODULES = Polynomial CircularQueue Stack
MOD_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(MODULES))

# Main problems
PROBLEMS = problem1 problem2 problem3 problem4 problem5
TARGETS  = $(patsubst %, $(BIN_DIR)/%, $(PROBLEMS))

.PHONY: all run clean directories

all: directories $(TARGETS)

directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile shared modules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build problem executables
$(BIN_DIR)/problem1: $(SRC_DIR)/problem1.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR)/problem2: $(SRC_DIR)/problem2.cpp $(OBJ_DIR)/Polynomial.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/problem3: $(SRC_DIR)/problem3.cpp $(OBJ_DIR)/CircularQueue.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/problem4: $(SRC_DIR)/problem4.cpp $(OBJ_DIR)/Stack.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN_DIR)/problem5: $(SRC_DIR)/problem5.cpp $(OBJ_DIR)/Stack.o
	$(CXX) $(CXXFLAGS) $^ -o $@

run: all
	@echo "============================================================"
	@echo " Running Problem 1: Polynomial f(x)"
	@echo "============================================================"
	./$(BIN_DIR)/problem1
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 2: Polynomial Add/Sub"
	@echo "============================================================"
	./$(BIN_DIR)/problem2
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 3: Circular Queue"
	@echo "============================================================"
	./$(BIN_DIR)/problem3
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 4: Parenthesis Matching"
	@echo "============================================================"
	./$(BIN_DIR)/problem4
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 5: Infix to Postfix"
	@echo "============================================================"
	./$(BIN_DIR)/problem5

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Cleaned obj/ and bin/ directories."
