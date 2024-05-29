all: main

main: server.c client.c 
	gcc server.c functions.c -o server -lrt
	gcc client.c functions.c -o client -lrt 
	
clang-format: *.c
	clang-format -n *.c *.h
	clang-format -i *.c *.h