/****************
    Elad Zohar
    ezohar
    pa3
****************/

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(){
   printf("Undirected Graph\n");
   printf("---------------------------------\n");
   Graph A = newGraph(7);
   addEdge(A, 1, 2);
   addEdge(A, 1, 3);
   addEdge(A, 1, 4);
   addEdge(A, 2, 4);
   addEdge(A, 2, 5);
   addEdge(A, 5, 6);
   addEdge(A, 6, 7);
   addEdge(A, 7, 1);
   printf("Order : %d\n", getOrder(A));
   printf("Size  : %d\n\n", getSize(A));
   printGraph(stdout, A);
   printf("\n");

   BFS(A, 1);
   printf("1 --> 7 Distance : %d\n", getDist(A, 7));
   printf("Vertex 7 Parent  : %d\n", getParent(A, 7));
   List p = newList();
   printf("Path to Vertex 7 : ");
   getPath(p, A, 7);
   printList(stdout, p);
   printf("\n");
   printf("---------------------------------\n\n\n");

   printf("Graph CLEARED\n");
   printf("---------------------------------\n");
   makeNull(A);
   clear(p);
   BFS(A, 1);
   int dist = getDist(A, 7);
   if(dist != INF)
      printf("1 --> 7 Distance : %d\n\n", dist); 
   else
      printf("1 --> 7 Distance : infinity\n\n");
   getPath(p, A, 7);
   if(front(p) == NIL)
      printf("Path to Vertex 7 : DNE");
   else{
      printf("Path to Vertex 7 : ");
      printList(stdout, p);
   }
   printf("\n---------------------------------\n\n\n");

   printf("Directed Graph\n");
   printf("---------------------------------\n");
   Graph B = newGraph(7);
   addArc(B, 1, 2);
   addArc(B, 2, 4);
   addArc(B, 2, 5);
   addArc(B, 3, 1);
   addArc(B, 4, 1);
   addArc(B, 5, 6);
   addArc(B, 6, 5);
   addArc(B, 6, 7);
   addArc(B, 7, 1);
   printf("Order : %d\n", getOrder(B));
   printf("Size  : %d\n\n", getSize(B));
   printGraph(stdout, B);
   printf("\n");

   BFS(B, 1);
   printf("1 --> 7 Distance : %d\n", getDist(B, 7));
   printf("Vertex 7 Parent  : %d\n", getParent(B, 7));
   printf("Path to Vertex 7 : ");
   getPath(p, B, 7);
   printList(stdout, p);
   printf("\n");

   dist = getDist(B, 3);
   if(dist != INF)
      printf("1 --> 3 Distance : %d\n", dist); 
   else
      printf("1 --> 3 Distance : infinity\n");
   getPath(p, A, 3);
   if(front(p) == NIL)
      printf("Path to Vertex 3 : DNE");
   else{
      printf("Path to Vertex 3 : ");
      printList(stdout, p);
   }
   printf("\n---------------------------------\n\n");

   freeList(&p);
   freeGraph(&A);
   freeGraph(&B);
   return 0;
}

/*
Undirected Graph
---------------------------------
Order : 7
Size  : 8

1: 2 3 4 7 
2: 1 4 5 
3: 1 
4: 1 2 
5: 2 6 
6: 5 7 
7: 1 6 

1 --> 7 Distance : 1
Vertex 7 Parent  : 1
Path to Vertex 7 : 1 7 
---------------------------------


Graph CLEARED
---------------------------------
1 --> 7 Distance : infinity

Path to Vertex 7 : DNE
---------------------------------


Directed Graph
---------------------------------
Order : 7
Size  : 9

1: 2 
2: 4 5 
3: 1 
4: 1 
5: 6 
6: 5 7 
7: 1 

1 --> 7 Distance : 4
Vertex 7 Parent  : 6
Path to Vertex 7 : 0 1 2 5 6 7 
1 --> 3 Distance : infinity
Path to Vertex 3 : DNE
---------------------------------
*/