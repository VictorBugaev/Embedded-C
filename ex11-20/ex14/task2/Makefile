main: server.c client.c 
	gcc server.c -o server
	gcc client.c -o client 
	./server
rm: my_pipe
	rm -rv my_pipe
	gcc server.c -o server
	gcc client.c -o client 
	./server
clang: main.c 
	clang-format -i client.c 
	clang-format -i server.c 
