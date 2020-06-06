/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdlib.h>
#include<stdio.h>
#include"List.h"

#ifndef _BIGINTEGER_H_INCLUDE_
#define _BIGINTEGER_H_INCLUDE_

// Exported type -------------------------------------------------------------

// BigInteger reference type
typedef struct BigIntegerObj* BigInteger;   

// Constructors-Destructors ---------------------------------------------------

// Returns a reference to a new BigInteger object in the zero state.                                            
BigInteger newBigInteger(void);  

// Frees heap memory associated with *pN, sets *pN to NULL.                       
void freeBigInteger(BigInteger* pN);  

// Access functions -----------------------------------------------------------

// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero state.
int sign(BigInteger N);   

// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B);        

// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B);                      

// Manipulation procedures ----------------------------------------------------

// Re-sets N to the zero state.
void makeZero(BigInteger N);                                

// Reverses the sign of N: positive <--> negative. Does nothing if N is in the zero state.
void negate(BigInteger N);

// BigInteger Arithmetic operations -----------------------------------------------

// Returns a reference to a new BigInteger object representing the decimal integer represented in base 10 
// by the string s. Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9} and
// an optional sign {+, -} prefix. 
BigInteger stringToBigInteger(char* s);

// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N);

// Places the sum of A and B in the existing BigInteger S, overwriting its current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B);         

// Returns a reference to a new BigInteger object representing A + B.                                
BigInteger sum(BigInteger A, BigInteger B);

// Places the difference of A and B in the existing BigInteger D, overwriting its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B);

// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B);

// Places the product of A and B in the existing BigInteger P, overwriting its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);

// Other operations -----------------------------------------------------------
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N);

#endif