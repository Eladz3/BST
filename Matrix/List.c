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

struct NodeObj{
    void *pData;
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

Node newNode(void *pData){
   Node N = malloc(sizeof(NodeObj));
   N->pData = pData;
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
   if(pL!=NULL && *pL!=NULL) { 
      while((*pL)->length !=0 ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

int isEmpty(List L){
   return(L->length==0);
}

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

void *front(List L){
    testNull(L);
    return(L->front->pData);
}

void *back(List L){
    testNull(L);
    return(L->back->pData);
}

void *get(List L){
    testNull(L);
 
    if(L->cursor == NULL){
        printf("Error: Calling get() when cursor is null\n");
        exit(1);
    }
    else
        return(L->cursor->pData);
}

// Manipulation procedures ----------------------------------------------------

void clear(List L){                     //I'm testing whether or not it is empty in the while loop?
    testNull(L);
    while(L->length != 0)
        deleteFront(L);
}

void moveFront(List L){
    testNull(L);

    L->cursor = L->front;
    L->cursorIndex = 0; 
}

void moveBack(List L){
    testNull(L);

    L->cursor = L->back;
    L->cursorIndex = L->length-1;
}

void movePrev(List L){
    testNull(L);
    
    if(L->cursorIndex == 0){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else if(L->cursorIndex > 0){
        L->cursor = L->cursor->prev;
        L->cursorIndex--;
    }
    else
        printf("Attention: Cursor hasn't been set\n");
}

void moveNext(List L){
    testNull(L);

    if(L->cursorIndex == L->length-1){
        L->cursor = NULL;
        L->cursorIndex = -1;
    }
    else if(L->cursorIndex >= 0){
        L->cursor = L->cursor->next;
        L->cursorIndex++;
    }
    else
        printf("Attention: Cursor hasn't been set\n");
}

void prepend(List L, void *pData){
    testNull(L);
    
    Node newCell = newNode(pData);  
    Node frontCell = L->front;      
    if (isEmpty(L))
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

void append(List L, void *pData){
    testNull(L);


    Node newCell = newNode(pData);   
    Node lastCell = L->back;  
    
    if (L->length == 0)                     
        L->front = newCell;
    else{
        lastCell->next = newCell;
        newCell->prev = lastCell; 
    }
    L->back = newCell;
    L->length++;
}

void insertBefore(List L, void *pData){
    testNull(L);
    testCursor(L);

    Node newCell = newNode(pData);
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

void insertAfter(List L, void *pData){
    testNull(L);
    testCursor(L);

    Node newCell = newNode(pData);
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

