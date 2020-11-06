all:	src/BigInt.cpp	test/Test.cpp
	g++	src/BigInt.cpp	test/Test.cpp	-o	bin/test	-std=c++17

.PHONY: all test

test:
	bin/test