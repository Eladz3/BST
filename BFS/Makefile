# Elad Zohar
# ezohar
# pa3

COMPILE        = gcc -c -g -std=c99 -Wall
LINK           = gcc -g -o 
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o Graph.o List.o 
	$(LINK) $@ $^

FindPath.o : FindPath.c Graph.h List.h
	$(COMPILE) FindPath.c

GraphTest : GraphTest.o Graph.o List.o
	$(LINK) $@ $^

GraphTest.o : GraphTest.c Graph.h List.h
	$(COMPILE) GraphTest.c

Graph.o : Graph.c Graph.h
	$(COMPILE) Graph.c 

List.o : List.c List.h
	$(COMPILE) List.c

clean :
	$(REMOVE) FindPath GraphTest *.o

memcheck1 : FindPath
	$(MEMCHECK) $^

memcheck2 : GraphTest
	$(MEMCHECK) $^