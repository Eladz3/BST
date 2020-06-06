# Elad Zohar
# ezohar
# pa2

COMPILE        = gcc -c -g -std=c99 -Wall
LINK           = gcc -g -o 
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Sparse : Sparse.o Matrix.o List.o 
	$(LINK) $@ $^

Sparse.o : Sparse.c Matrix.h List.h
	$(COMPILE) Sparse.c

ListTest : ListTest.o Matrix.o List.o
	$(LINK) $@ $^

ListTest.o : ListTest.c List.h
	$(COMPILE) ListTest.c

MatrixTest : MatrixTest.o Matrix.o List.o
	$(LINK) $@ $^

MatrixTest.o : MatrixTest.c Matrix.h List.h
	$(COMPILE) MatrixTest.c

Matrix.o : Matrix.c Matrix.h
	$(COMPILE) Matrix.c 

List.o : List.c List.h
	$(COMPILE) List.c

clean :
	$(REMOVE) Sparse MatrixTest ListTest *.o

s_memcheck : Sparse
	$(MEMCHECK) $^

mt_memcheck : MatrixTest
	$(MEMCHECK) $^

lt_memcheck : ListTest
	$(MEMCHECK) $^