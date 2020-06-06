# Elad Zohar
# ezohar
# pa4

COMPILE        = gcc -c -g -std=c99 -Wall
LINK           = gcc -g -o 
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o Graph.o List.o 
	$(LINK) $@ $^

FindComponents.o : FindComponents.c Graph.h List.h
	$(COMPILE) FindComponents.c

GraphTest : GraphTest.o Graph.o List.o
	$(LINK) $@ $^

GraphTest.o : GraphTest.c Graph.h List.h
	$(COMPILE) GraphTest.c

Graph.o : Graph.c Graph.h
	$(COMPILE) Graph.c 

List.o : List.c List.h
	$(COMPILE) List.c

clean :
	$(REMOVE) FindComponents GraphTest *.o

memcheck1 : FindComponents
	$(MEMCHECK) $^

memcheck2 : GraphTest
	$(MEMCHECK) $^