/****************
    Elad Zohar
    ezohar
    pa3
****************/

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
#include"List.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

// Constructors-Destructors --------------------------------------------------------------------------

struct GraphObj{
    List *adj;
    int *color;
    int *parent;
    int *distance;
    int order;
    int size;    
    int source;
} GraphObj;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    G->adj = calloc((n + 1), sizeof(List));
    G->color = calloc((n + 1), sizeof(int));
    G->parent = calloc((n + 1), sizeof(int));
    G->distance = calloc((n + 1), sizeof(int));
    for(int i = 1; i < n + 1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return(G);
}

void freeGraph(Graph* pG){
    if(pG != NULL && *pG != NULL){
        for(int i = 1; i < (*pG)->order + 1; i++)
            freeList(&(*pG)->adj[i]);
        free((*pG)->adj);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        free(*pG);
        *pG = NULL;
    }
}

// Access functions ----------------------------------------------------------------------------------

void testRange(Graph G, int x){
    if(x < 1 || x > getOrder(G)){
        printf("Error: u is not within range\n");
        exit(1);
    }
}

void testSource(Graph G){
    if(getSource(G) == NIL){
        printf("Error: BFS() hasn't been called yet\n");
        exit(1);
    }
}

int getOrder(Graph G){
    return(G->order);
}

int getSize(Graph G){
    return(G->size);
}

int getSource(Graph G){
    return(G->source);
}

int getParent(Graph G, int u){
    testRange(G, u);
    return(G->parent[u]);
}

int getDist(Graph G, int u){
    testRange(G, u);
    return(G->distance[u]);
}

void getPath(List L, Graph G, int u){
    testRange(G, u);
    testSource(G);
    if(u == G->source)
        append(L, u);
    else if(G->parent[u] == NIL)
        append(L, NIL);
    else{
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}

// Manipulation procedures ---------------------------------------------------------------------------

void makeNull(Graph G){
    G->size = 0;
    G->source = NIL;
    for(int i = 1; i < G->order + 1; i++){
        clear(G->adj[i]);
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
}

void addNode(Graph G, int u, int v){
    List L = G->adj[u];
    moveFront(L);
    while(index(L) >= 0 && get(L) < v)
        moveNext(L);
    if(index(L) == -1)
        append(L, v);
    else
        insertBefore(L, v);
}

void addEdge(Graph G, int u, int v){
    testRange(G, u); testRange(G, v);
    addNode(G, u, v);
    addNode(G, v, u);
    G->size++;
}

void addArc(Graph G, int u, int v){
    testRange(G, u); testRange(G, v);
    addNode(G, u, v);
    G->size++;
}

void BFS(Graph G, int s){
    for(int i = 1; i < G->order + 1; i++){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;

    List T = newList();
    append(T, s);
    while(length(T) > 0){
        int x = front(T);
        deleteFront(T);
        List N = G->adj[x];
        for(moveFront(N); index(N) > -1; moveNext(N)){
            int n = (int)get(N);
            if(G->color[n] == WHITE){
                G->color[n] = GRAY;
                G->distance[n] = G->distance[x] + 1;
                G->parent[n] = x;
                append(T, n);
            }
        }
        G->color[x] = BLACK;
    }
    freeList(&T);
}

// Other operations ----------------------------------------------------------------------------------

void printGraph(FILE* out, Graph G){
    for(int i = 1; i < G->order + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}