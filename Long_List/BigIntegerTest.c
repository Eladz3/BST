/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"BigInteger.h"
#include"List.h"

int main(){
    
    // int count = 5;
    char s[160] = "123456789876543210101010101010";
    char t[160] = "10101010101010";
    char u[160] = "123456789";
    BigInteger A = stringToBigInteger(s);
    BigInteger B = stringToBigInteger(t);
    BigInteger C = copy(A);
    BigInteger F = stringToBigInteger(u);
    printBigInteger(stdout, A);    
    printBigInteger(stdout, B);
    printBigInteger(stdout, F);


    if(equals(A, B) == 1){
        printf("A and B are equal\n");
    }
    else{
        printf("A and B are NOT equal\n");
    }
    if(equals(A, C)){
        printf("A and C are equal\n\n");
    }
    else{
        printf("A and C are NOT equal\n\n");
    }

    // C = sum(A, B);
    // printBigInteger(stdout, C);

    BigInteger D = diff(A, C);
    printBigInteger(stdout, D);

    BigInteger E = prod(A, D);
    printBigInteger(stdout, E);

    multiply(E, B, F);
    printBigInteger(stdout, E);

    return 0;
}