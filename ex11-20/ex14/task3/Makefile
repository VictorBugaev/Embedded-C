all: mk

mk: 
	gcc main.c functions.c -o main -lncurses

clang-format:  *.c *.h
	clang-format -n *.c *.h
	clang-format -i *.c *.h
