# Elad Zohar
# ezohar
# pa1

Lex : Lex.o List.o
	gcc -std=c11 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c11 -Wall -c Lex.c

ListClient: ListClient.o List.o
	gcc -std=c11 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c11 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c11 -Wall -c List.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o

checkClient : 
	valgrind --leak-check=full ListClient

checkLex : 
	valgrind --leak-check=full Lex