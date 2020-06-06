/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"BigInteger.h"
#include"List.h"
#define POWER 9
#define BASE 1000000000
extern size_t strlen(const char *str);

// Exported type -------------------------------------------------------------

struct BigIntegerObj{
    int sign;
    List digits; 
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

BigInteger newBigInteger(void){
    BigInteger B = malloc(sizeof(BigIntegerObj));
    B->sign = 0;
    B->digits = newList();
    return(B);
}       //done//                      

void freeBigInteger(BigInteger* pN){
   if(pN!=NULL && *pN!=NULL){ 
      freeList(&(*pN)->digits);
      free((*pN)->digits);
      free(*pN);
      *pN = NULL;
   }
}       //done//

// Access functions -----------------------------------------------------------

void testBNull(BigInteger N){
    if(N == NULL){
        printf("Error: Big Integer doesn't exist");
        exit(1);
    }
}       //helper function//

void flip(List N){               //flips every value in the list to opposite sign
    for(moveFront(N); index(N) >= 0; moveNext(N)){
        set(N, (get(N) * (-1)));
    }
}       //helper function//

void carryClean(List L){
    long carry = 0;
    for(moveBack(L); index(L) >= 0; movePrev(L)){
        long node = get(L);
        node += carry;
        
        carry = 0;
        set(L, node);
        if(node < 0){
            node = node * (-1);
            carry = node / BASE;
            carry++;
            carry = carry * (-1);
            long temp = node % BASE;
            node = BASE - temp;
            set(L, node);
        }
        else if(node > BASE){
            carry = node / BASE;
            set(L, (node % BASE));
        }
        else
            carry = 0;
    }

    if(carry >= 1)
        prepend(L, carry);
    else if(carry <= -1){
        flip(L);
        carryClean(L);
    }

    if(front(L) == 0){
        deleteFront(L);
    }
}       //helper function//

int sign(BigInteger N){
    testBNull(N);
    return(N->sign);
}       //done//

int compare(BigInteger A, BigInteger B){
    testBNull(A); testBNull(B);

    if(A->sign < B->sign) // A is zero and B is positive, or A is negative and B is zero or positive
        return -1;
    if(A->sign > B->sign) // B is zero and A is positive, or B is negative and A is zero or positive
        return 1;
    if(A->sign == 0 && B->sign == 0) // both A and B are zero
        return 0;
    if(A->sign == -1){                             //if sign of A == -1 then sign of B == -1 at this point
        if(length(A->digits) < length(B->digits))  // A has less digits so it is greater than B for sure
            return 1;
        else if(length(A->digits) > length(B->digits)) // B has less digits so it is greater than A for sure
            return -1;
        else{  // both A and B have same number of digits
            moveFront(A->digits); moveFront(B->digits);
            while(index(A->digits) != -1){
                long dA = get(A->digits); long dB = get(B->digits);
                if(dA < dB) 
                    return 1;
                else if(dA > dB)
                    return -1;
                else{
                    moveNext(A->digits); moveNext(B->digits);
                }
            }
            return 0;
        }
    }
    if(A->sign == 1){                               //if sign of A == 1 then sign of B == 1 at this point
        if(length(A->digits) < length(B->digits))
            return -1;
        else if(length(A->digits) > length(B->digits))
            return 1;
        else{
            moveFront(A->digits); moveFront(B->digits);
            while(index(A->digits) != -1){
                long dA = get(A->digits); long dB = get(B->digits);
                if(dA < dB)
                    return -1;
                else if(dA > dB)
                    return 1;
                else{
                    moveNext(A->digits); moveNext(B->digits);
                }
            }
            return 0;
        }
    }
    return 0;
}       //done//

int equals(BigInteger A, BigInteger B){
    testBNull(A); testBNull(B);

    if(A->sign == 0 && B->sign == 0)
        return 1;
    if(A->sign != B->sign)
        return 0;
    List LA = A->digits;
    List LB = B->digits;

    moveFront(LA); moveFront(LB);
    if(length(LA) != length(LB)){
        return 0;
    }

    while(index(LA) != -1){
        if(get(LA) != get(LB)){
            return 0;
        }
        moveNext(LA); moveNext(LB);
    }
    return 1;
}       //done//

// Manipulation procedures ----------------------------------------------------

void makeZero(BigInteger N){
    testBNull(N);
    N->sign = 0;
    clear(N->digits);
}       //done//

void negate(BigInteger N){
    testBNull(N);
    N->sign = N->sign * (-1);
}       //done//

// BigInteger Arithmetic operations -----------------------------------------------

BigInteger stringToBigInteger(char* s){
    BigInteger N = newBigInteger();
    int result = 0;
    int strSize = strlen(s);

    if(s[strSize - 1] == '\n'){
        s[strSize - 1] = '\0';
        strSize--;
    }
    
    if(s[0] == '+'){
        N->sign = 1;
        s++;
        strSize--;
    }
    else if(s[0] == '-'){
        N->sign = -1;
        s++;
        strSize--;
    }
    else
        N->sign = 1;

    int i = 0;
    if(strSize % POWER != 0)
    {
        for(; i < (strSize % POWER); i++){
            result = result * 10 + s[i] - '0';
        }
    }
    
    if(result != 0)
        append(N->digits, result);
    result = 0;
    
    while(s[i] != '\0')
    {
        for(int j = 0; j < POWER; j++)
        {
            result = result * 10 + s[i] - '0';
            i++;
        }
        append(N->digits, result);
        result = 0;
    }
    return(N);
}       //done//

BigInteger copy(BigInteger N){
    BigInteger C = newBigInteger();
    List LN = N->digits;
    C->sign = N->sign;
    long c;
    
    for(moveBack(LN); index(LN) > -1; movePrev(LN)){
        c = get(LN);
        prepend(C->digits, c);
    }
    return(C);
}       //done//

void add(BigInteger S, BigInteger A, BigInteger B){    
    makeZero(S);
    List LS = S->digits;
    List LA = A->digits;
    List LB = B->digits;
    
    BigInteger temp = copy(B);
    negate(temp);
    if(equals(A,temp)){
        freeBigInteger(&temp);
        return;
    }
    freeBigInteger(&temp);

    int flipA = 0; int flipB = 0;
    if(A->sign == -1){
        flip(LA);
        flipA = 1;
    }
    if(B->sign == -1){
        flip(LB);
        flipB = 1;
    }

    moveBack(LA); moveBack(LB);
    while(index(LA) > -1 && index(LB) > -1){
        long digit = get(LA) + get(LB);
        prepend(LS, digit);
        movePrev(LA); movePrev(LB);
    }

    if(index(LA) != -1){
        while(index(LA) >= 0){
            prepend(LS, get(LA));
            movePrev(LA);
        }
    }
    else if(index(LB) != -1){
        while(index(LB) >= 0){
            prepend(LS, get(LB));
            movePrev(LB);
        }
    }

    if (flipA == 1)
        flip(LA);
    if (flipB == 1)
        flip(LB);
    
    if (front(LS) < 0)
    {
        S->sign = -1;
        flip(LS);
    }
    else
        S->sign = 1;
    carryClean(LS);
}       //done//

BigInteger sum(BigInteger A, BigInteger B){     //return A + B
    BigInteger S = newBigInteger();
    add(S, A, B);
    return(S);
}       //done//

void subtract(BigInteger D, BigInteger A, BigInteger B){
    makeZero(D);
    List LD = D->digits;
    List LA = A->digits;
    List LB = B->digits;
    
    if(equals(A, B) == 1){
        return;
    }
    
    int flipA = 0;
    int flipB = 0;
    if(A->sign == -1){
        flip(LA);
        flipA = 1;
    }
    if(B->sign == -1){
        flip(LB);
        flipB = 1;
    }

    moveBack(LA); moveBack(LB);
    while(index(LA) > -1 && index(LB) > -1){
        long digit = get(LA) - get(LB);
        prepend(LD, digit);
        movePrev(LA); movePrev(LB);
    }

    if(index(LA) != -1){
        while(index(LA) >= 0){
            prepend(LD, get(LA));
            movePrev(LA);
        }
    }
    else if(index(LB) != -1){
        while(index(LB) >= 0){
            prepend(LD, get(LB) * (-1));
            movePrev(LB);
        }
    }

    if (flipA == 1)
        flip(LA);
    if (flipB == 1)
        flip(LB);
    
    if (front(LD) < 0)
    {
        D->sign = -1;
        flip(LD);
    }
    else
        D->sign = 1;
    carryClean(LD);
}       //done//

BigInteger diff(BigInteger A, BigInteger B){
    BigInteger D = newBigInteger();
    subtract(D, A, B);
    return(D);
}       //done//

void multiply(BigInteger P, BigInteger A, BigInteger B){ 
    makeZero(P);
    if(sign(A) == 0 || sign(B) == 0){
        return;
    }

    BigInteger N1 = newBigInteger();    BigInteger N2 = newBigInteger();
    List LN1 = N1->digits;              List LN2 = N2->digits;
    BigInteger T = NULL;
    List LP = P->digits;
    List LA = A->digits;
    List LB;
    int zCnt = 0;

    if(equals(A, B)){                                   // ensures that if pointing at the same BigInt, it won't bug out
        T = copy(B);
        LB = T->digits;
    }
    else
        LB = B->digits;

    for(moveBack(LB); index(LB) >= 0; movePrev(LB)){
        clear(LN2);
        long x = get(LB);
        for(int i = 0; i < zCnt; i++)
            append(LN2, 0);
        for(moveBack(LA); index(LA) >= 0; movePrev(LA)){
            long node = x * get(LA);
            prepend(LN2, node);
        }
        carryClean(LN2);
        clear(LN1);
        for(moveFront(LP); index(LP) >= 0; moveNext(LP)){
            append(LN1, get(LP));
        }
        clear(LP);
        moveBack(LN2); moveBack(LN1);
        while(index(LN2) >= 0 && index(LN1) >= 0){
            long node = get(LN2) + get(LN1);
            prepend(LP, node);
            movePrev(LN2); movePrev(LN1);
        }
        if(index(LN1) != -1){
            while(index(LN1) >= 0){
                prepend(LP, get(LN1));
                movePrev(LN1);
            }
        }
        else if(index(LN2) != -1){
            while(index(LN2) >= 0){
                prepend(LP, get(LN2));
                movePrev(LN2);
            }
        }
        zCnt++;
    }
    carryClean(LP);
    
    if(A->sign != B->sign)
        P->sign = -1;
    else
        P->sign = 1;
    
    freeBigInteger(&N1);
    freeBigInteger(&N2);
    freeBigInteger(&T);
}       //done//

BigInteger prod(BigInteger A, BigInteger B){
    BigInteger P = newBigInteger();
    multiply(P, A, B);
    return(P);
}       //done//

// Other operations -----------------------------------------------------------
void printBigInteger(FILE* out, BigInteger N){
    List LN = N->digits;
    if(length(LN) == 0){
        fprintf(out, "0\n\n");
        return;
    }
    if(N->sign == -1)
        fprintf(out, "-");

    long numDigits;
    char str[160];
    for(moveFront(LN); index(LN) >= 0; moveNext(LN)){
        long node = get(LN);
        sprintf(str, "%li", node);
        numDigits = strlen(str);
        if(index(LN) != 0){
            for(int i = POWER - numDigits; i > 0; i--)
                fprintf(out, "0");
        }
        fprintf(out, "%li", node);
    }
    fprintf(out, "\n\n");
}       //done//

