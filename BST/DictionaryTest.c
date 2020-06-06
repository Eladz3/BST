/****************
   Elad Zohar
   ezohar
   pa5
****************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Dictionary.h"

int main(int argc, char* argv[]){

   int i, n=26;
   Dictionary A = newDictionary(0);
   Dictionary B = newDictionary(1);
   char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
   VAL_TYPE x;
   VAL_TYPE y;

   // add pairs to A --------------------------------------
   for(i=0; i<n; i++){
      insert(A, word[i], i);
   }

   // add pairs to B
   for(i=n-1; i>=0; i--){
      insert(B, word[i], i);
   }

   // forward iteration over A ----------------------------
   printf("----Forward A----\n   (size = %d)\n", size(A));
   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   // reverse iteration over B 
   printf("----Reverse B----\n   (size = %d)\n", size(B));
   for(y=beginReverse(B); currentVal(B)!=VAL_UNDEF; y=prev(B)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), y);
   }
   printf("\n\n");


   // print Dictionary A ----------------------------------
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printDictionary(stdout, A);
   printf("\n");

   // print Dictionary B
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printDictionary(stdout, B);
   printf("\n");


   // delete keys from A ----------------------------------
   for(i=0; i<n; i+=2){
      delete(A, word[i]);
   }

   // print Dictionary A after deletions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("----After deletions----\n      (size = %d)\n", size(A));
   printDictionary(stdout, A);
   printf("\n");


   // delete keys from B ----------------------------------
   for(i=1; i<n; i+=2){
      delete(B, word[i]);
   }

   // print Dictionary B after deletions
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printf("----After deletions----\n      (size = %d)\n", size(B));
   printDictionary(stdout, B);
   printf("\n");


   // insert duplicates into A ----------------------------
   for(i=1; i<n; i+=2){
      insert(A, word[i], i);
   }

   // print Dictionary A after insertions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("----After insertions----\n      (size = %d)\n", size(A));
   printDictionary(stdout, A);
   printf("\n");

   // uncomment line below to get error message
   // insert(B, word[10], 10);
   // Dictionary Error: calling insert() on existing key: e because Dictionary reference is UNIQUE

   // clear Dictionary B --------------------------------
   makeEmpty(B);
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printf("----After makeEmpty----\n      (size = %d)\n", size(B));
   printDictionary(stdout, B);
   printf("\n");

   // free heap memory ------------------------------------
   freeDictionary(&A);
   freeDictionary(&B);
   return(0);
}

/*
Expected output:
----Forward A----
   (size = 26)
key: a value: 9
key: b value: 12
key: c value: 5
key: d value: 7
key: e value: 10
key: f value: 15
key: g value: 23
key: h value: 13
key: i value: 4
key: j value: 24
key: k value: 3
key: l value: 6
key: m value: 17
key: n value: 0
key: o value: 20
key: p value: 22
key: q value: 25
key: r value: 19
key: s value: 16
key: t value: 8
key: u value: 21
key: v value: 14
key: w value: 2
key: x value: 18
key: y value: 11
key: z value: 1


----Reverse B----
   (size = 26)
key: z value: 1
key: y value: 11
key: x value: 18
key: w value: 2
key: v value: 14
key: u value: 21
key: t value: 8
key: s value: 16
key: r value: 19
key: q value: 25
key: p value: 22
key: o value: 20
key: n value: 0
key: m value: 17
key: l value: 6
key: k value: 3
key: j value: 24
key: i value: 4
key: h value: 13
key: g value: 23
key: f value: 15
key: e value: 10
key: d value: 7
key: c value: 5
key: b value: 12
key: a value: 9


Dictionary A (non-unique keys):
a 9
b 12
c 5
d 7
e 10
f 15
g 23
h 13
i 4
j 24
k 3
l 6
m 17
n 0
o 20
p 22
q 25
r 19
s 16
t 8
u 21
v 14
w 2
x 18
y 11
z 1

Dictionary B (unique keys):
a 9
b 12
c 5
d 7
e 10
f 15
g 23
h 13
i 4
j 24
k 3
l 6
m 17
n 0
o 20
p 22
q 25
r 19
s 16
t 8
u 21
v 14
w 2
x 18
y 11
z 1

Dictionary A (non-unique keys):
----After deletions----
      (size = 13)
a 9
c 5
d 7
f 15
g 23
h 13
k 3
m 17
q 25
r 19
u 21
y 11
z 1

Dictionary B (unique keys):
----After deletions----
      (size = 13)
b 12
e 10
i 4
j 24
l 6
n 0
o 20
p 22
s 16
t 8
v 14
w 2
x 18

Dictionary A (non-unique keys):
----After insertions----
      (size = 26)
a 9
a 9
c 5
c 5
d 7
d 7
f 15
f 15
g 23
g 23
h 13
h 13
k 3
k 3
m 17
m 17
q 25
q 25
r 19
r 19
u 21
u 21
y 11
y 11
z 1
z 1

Dictionary B (unique keys):
----After makeEmpty----
      (size = 0)

Attention: Dictionary reference is already empty

*/
