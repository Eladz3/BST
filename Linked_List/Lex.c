/****************
   Elad Zohar
   ezohar
   pa1
****************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"
#define MAX_LEN 160

int main(int argc, char *argv[]){
    
    FILE *input, *output;
    int cnt = 0;
    char line[MAX_LEN];                                 //feeds in one line of input

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
    while(fgets(line, MAX_LEN, input) != NULL){             //count how many lines in file
      cnt++;
    }
    
    char inputFile[cnt][MAX_LEN];                           //create array that stores all rows of file
    
    rewind(input);
    
    int strIndex = 0;                                   
    while(fgets(line, MAX_LEN, input) != NULL){
        strcpy(inputFile[strIndex], line);
        strIndex++;
    }

    List outputList = newList();    
    append(outputList,0);
    
    for (int i = 1; i < cnt; i++) {
        moveFront(outputList);
        while(index(outputList)>=0){
            if(strcmp(inputFile[i],inputFile[get(outputList)])>0){
                if(get(outputList) == back(outputList)){
                    insertAfter(outputList, i);
                    moveBack(outputList);
                    moveNext(outputList);
                }
                else
                    moveNext(outputList);
            }
            else{
                insertBefore(outputList, i);
                moveBack(outputList);
                moveNext(outputList);
            }
        }
    }

    moveFront(outputList);
    while(index(outputList) != -1){
        fprintf(output, "%s", inputFile[get(outputList)]);
        moveNext(outputList);
    }
    freeList(&outputList);
    fclose(input);
    fclose(output);

return 0;
}
