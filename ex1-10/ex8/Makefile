all: dinamic

dinamic: difference.c division.c multiplication.c summary.c
	gcc difference.c division.c multiplication.c summary.c -fPIC -c
	gcc  -shared *.o -o libtest.so
	gcc main.c -o one -L. -ltest
	 
clean:
	rm *.o *.so