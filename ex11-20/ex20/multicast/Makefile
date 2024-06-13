all: main

main: sender.c receiver.c 
	gcc sender.c -o sender
	gcc receiver.c -o receiver

clang: *.c
	clang-format -n *.c
	clang-format -i *.c
