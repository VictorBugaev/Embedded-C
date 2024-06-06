all: main

main: server.c client.c 
	gcc server.c -o server
	gcc client.c -o client

main_rm: server.c client.c Server 
	gcc server.c -o server
	gcc client.c -o client
	rm Server

clang: *.c
	clang-format -n *.c
	clang-format -i *.c
