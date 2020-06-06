/****************
   Elad Zohar
   ezohar
   pa5
****************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#define MAX_LEN 160

int main(int argc, char *argv[]){
    
   FILE *input, *output;
   int cnt = 0;
   char line[MAX_LEN];                                 //feeds in one line of input
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
   
   //create static array that stores all rows of file
   static char inputFile[500000][MAX_LEN];                           
   
   rewind(input);
   // populate Dictionary D
   Dictionary D = newDictionary(0);
   cnt = 0;                                   
   while(fgets(line, MAX_LEN, input) != NULL){
      strcpy(inputFile[cnt], line);
      insert(D, inputFile[cnt], cnt);
      cnt++;
   }

   // print key's in order
   for(beginForward(D); currentVal(D) != VAL_UNDEF; next(D)){
      fprintf(output, KEY_FORMAT, currentKey(D));
   }
   
   freeDictionary(&D);
   fclose(input);
   fclose(output);
   return 0;
}
