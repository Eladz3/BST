/****************
   Elad Zohar
   ezohar
   pa5
****************/

#include<stdio.h>
#include<stdlib.h>
#include "Dictionary.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   KEY_TYPE key;
   VAL_TYPE val;
   struct NodeObj* parent;
   struct NodeObj* left;
   struct NodeObj* right;
} NodeObj;
typedef NodeObj* Node;

Node newNode(KEY_TYPE key, VAL_TYPE val){
   Node N = malloc(sizeof(NodeObj));
   N->key = key;
   N->val = val;
   N->parent = N->left = N->right = NULL;
   return(N);
} // done //

void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
} // done //

// private DictionaryObj type
typedef struct DictionaryObj{
   Node root;
   Node cursor;
   int unique;
   int size;
} DictionaryObj;

Dictionary newDictionary(int unique){
   Dictionary D = malloc(sizeof(DictionaryObj));
   D->cursor = NULL;
   D->root = NULL;
   D->unique = unique;                                 // unique == 0 means FALSE; == 1 means TRUE
   D->size = 0;
   return(D);
} // done //

void freeDictionary(Dictionary* pD){
   if(pD != NULL && *pD != NULL){
      makeEmpty(*pD);
      free(*pD);
      *pD = NULL;
   }
} // done //

// Access functions -----------------------------------------------------------

void checkNull(Dictionary D, const char* s){
   if(D == NULL){
      fprintf(stderr, "Dictionary Error: calling %s on NULL Dictionary reference\n", s);
      exit(1);
   }
} // private tester function //

int size(Dictionary D){
   checkNull(D, __func__);
   return(D->size);
} // done //

int getUnique(Dictionary D){
   checkNull(D, __func__);
   return(D->unique);
} // done //

Node findKey(Node N, KEY_TYPE k){
   if(N == NULL || KEY_CMP(k, N->key) == 0){
      return N;
   }
   if(KEY_CMP(k, N->key) < 0){
      return findKey(N->left, k);
   }
   else{
      return findKey(N->right, k);
   }
} // private helper function //

VAL_TYPE lookup(Dictionary D, KEY_TYPE k){      // return int
   checkNull(D, __func__);
   Node N = findKey(D->root, k);
   return(N == NULL ? VAL_UNDEF : N->val);
} // done //


// Manipulation procedures ----------------------------------------------------

void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v){
   checkNull(D, __func__);
   // if Dictionary IS unique and key already exists then duplicate cannot be accepted.
   if(D->unique >= 1 && findKey(D->root, k) != NULL){
      fprintf(stderr, "Dictionary Error: cannot insert() duplicate key: \"%s\" because Dictionary reference is UNIQUE\n", k);
      exit(1);
   }
   // find which node the new node is inserted next to
   Node N = newNode(k, v);
   Node A = D->root;
   Node B = NULL;
   while(A != NULL){
      B = A;
      if(KEY_CMP(k, A->key) < 0){
         A = A->left;
      }
      else{
         A = A->right;
      }
   }
   // insert new node
   if(B == NULL){
      D->root = N;
   }
   else if(KEY_CMP(k, B->key) < 0){
      N->parent = B;
      B->left = N;
   }
   else{
      N->parent = B;
      B->right = N;
   }
   (D->size)++;
} // done //

