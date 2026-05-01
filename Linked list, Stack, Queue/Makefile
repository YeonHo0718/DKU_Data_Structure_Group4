# Makefile for HW #3 - Linked List, Stack, Queue, and Computation
# Usage:
#   make all       - build all problems
#   make run       - build and run all
#   make clean     - remove binaries and object files
#   make problem1  - build only problem 1
#   (similarly problem2 .. problem5)

CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGETS  = problem1 problem2 problem3 problem4 problem5

.PHONY: all run clean $(TARGETS)

all: $(TARGETS)

problem1: problem1.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

problem2: problem2.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

problem3: problem3.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

problem4: problem4.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

problem5: problem5.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: all
	@echo "============================================================"
	@echo " Running Problem 1: Polynomial f(x)"
	@echo "============================================================"
	./problem1
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 2: Polynomial Add/Sub"
	@echo "============================================================"
	./problem2
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 3: Circular Queue"
	@echo "============================================================"
	./problem3
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 4: Parenthesis Matching"
	@echo "============================================================"
	./problem4
	@echo ""
	@echo "============================================================"
	@echo " Running Problem 5: Infix to Postfix"
	@echo "============================================================"
	./problem5

clean:
	rm -f $(TARGETS)
