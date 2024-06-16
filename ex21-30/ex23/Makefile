all: main

main: server.c client.c 
	gcc server.c -o server
	gcc client.c -o client

clang: *.c
	clang-format -n *.c
	clang-format -i *.c