void delete(Dictionary D, KEY_TYPE k){
   Node N, P, S;
   checkNull(D, __func__);
   N = findKey(D->root, k);
   if(N == NULL){
      fprintf(stderr, 
         "Dictionary Error: cannot delete() non-existent key: \"%s\"\n", k);
      exit(1);
   }
   if(N == D->cursor){
      D->cursor = NULL;
   }

   if(N->left == NULL && N->right == NULL){  // case 1 (has no child)
      if(N == D->root){
         D->root = NULL;
         freeNode(&N);
      }
      else{
         P = N->parent;
         if(P->right == N){
            P->right = NULL;
         }
         else{
            P->left = NULL;  
         }
         freeNode(&N);
      }
   }
   else if(N->right == NULL){  // case 2 (has left child only)
      if(N == D->root){
         D->root = N->left;
         freeNode(&N);
      }
      else{
         P = N->parent;
         if(P->right == N){
            P->right = N->left;
            if(N->left != NULL){
               N->left->parent = P;
            }
         }
         else{
            P->left = N->left;
            if(N->left != NULL){
               N->left->parent = P;
            }
         }
         freeNode(&N);
      }
   }
   else if(N->left == NULL){  // case 3 (has right child only)
      if(N == D->root){
         D->root = N->right;
         freeNode(&N);
      }
      else{
         P = N->parent;
         if(P->right == N){
            P->right = N->right;
            if(N->right != NULL){
               N->right->parent = P;
            }
         }
         else{
            P->left = N->right;
            if(N->right != NULL){
               N->right->parent = P;
            }
         }
         freeNode(&N);
      }
   }
   else{                     // case 4 (has both children)
      S = N->right;
      while(S->left != NULL){
         S = S->left;
      }
      N->key = S->key;
      N->val = S->val;
      P = S->parent;
      if(P->right == S){
         P->right = S->right;
         if(S->right != NULL){
            S->right->parent = P;
         }
      }
      else{
         P->left = S->right;
         if(S->right != NULL){
            S->right->parent = P;
         }
      }
      freeNode(&S);
   } // done //

   (D->size)--;
} // done //

void clearNodes(Node N){
   if(N != NULL){
      clearNodes(N->left);
      clearNodes(N->right);
      freeNode(&N);
   }
} // private helper function //

void makeEmpty(Dictionary D){
   checkNull(D, __func__);
   clearNodes(D->root);
   D->root = NULL;
   D->size = 0;
} // done //

VAL_TYPE beginForward(Dictionary D){
   if(D->root == NULL){
      return VAL_UNDEF;
   }
   Node N = D->root;
   while(N->left != NULL){
      N = N->left;
   }
   D->cursor = N;
   return(N->val);
} // done //

VAL_TYPE beginReverse(Dictionary D){
   if(D->root == NULL){
      return VAL_UNDEF;
   }
   Node N = D->root;
   while(N->right != NULL){
      N = N->right;
   }
   D->cursor = N;
   return(N->val);
} // done //

KEY_TYPE currentKey(Dictionary D){
   if(D->root == NULL || D->cursor == NULL){
      return KEY_UNDEF;
   }
   return(D->cursor->key);
} // done //

VAL_TYPE currentVal(Dictionary D){
   if(D ->root == NULL || D->cursor == NULL){
      return VAL_UNDEF;
   }
   return(D->cursor->val);
} // done //

VAL_TYPE next(Dictionary D){
   Node N;
   if(D->cursor->right != NULL){
      N = D->cursor->right;
      while(N->left != NULL){
         N = N->left;
      }
      D->cursor = N;
      return N->val;
   }
   N = D->cursor->parent;
   while(N != NULL && D->cursor == N->right){
      D->cursor = N;
      N = N->parent;
   }
   D->cursor = N;
   if(N == NULL){
      return VAL_UNDEF;
   }
   return N->val;
} // done //

VAL_TYPE prev(Dictionary D){
   Node N;
   if(D->cursor->left != NULL){
      N = D->cursor->left;
      while(N->right != NULL){
         N = N->right;
      }
      D->cursor = N;
      return N->val;
   }
   N = D->cursor->parent;
   while(N != NULL && D->cursor == N->left){
      D->cursor = N;
      N = N->parent;
   }
   D->cursor = N;
   if(N == NULL){
      return VAL_UNDEF;
   }
   return N->val;
} // done //


// Other operations -----------------------------------------------------------

void printDictionary(FILE* out, Dictionary D){
   if(D->root == NULL){
      fprintf(stdout, "\nAttention: Dictionary reference is already empty\n");
      return;
   }
   for(int x = beginForward(D); currentVal(D) != VAL_UNDEF; x = next(D)){
      fprintf(stdout, KEY_FORMAT" "VAL_FORMAT"\n", currentKey(D), x);
   }
}