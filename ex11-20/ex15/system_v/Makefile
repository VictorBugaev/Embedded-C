all: main

main: server.c client.c 
	gcc server.c -o server
	gcc client.c -o client
	
clang-format: *.c *.h
	clang-format -n *.c *.h
	clang-format -i *.c *.h