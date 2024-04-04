LIB_DIR = ./libs
OBJ  = ./obj
all: dinamic clean

dinamic: difference division multiplication summary	
	gcc main.c -o one -g -ldl -rdynamic

difference: difference.c 
	gcc difference.c -fPIC -c 
	gcc  -shared *.o -o $(LIB_DIR)/libdifference.so
	
division: division.c 
	gcc division.c -fPIC -c
	gcc  -shared *.o -o $(LIB_DIR)/libdivision.so

multiplication: multiplication.c
	gcc multiplication.c -fPIC -c
	gcc  -shared *.o -o $(LIB_DIR)/libmultiplication.so

summary: summary.c
	gcc summary.c -fPIC -c
	gcc  -shared *.o -o $(LIB_DIR)/libsummary.so

clean:
	rm *.o 

clean_lib:
	rm $(LIB_DIR)/*.so 
