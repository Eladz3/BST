/****************
    Elad Zohar
    ezohar
    pa4
****************/

#include<stdlib.h>
#include<stdio.h>
#include"List.h"

#define UNDEF -1
#define NIL 0

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

typedef struct GraphObj* Graph;
// Constructors-Destructors --------------------------------------------------------------------------

//returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);
//frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph* pG);

// Access functions ----------------------------------------------------------------------------------

//returns order of G
int getOrder(Graph G);
//returns size of G
int getSize(Graph G);
//will return the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called
//precondition 1 <= u <= n <= getOrder(G)
int getParent(Graph G, int u);
//returns the time vertex u is discovered in DFS()
//precondition 1 <= u <= n <= getOrder(G)
int getDiscover(Graph G, int u);
//returns the time vertex u is closed in DFS()
//precondition 1 <= u <= n <= getOrder(G)
int getFinish(Graph G, int u);

// Manipulation procedures ---------------------------------------------------------------------------

//inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
//precondition that two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);
//inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v)
//precondition that two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);
//runs the DFS algorithm on the Graph G in order of List S, setting the color, discover time, parent, finish time of G accordingly
void DFS(Graph G, List S);

// Other operations ----------------------------------------------------------------------------------

//returns a reference to a transpose of graph G.
Graph transpose(Graph G);
//returns a copy of graph G
Graph copyGraph(Graph G); 
//prints the adjacency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif