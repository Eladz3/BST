/****************
    Elad Zohar
    ezohar
    pa4
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
    int *discover;
    int *finish;
    int order;
    int size;
} GraphObj;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->order = n;
    G->size = 0;

    G->adj = calloc((n + 1), sizeof(List));
    G->color = calloc((n + 1), sizeof(int));
    G->parent = calloc((n + 1), sizeof(int));
    G->discover = calloc((n + 1), sizeof(int));
    G->finish = calloc((n + 1), sizeof(int));
    for(int i = 1; i < n + 1; i++){
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        free((*pG)->discover);
        free((*pG)->finish);
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

int getOrder(Graph G){
    return(G->order);
}

int getSize(Graph G){
    return(G->size);
}

int getParent(Graph G, int u){
    testRange(G, u);
    return(G->parent[u]);
}

int getDiscover(Graph G, int u){
    testRange(G, u);
    return(G->discover[u]);
}

int getFinish(Graph G, int u){
    testRange(G, u);
    return(G->finish[u]);
}

// Manipulation procedures ---------------------------------------------------------------------------

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

void Visit(Graph G, List S, int u, int *time){
    G->discover[u] = ++(*time);
    G->color[u] = GRAY;
    List A = G->adj[u];
    for(moveFront(A); index(A) > -1; moveNext(A)){
        int v = get(A);
        if(G->color[v] == WHITE){
            G->parent[v] = u;
            Visit(G, S, v, time);
        }
    }
    G->color[u] = BLACK;
    G->finish[u] = ++(*time);
    prepend(S, u);
}

void DFS(Graph G, List S){
    for(int i = 1; i < G->order + 1; i++){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    int time = 0;
    List cS = copyList(S);
    clear(S);
    for(moveFront(cS); index(cS) > -1; moveNext(cS)){
        if(G->color[get(cS)] == WHITE){
            Visit(G, S, get(cS), &time);
        }
    }
    freeList(&cS);
}

// Other operations ----------------------------------------------------------------------------------

Graph transpose(Graph G){
    Graph T = newGraph(G->order);
    for(int i = 1; i < G->order + 1; i++){
        List L = G->adj[i];
        for(moveFront(L); index(L) > -1; moveNext(L)){
            addArc(T, get(L), i);
        }
    }
    return(T);
}

Graph copyGraph(Graph G){
    Graph C = newGraph(G->order);
    C->size = G->size;
    for(int i = 1; i < G->order + 1; i++){
        C->adj[i] = copyList(G->adj[i]);
        C->color[i] = G->color[i];
        C->parent[i] = G->parent[i];
        C->discover[i] = G->discover[i];
        C->finish[i] = G->finish[i];
    }
    return(C);
}

void printGraph(FILE* out, Graph G){
    for(int i = 1; i < G->order + 1; i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}