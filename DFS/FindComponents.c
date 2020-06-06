/****************
    Elad Zohar
    ezohar
    pa4
****************/

#include<stdlib.h>
#include<stdio.h>
#include"Graph.h"
#include"List.h"

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

    int order, V1, V2, i, cnt = 0;
    List S = newList();
    List component = newList();
    
    rewind(input);
    fscanf(input, "%d", &order);
    Graph G = newGraph(order);
    while(fgetc(input) != EOF){
        fscanf(input, "%d %d", &V1, &V2);
        if(V1 == 0 && V2 == 0)
            break;
        addArc(G, V1, V2);
    }
    
    for(i = 1; i <= getOrder(G); i++)
        append(S, i);

    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);
    fprintf(output, "\n");

    DFS(G, S);
    Graph C = copyGraph(G);
    Graph T = transpose(C);
    DFS(T, S);
    
    for(i = 1; i <= getOrder(G); i++){
        if(getParent(T, i) == NIL){
            cnt++;
        }
    }
    fprintf(output, "G contains %d strongly connected components:\n", cnt);
    
    cnt = 0;
    for(moveBack(S); index(S) > -1; movePrev(S)){
        cnt++;
        clear(component);
        prepend(component, get(S));
        fprintf(output, "Component %d: ", cnt);
        while(getParent(T, get(S)) != NIL){
            movePrev(S);
            prepend(component, get(S));
        }
        printList(output, component);
        fprintf(output, "\n");
    }
    
    
    // while(fgetc(input) != EOF){
    //     fscanf(input, "%d %d", &V1, &V2);
    //     if(V1 == 0 && V2 == 0)
    //         break;
    //     BFS(G, V1);
        
    //     int dist = getDist(G, V2);
    //     if(dist == UNDEF)
    //         fprintf(output, "\nThe distance from %d to %d is infinity\n", V1, V2);
    //     else
    //         fprintf(output, "\nThe distance from %d to %d is %d\n", V1, V2, dist);
    //     List path = newList();
    //     getPath(path, G, V2);
    //     if(front(path) == NIL)
    //         fprintf(output, "No %d-%d path exists", V1, V2);
    //     else{
    //         fprintf(output, "A shortest %d-%d path is: ", V1, V2);
    //         printList(output, path);
    //     }
    //     fprintf(output, "\n");
    //     freeList(&path);
    // }

    freeGraph(&C);
    freeGraph(&T);
    freeGraph(&G);
    freeList(&S);
    fclose(input);
    fclose(output);
    return EXIT_SUCCESS;
}