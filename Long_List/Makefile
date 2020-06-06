# Elad Zohar
# ezohar
# pa2

COMPILE        = gcc -c -g -std=c11 -Wall
LINK           = gcc -g -o 
MEMCHECK       = valgrind --leak-check=full

Arithmetic : Arithmetic.o BigInteger.o List.o 
	$(LINK) $@ $^

Arithmetic.o : Arithmetic.c BigInteger.h List.h
	$(COMPILE) Arithmetic.c

ListTest : ListTest.o BigInteger.o List.o
	$(LINK) $@ $^

ListTest.o : ListTest.c List.h
	$(COMPILE) ListTest.c

BigIntegerTest : BigIntegerTest.o BigInteger.o List.o
	$(LINK) $@ $^

BigIntegerTest.o : BigIntegerTest.c BigInteger.h List.h
	$(COMPILE) BigIntegerTest.c

BigInteger.o : BigInteger.c BigInteger.h
	$(COMPILE) BigInteger.c 

List.o : List.c List.h
	$(COMPILE) List.c

clean :
	rm -f Arithmetic BigIntegerTest ListTest *.o

A_memcheck : Arithmetic
	$(MEMCHECK) $^

BIT_memcheck : BigIntegerTest
	$(MEMCHECK) $^

LT_memcheck : ListTest
	$(MEMCHECK) $^