main: main.c functions.c
	gcc main.c functions.c -o main -pthread

clang-format: *.c *.h
	clang-format -n *.c *.h
	clang-format -i *.c *.h
