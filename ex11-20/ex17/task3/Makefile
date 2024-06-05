all: main

main: receiver.c sender.c
	gcc receiver.c -o receiver
	gcc sender.c -o sender

clang: *.c
	clang-format -n *.c
	clang-format -i *.c
