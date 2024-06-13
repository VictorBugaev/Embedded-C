all: main

main: server.c client.c functions.c
	gcc server.c functions.c -o server
	gcc client.c functions.c -o client

clang: *.c *.h
	clang-format -n *.c *.h
	clang-format -i *.c *.h
