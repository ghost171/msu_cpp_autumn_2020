all:	test/test.cpp src/ThreadPool.cpp
	g++	test/test.cpp	src/ThreadPool.cpp	-pthread	-o	bin/test

.PHONY: all test

test:
	bin/test