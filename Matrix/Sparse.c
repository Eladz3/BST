/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"
#include"List.h"
#define MAX_LEN 160

int main(int argc, char *argv[]){
    
    FILE *input, *output;
    int cnt = 0;
    char line[MAX_LEN];                                 //feeds in one line of input
    int n, a, b;


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
        
    rewind(input);
    fgets(line, MAX_LEN, input);
    sscanf(line, "%d %d %d", &n, &a, &b);

    if (cnt < a+b+3){
        printf("Error: not enough args in file\n");
        exit(1);
    }

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int r, c;
    double d;

    fgets(line, MAX_LEN, input);                            //skipping space line
    for(int i = 0; i < a; i++){
        fgets(line, MAX_LEN, input);
        sscanf(line, "%d %d %lf", &r, &c, &d);
        changeEntry(A, r, c, d);
    }
    fprintf(output, "A has %d non-zero entries:\n", a);     //printing A
    printMatrix(output, A);
    fprintf(output, "\n");

    fgets(line, MAX_LEN, input);                            //skipping space line
    for(int i = 0; i < b; i++){
        fgets(line, MAX_LEN, input);
        sscanf(line, "%d %d %lf", &r, &c, &d);
        changeEntry(B, r, c, d);
    }
    fprintf(output, "B has %d non-zero entries:\n", b);     //printing B
    printMatrix(output, B);
    fprintf(output, "\n");

    double scalar = 1.5;
    Matrix C = scalarMult(scalar, A);
    fprintf(output, "(%.1lf)*A = \n", scalar);                //printing scalar multiple
    printMatrix(output, C);
    fprintf(output, "\n");

    C = sum(A, B);
    fprintf(output, "A+B = \n");                            //printing A + B
    printMatrix(output, C);
    fprintf(output, "\n");

    C = sum(A, A);
    fprintf(output, "A+A = \n");                            //printing A + A
    printMatrix(output, C);
    fprintf(output, "\n");

    C = diff(B, A);
    fprintf(output, "B-A = \n");                            //printing B - A
    printMatrix(output, C);
    fprintf(output, "\n");

    C = diff(A, A);
    fprintf(output, "A-A = \n");                            //printing A - A
    printMatrix(output, C);
    fprintf(output, "\n");

    C = transpose(A);
    fprintf(output, "Transpose(A) = \n");                   //printing Transpose of A
    printMatrix(output, C);
    fprintf(output, "\n");

    C = product(A, B);
    fprintf(output, "A*B = \n");                            //printing A * B
    printMatrix(output, C);
    fprintf(output, "\n");

    C = product(B, B);
    fprintf(output, "B*B = \n");                            //printing B * B
    printMatrix(output, C);
    fprintf(output, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    fclose(input);
    fclose(output);
    return 0;
}