all:
	g++ -o test.exe tests/test_compile_magic.cpp tests/tests.cpp -I include -std=c++1z -O3 -Wall -Wpedantic