# Elad Zohar
# ezohar
# pa5
#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                     makes Lex
#  make DictionaryTest      makes DictionaryTest
#  make clean               removes all binaries
#  make check1              checks DictionaryTest for memory leaks
#  make check2              checks Lex for memory leaks on in4
#------------------------------------------------------------------------------

COMPILE        = gcc -std=c11 -Wall -c
LINK           = gcc -std=c11 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

Lex : Lex.o Dictionary.o 
	$(LINK) $@ $^

Lex.o : Lex.c Dictionary.h
	$(COMPILE) Lex.c

DictionaryTest : DictionaryTest.o Dictionary.o
	$(LINK) $@ $^

DictionaryTest.o : DictionaryTest.c Dictionary.h
	$(COMPILE) DictionaryTest.c

Dictionary.o : Dictionary.c Dictionary.h
	$(COMPILE) Dictionary.c

clean :
	$(REMOVE) Lex DictionaryTest *.o

check1 : Lex
	$(MEMCHECK) $^

check2 : DictionaryTest
	$(MEMCHECK) $^