/****************
    Elad Zohar
    ezohar
    pa4
****************/

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
#include"List.h"

int main(){
   int i, n = 8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T = NULL, C = NULL;

   for(i = 1; i <= n; i++) 
      append(S, i);
   
   printf("Directed Graph (G)\n");
   printf("---------------------------------\n");
   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);
   printf("---------------------------------\n\n\n");

   DFS(G, S);
   printf("DFS of G\n");
   printf("---------------------------------\n");
   printf("x:  d  f  p\n");
   for(i = 1; i <= n; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }

   printf("\nStack: ");
   printList(stdout, S);
   printf("\n---------------------------------\n\n\n");

   T = transpose(G);
   C = copyGraph(G);
   printf("Copy of G\n");
   printf("---------------------------------\n");
   printGraph(stdout, C);
   printf("---------------------------------\n\n\n");
   printf("Transpose of G\n");
   printf("---------------------------------\n");
   printGraph(stdout, T);
   printf("---------------------------------\n\n\n");

   DFS(T, S);
   printf("DFS of Transpose\n");
   printf("---------------------------------\n");
   printf("x:  d  f  p\n");
   for(i = 1; i <= n; i++){
      printf("%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   printf("\nStack: ");
   printList(stdout, S);
   printf("\n---------------------------------\n\n\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
/*
Desired Output:
Directed Graph (G)
---------------------------------
1: 2 5 
2: 5 6 
3: 2 4 6 7 8 
4: 
5: 
6: 5 7 
7: 
8: 4 7 
---------------------------------


DFS of G
---------------------------------
x:  d  f  p
1:  1 10  0
2:  2  9  1
3: 11 16  0
4: 12 13  3
5:  3  4  2
6:  5  8  2
7:  6  7  6
8: 14 15  3

Stack: 3 8 4 1 2 6 7 5 
---------------------------------


Copy of G
---------------------------------
1: 2 5 
2: 5 6 
3: 2 4 6 7 8 
4: 
5: 
6: 5 7 
7: 
8: 4 7 
---------------------------------


Transpose of G
---------------------------------
1: 
2: 1 3 
3: 
4: 3 8 
5: 1 2 6 
6: 2 3 
7: 3 6 8 
8: 3 
---------------------------------


DFS of Transpose
---------------------------------
x:  d  f  p
1:  7  8  0
2:  9 10  0
3:  1  2  0
4:  5  6  0
5: 15 16  0
6: 11 12  0
7: 13 14  0
8:  3  4  0

Stack: 5 7 6 2 1 4 8 3 
---------------------------------

*/