/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdlib.h>
#include<stdio.h>
#include"BigInteger.h"
#include"List.h"
#define MAX_LEN 160

int main(int argc, char *argv[]){
    
    FILE *input, *output;
    int a, b;

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
    rewind(input);

    fscanf(input, "%d\n", &a);
    a = a + 2;
    char lineA[a];
    fgets(lineA, a, input);
    BigInteger A = stringToBigInteger(lineA);

    fscanf(input, "%d\n", &b);
    b = b + 2;
    char lineB[b];
    fgets(lineB, b, input);
    BigInteger B = stringToBigInteger(lineB);

    // A
    printBigInteger(output, A);     
    // B
    printBigInteger(output, B);    
    // A + B
    BigInteger Eq = sum(A, B);       
    printBigInteger(output, Eq);
    // A - B
    subtract(Eq, A, B);      
    printBigInteger(output, Eq);
    // A - A
    subtract(Eq, A, A);      
    printBigInteger(output, Eq);
    // 3A - 2B
    BigInteger const1 = stringToBigInteger("3");
    BigInteger const2 = stringToBigInteger("2");
    BigInteger FA = prod(A, const1);
    BigInteger FB = prod(B, const2);
    subtract(Eq, FA, FB);   
    printBigInteger(output, Eq);
    // AB
    multiply(Eq, A, B);
    printBigInteger(output, Eq);
    // A^2
    BigInteger A2 = prod(A, A);
    printBigInteger(output, A2);
    // B^2
    BigInteger B2 = prod(B, B);
    printBigInteger(output, B2);
    // 9A^4 + 16B^5
    BigInteger const3 = stringToBigInteger("9");
    BigInteger const4 = stringToBigInteger("16");
    BigInteger A4 = prod(A2, A2);    
    multiply(FA, const3, A4);       // FA = 9A^4
    BigInteger B4 = prod(B2, B2);    
    BigInteger B5 = prod(B4, B);
    multiply(FB, const4, B5);       //FB = 16B^5
    add(Eq, FA, FB);
    printBigInteger(output, Eq);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&Eq);
    freeBigInteger(&A2);
    freeBigInteger(&B2);
    freeBigInteger(&A4);
    freeBigInteger(&B4);
    freeBigInteger(&B5);
    freeBigInteger(&FA);
    freeBigInteger(&FB);

    freeBigInteger(&const1);
    freeBigInteger(&const2);
    freeBigInteger(&const3);
    freeBigInteger(&const4);    
    
    return 0;
}