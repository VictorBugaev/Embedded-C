all: main

main: server.c client.c 
	gcc server.c func_server.c -o server -lrt
	gcc client.c func_client.c -o client -lrt 
	
clang-format: *.c
	clang-format -n *.c *.h
	clang-format -i *.c *.h