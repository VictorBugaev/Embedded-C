all: main

main: server.c client_tcp.c client_udp.c functions.c
	gcc server.c functions.c -o server
	gcc client_udp.c functions.c -o client_udp
	gcc client_tcp.c functions.c -o client_tcp

clang: *.c *.h
	clang-format -n *.c *.h
	clang-format -i *.c *.h
