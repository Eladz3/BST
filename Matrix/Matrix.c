/****************
    Elad Zohar
    ezohar  
    pa2
****************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

// Structs --------------------------------------------------------------------
typedef struct EntryObj* Entry;

struct EntryObj{
    int index;
    double data;    
} EntryObj;

struct MatrixObj{
    int NNZ;
    int size;
    List *row;        
} MatrixObj;

// Constructors-Destructors --------------------------------------------------------------------------

Entry newEntry(int i, double d){
    Entry E = malloc(sizeof(EntryObj));
    E->index = i;
    E->data = d;
    return(E);
}

void freeEntry(Entry *pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n){
    if(n < 1){
        printf("Error: Matrix size cannot be less than 1");
        exit(1);
    }
    Matrix M = malloc(sizeof(MatrixObj));
    M->row = malloc(sizeof(List) * (n+1));
    
    for(int i = 1; i <= n; i++){
        M->row[i] = newList();
    }
    M->NNZ = 0;
    M->size = n;
    return M;
}                               

void freeMatrix(Matrix *pM){
    if(pM!=NULL && *pM!=NULL){
        for(int i = 1; i <= (*pM)->size; i++){
            if((*pM)->row[i] != NULL){
                freeList(&(*pM)->row[i]);
            }
        }
        free((*pM)->row);
        free(*pM);
        *pM = NULL;
    }
}                   

// Access functions ----------------------------------------------------------------------------------
void testMatrixNull(Matrix M){
    if(M == NULL){
        printf("Error: Matrix does not exist");
        exit(1);
    }
}

int size(Matrix M){
    testMatrixNull(M);
    return(M->size);
}

int NNZ(Matrix M){
    testMatrixNull(M);
    return(M->NNZ);
}

int equals(Matrix A, Matrix B){
    testMatrixNull(A);
    testMatrixNull(B);
    if(A == B)
        return 1;
    if(A->size != B->size)
        return 0;
    if(A->NNZ == 0 && B->NNZ == 0)
        return 1;
    if(A->NNZ != B->NNZ)
        return 0;
    for(int i = 1; i <= A->size; i++)
    {
        List P = A->row[i];
        List Q = B->row[i];
        moveFront(P);
        moveFront(Q);
        if(length(P) != length(Q))
            return 0;
        
        for(int j = 0; j < length(P); j++){
            Entry eP = get(P);
            Entry eQ = get(Q);
            if(eP->index != eQ->index || eP->data != eQ->data)
                return 0;
            moveNext(P);
            moveNext(Q);
            if(index(P) == -1 || index(Q) == -1)
                break;
        }
    }
    return 1;
}                        

// Manipulation procedures ---------------------------------------------------------------------------
void addToEntry(Matrix M, int i, int j, double x){
    testMatrixNull(M);
    if(i > M->size || j > M->size){
        printf("Error: Row or column searched for does not exist in matrix");
        exit(1);
    }
    List R = M->row[i];
    Entry E = newEntry(j, x);
    if(M->NNZ == 0 && x != 0){              //0 matrix, but x = non-zero value       ADD NEW VALUE
        append(R, E);
        M->NNZ++;
    }
    else if(M->NNZ != 0 && x != 0){              //populated matrix & x = non zero value  ADD NEW OR REPLACE
        if(length(R) == 0){
            append(R, E);
            M->NNZ++;
        }
        else{
            moveFront(R);
            Entry F = get(R);
            while(F->index < j && index(R) != -1){
                moveNext(R);
                if(index(R) > -1){
                    F = get(R);
                }
            }
            if(F->index == j){               //index exists - replacing entry here
                E->data = E->data + F->data;
                if(E->data == 0){
                    delete(R);
                    M->NNZ--;
                }
                else{
                    insertBefore(R, E);
                    delete(R);
                }
            }
            else if(F->index < j){
                append(R, E);
                M->NNZ++;
            }
            else{                            //index does not exist in row - inserting new entry
                insertBefore(R, E);
                M->NNZ++;
            }
        }
    }    
}       //helper function//

double vectorDot(List P, List Q){
    double sum = 0;
    if(length(P) > 0 && length(Q) > 0){
        moveFront(P);
        for(int i = 0; i < length(P); i++){
            Entry eP = get(P);
            moveFront(Q);
            for(int j = 0; j < length(Q); j++){
                Entry eQ = get(Q);
                if(eP->index == eQ->index){
                    sum = sum + (eP->data * eQ->data);
                    break;
                }
                else
                    moveNext(Q);
            }
            moveNext(P);
        }
    }
    return sum;
}       //helper function//

void makeZero(Matrix M){
    testMatrixNull(M);
    for(int i = 1; i <= M->size; i++){
        clear(M->row[i]);
    }
    M->NNZ = 0;
}       // CHECK FOR MEMORY LEAKS //

void changeEntry(Matrix M, int i, int j, double x){
    testMatrixNull(M);
    if(i > M->size || j > M->size){
        printf("Error: Row or column searched for does not exist in matrix");
        exit(1);
    }
    List R = M->row[i];
    Entry E = newEntry(j, x);
    Entry F;
    if(M->NNZ != 0 && x == 0){              //matrix has some values and we're DELETING one of them
        if(length(R) > 0){
            moveFront(R);
            F = get(R);
            while(F->index < j && index(R) != -1){
                moveNext(R);
                if(index(R) > -1){
                    F = get(R);
                }
            }
            if(F->index == j){              //delete here
                delete(R);
                M->NNZ--;
            }
        }      
    }
    else if(M->NNZ == 0 && x != 0){              //0 matrix, but x = non-zero value       ADD NEW VALUE
        append(R, E);
        M->NNZ++;
    }
    else if(M->NNZ != 0 && x != 0){              //populated matrix & x = non zero value  ADD NEW OR REPLACE
        if(length(R) == 0){
            append(R, E);
            M->NNZ++;
        }
        else{
            moveFront(R);
            F = get(R);
            while(F->index < j && index(R) != -1){
                moveNext(R);
                if(index(R) > -1){
                    F = get(R);
                }
            }
            if(F->index == j){               //index exists - replacing entry here
                insertBefore(R, E);
                delete(R);
            }
            else if(F->index < j){
                append(R, E);
                M->NNZ++;
            }
            else{                            //index does not exist in row - inserting new entry
                insertBefore(R, E);
                M->NNZ++;
            }
        }
    }
}

// Matrix Arithmetic operations ---------------------------------------------------------------------
Matrix copy(Matrix A){
    Matrix B = newMatrix(A->size);
    for(int i = 1; i <= A->size; i++){
        moveFront(A->row[i]);
        for(int j = 0; j < length(A->row[i]); j++){
            Entry E = get(A->row[i]);
            Entry F = newEntry(E->index, E->data);
            append(B->row[i], F);
            moveNext(A->row[i]);
        }
    }
    B->NNZ = A->NNZ;
    return(B);
}        

Matrix transpose(Matrix A){
    testMatrixNull(A);
    Matrix M = newMatrix(A->size);

    for(int i = 1; i <= A->size; i++){
        List R = A->row[i];
        moveFront(R);
        for(int j = 1; j <= length(R); j++){
            Entry E = get(R);
            changeEntry(M, E->index, i, E->data);
            moveNext(R);          
        }
    }
    return(M);
}                          

Matrix scalarMult(double x, Matrix A){
    testMatrixNull(A);
    Matrix M = newMatrix(A->size);

    for(int i = 1; i <= A->size; i++){
        List R = A->row[i];
        moveFront(R);
        for(int j = 1; j <= length(R); j++){
            Entry E = get(R);
            changeEntry(M, i, E->index, (E->data)*x);
            moveNext(R);          
        }
    }
    return(M);
}              

Matrix sum(Matrix A, Matrix B){
    testMatrixNull(A);
    testMatrixNull(B);
    if(A->size != B->size){
        printf("Error: Matrices are different sizes");
        exit(1);
    }
    Matrix M = copy(A);
    for(int i = 1; i <= B->size; i++){
        List R = B->row[i];
        moveFront(R);
        for(int j = 1; j <= length(R); j++){
            Entry E = get(R);
            addToEntry(M, i, E->index, E->data);
            moveNext(R);          
        }
    }
    return(M);
}

Matrix diff(Matrix A, Matrix B){
    testMatrixNull(A);
    testMatrixNull(B);
    if(A->size != B->size){
        printf("Error: Matrices are different sizes");
        exit(1);
    }
    Matrix M = copy(A);
    for(int i = 1; i <= B->size; i++){
        List R = B->row[i];
        moveFront(R);
        for(int j = 1; j <= length(R); j++){
            Entry E = get(R);
            addToEntry(M, i, E->index, 0 - E->data);
            moveNext(R);          
        }
    }
    return(M);
}      

Matrix product(Matrix A, Matrix B){
    testMatrixNull(A);
    testMatrixNull(B);
    if(A->size != B->size){
        printf("Error: Matrices are different sizes");
        exit(1);
    }
    Matrix T = transpose(B);
    Matrix M = newMatrix(A->size);
    double prod;

    for(int i = 1; i <= A->size; i++){
        List P = A->row[i];
        for(int j = 1; j <= A->size; j++){
            List Q = T->row[j];
            prod = vectorDot(P, Q);
            changeEntry(M, i, j, prod);
        }
    }
    return(M);
}            

void printMatrix(FILE* out, Matrix M){
    testMatrixNull(M);
    for(int i = 1; i <= M->size; i++){
        List L = M->row[i];
        if(length(L) == 0){
            continue;
        }
        fprintf(out, "%d: ", i);
        moveFront(L); 
        while(index(L) >= 0){
            Entry E = (Entry)get(L);
            fprintf(out, "(%d, %.1lf) ", E->index , E->data);
            moveNext(L);
        }
        fprintf(out, "\n");
    }
}

int getEntryInd(Entry E){
    return(E->index);
}

double getEntryData(Entry E){
    return(E->data);
}


