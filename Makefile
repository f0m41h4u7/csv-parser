SHELL := bash
CXX = g++

all:
	$(CXX) -w -o parser parser.cpp

test:
	$(CXX) -w -o parser parser.cpp
	$(CXX) -w -o runTest test/parserTests.cpp

.PHONY: all test
