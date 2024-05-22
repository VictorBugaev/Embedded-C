all: main

main: program1.c program2.c 
	gcc program1.c -o program1
	gcc program2.c -o program2
	
clang-format: *.c
	clang-format -n *.c
	clang-format -i *.c