all:	test/test.cpp src/ThreadPool.cpp
	g++	test/test.cpp	src/ThreadPool.cpp	-pthread	-std=c++11	-o	bin/test	-std=c++17

.PHONY: all test

test:
	bin/test