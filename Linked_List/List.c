/****************
   Elad Zohar
   ezohar
   pa1
****************/

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;
typedef struct NodeObj* Node;

// private ListObj type
struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int cursorIndex;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

Node newNode(int data){
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

void testEmpty(List L){
    if(L->length==0){
        printf("Error: List is empty\n");
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

int front(List L){
    testNull(L);
    testEmpty(L);
    return(L->front->data);
}

int back(List L){
    testNull(L);
    testEmpty(L);
    return(L->back->data);
}

int get(List L){
    testNull(L);
    testEmpty(L);
    return(L->cursor->data);
}

int equals(List A, List B){
    if(A==NULL || B==NULL){
        printf("Error: One or both of these lists don't exist\n");
        exit(1);
    }
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

void clear(List L){
    testNull(L);
    
    while(L->length != 0){
        deleteFront(L);
    }
    L->cursorIndex = -1;
}

void moveFront(List L){
    testNull(L);
    testEmpty(L);

    L->cursor = L->front;
    L->cursorIndex = 0; 
}

void moveBack(List L){
    testNull(L);
    testEmpty(L);

    L->cursor = L->back;
    L->cursorIndex = L->length-1;
}

void movePrev(List L){
    testNull(L);
    testEmpty(L);
    
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
    testEmpty(L);

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

void prepend(List L, int data){
    testNull(L);
    
    Node newCell = newNode(data);  
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

void append(List L, int data){
    testNull(L);

    Node newCell = newNode(data);   
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

void insertBefore(List L, int data){
    testNull(L);
    testEmpty(L);
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

void insertAfter(List L, int data){
    testNull(L);
    testEmpty(L);
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
    testEmpty(L);
    
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
    else{
        L->front = L->back = NULL;
    }
    L->length--;
    freeNode(&deleteMe);
}

void deleteBack(List L){
    testNull(L);
    testEmpty(L);

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
    testEmpty(L);
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

// Other Functions ------------------------------------------------------------

void printList(FILE* f,List L){
    testNull(L);
    testEmpty(L);

    for(Node N = L->front; N != NULL; N = N->next){
        printf("%d ", N->data);
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
    testEmpty(A);
    testNull(B);
    testEmpty(B);

    List C = newList();

    for(Node N = A->front; N != NULL; N = N->next){
        append(C, N->data);
    }
    for(Node N = B->front; N != NULL; N = N->next){
        append(C, N->data);
    }
    return(C);
}
//--------- Quiz 1 stuff --------------------------------
int searchList(List L, int x){
    for(moveFront(L); index(L) >= 0; moveNext(L)){
        if(get(L) == x){
            return index(L) + 1; 
        }
    }
    return -1;
}

int isPalindrome(List L)
{
    List temp;
    temp = copyList(L);
    moveFront(L);
    moveBack(temp);
    for(int i = 0; i <= length(L)/2; i++)
    {
        if(get(L) != get(temp))
        {
            freeList(&temp);
            return 0;
        }
        else
        {
            moveNext(L);
            movePrev(temp);
        }
    }
    freeList(&temp);
    return 1;
}