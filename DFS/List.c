/****************
    Elad Zohar
    ezohar
    pa4
****************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs --------------------------------------------------------------------

struct NodeObj{
   long data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;
typedef struct NodeObj* Node;

struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int cursorIndex;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(long data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = N->next = NULL;
   return(N);
}

List newList(void){
    List L = malloc(sizeof(ListObj));
    L->back = L->cursor = L->front = NULL;
    L->length = 0;
    L->cursorIndex = -1;
    return(L);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL){ 
      while((*pL)->length != 0)
         deleteFront(*pL); 
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

void testNull(List L){
    if(L==NULL){
        printf("Error: List doesn't exist\n");
        exit(1);
    }
}

void testCursor(List L){
    if(L->cursor == NULL || L->cursorIndex == -1){
        printf("Error: Cursor is not set\n");
        exit(1);
    }
}

int length(List L){
    testNull(L);
    return(L->length);
}

int index(List L){
    testNull(L);
    return(L->cursorIndex);
}

long front(List L){
    testNull(L);
    return(L->front->data);
}

long back(List L){
    testNull(L);
    return(L->back->data);
}

long get(List L){
    testNull(L);
    return(L->cursor->data);
}



int equals(List A, List B){
    testNull(A); testNull(B);

    Node n1 = A->front;
    Node n2 = B->front;
    if(A->length != B->length){
        return 0;
    }
    while(n1 != NULL){
        if(n1->data != n2->data){
            return 0;
        }
        n1 = n1->next;
        n2 = n2->next;
    }
    return 1;
}

// Manipulation procedures ----------------------------------------------------

void clear(List L){                     //I'm testing whether or not it is empty in the while loop?
    testNull(L);
    
    while(L->length != 0){
        deleteFront(L);
    }
    L->cursorIndex = -1;
}

void moveFront(List L){
    testNull(L);
    if (L->length == 0)
        return;
    L->cursor = L->front;
    L->cursorIndex = 0;
}

void moveBack(List L){
    testNull(L);
    if (L->length == 0)
        return;
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
}

void movePrev(List L){
    if (L->cursor == NULL)
        return;
    if (L->cursor == L->front){
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    else{
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }
}

void moveNext(List L){
    if (L->cursor == NULL)
        return;
    if (L->cursor == L->back){
        L->cursor = NULL;
        L->cursorIndex = -1;
        return;
    }
    L->cursor = L->cursor->next;
    L->cursorIndex++;
}

void prepend(List L, long data){
    testNull(L);
    
    Node newCell = newNode(data);  
    Node frontCell = L->front;      
    if(L->length == 0)
        L->back = newCell; 
    else{
        frontCell->prev = newCell;
        newCell->next = frontCell;
        if(L->cursorIndex > -1)
            L->cursorIndex++;
    }
    L->front = newCell;
    L->length++;
}

void append(List L, long data){
    testNull(L);

    Node newCell = newNode(data);   
    Node lastCell = L->back;  
    
    if(L->length == 0)                     
        L->front = newCell;
    else{
        lastCell->next = newCell;
        newCell->prev = lastCell; 
    }
    L->back = newCell;
    L->length++;
}

void insertBefore(List L, long data){
    testNull(L);
    testCursor(L);

    Node newCell = newNode(data);
    Node currentCell = L->cursor;
    Node prevCell = L->cursor->prev;

    newCell->next = currentCell;
    currentCell->prev = newCell;
    
    if(L->cursorIndex == 0){
        L->front = newCell;
    }
    else{
        prevCell->next = newCell;
        newCell->prev = prevCell;
    }
    L->cursorIndex++;
    L->length++;
}

void insertAfter(List L, long data){
    testNull(L);
    testCursor(L);

    Node newCell = newNode(data);
    Node currentCell = L->cursor;
    Node nextCell = L->cursor->next;

    newCell->prev = currentCell;
    currentCell->next = newCell;
    
    if(L->cursorIndex == L->length-1){
        L->back = newCell;
    }
    else{
        nextCell->prev = newCell;
        newCell->next = nextCell;
    }
    L->length++;
}

void deleteFront(List L){
    testNull(L);
    
    if(L->cursorIndex == 0){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else{
        L->cursorIndex--;
    }
    
    Node deleteMe = L->front;
    if(L->length > 1){
        L->front = L->front->next;
        L->front->prev = NULL;
    } 
    else 
        L->front = L->back = NULL;
    L->length--;
    freeNode(&deleteMe);
}

void deleteBack(List L){
    testNull(L);
    
    if(L->cursorIndex == L->length-1){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    
    Node deleteMe = L->back;
    if(L->length > 1){  
        L->back = deleteMe->prev;
        L->back->next = NULL;
    }
    else 
        L->front = L->back = NULL; 
    L->length--;
    freeNode(&deleteMe);
}

void delete(List L){
    testNull(L);
    testCursor(L);

    Node deleteMe = L->cursor;
    Node prevCell = L->cursor->prev;
    Node nextCell = L->cursor->next;

    if(L->length > 1){
        if(prevCell == NULL){                   //dealing with first cell in list
            L->front = nextCell;                //front is next cell forward
            L->front->prev = NULL;              //current front ptr has prev ptr = null
        }
        else if(nextCell == NULL){              //dealing with last cell
            L->back = prevCell;                 //back is now prev cell
            L->back->next = NULL;               
        }
        else{                                   //if anywhere else in list
            prevCell->next = nextCell;          
            nextCell->prev = prevCell;
        }
    }
    else
        L->front = L->back = NULL;
    
    L->cursor = NULL;
    L->cursorIndex = -1;
    L->length--;
    freeNode(&deleteMe);
}

void set(List L, long x){
    testNull(L);
    testCursor(L);
    L->cursor->data = x;
}

// Other Functions ------------------------------------------------------------

void printList(FILE* f,List L){
    testNull(L);

    for(Node N = L->front; N != NULL; N = N->next){
        fprintf(f, "%li ", N->data);
    }
}

List copyList(List L){
    testNull(L);
    List copyL = newList();
    for(Node N = L->front; N != NULL; N = N->next){
        append(copyL, N->data);
    }
    return(copyL);
}

List concatList(List A, List B){
    testNull(A);
    testNull(B);
    
    List C = newList();

    for(Node N = A->front; N != NULL; N = N->next){
        append(C, N->data);
    }
    for(Node N = B->front; N != NULL; N = N->next){
        append(C, N->data);
    }
    return(C);
}
