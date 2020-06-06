/****************
    Elad Zohar
    ezohar
    pa3
****************/

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

int main(int argc, char *argv[]){
    FILE *input, *output;
    
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    
    if(input == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(output == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int vertices, V1, V2;
    rewind(input);
    fscanf(input, "%d", &vertices);
    Graph G = newGraph(vertices);
    while(fgetc(input) != EOF){
        fscanf(input, "%d %d", &V1, &V2);
        if(V1 == 0 && V2 == 0)
            break;
        addEdge(G, V1, V2);
    }
    printGraph(output, G);

    while(fgetc(input) != EOF){
        fscanf(input, "%d %d", &V1, &V2);
        if(V1 == 0 && V2 == 0)
            break;
        BFS(G, V1);
        int dist = getDist(G, V2);
        if(dist == INF)
            fprintf(output, "\nThe distance from %d to %d is infinity\n", V1, V2);
        else
            fprintf(output, "\nThe distance from %d to %d is %d\n", V1, V2, dist);
        List path = newList();
        getPath(path, G, V2);
        if(front(path) == NIL)
            fprintf(output, "No %d-%d path exists", V1, V2);
        else{
            fprintf(output, "A shortest %d-%d path is: ", V1, V2);
            printList(output, path);
        }
        fprintf(output, "\n");
        freeList(&path);
    }

    freeGraph(&G);
    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}