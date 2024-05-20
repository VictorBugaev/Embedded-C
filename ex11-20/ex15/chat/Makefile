all: main

main: server.c client.c 
	gcc server.c -o server -lrt
	gcc client.c -o client -lrt 
	
clang-format: *.c
	clang-format -n *.c 
	clang-format -i *.c