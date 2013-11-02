grep: grep.o vecGrep.o
	nvcc -o grep grep.o vecGrep.o -I .

grep.o: grep.cpp grep.h
	g++ -c grep.cpp

vecGrep.o: vecGrep.cu grep.h
	nvcc -c vecGrep.cu

