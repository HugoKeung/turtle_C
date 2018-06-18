#include "turtle.h"

int main(int argc, char* argv[]){

   FILE* fp;
   Prog p;

   if (argc == 2){
      fp = fopen(argv[1], "r");
   }
   else {
      fprintf(stderr, "INCORRECT USAGE OF PROGRAMME\n %s FILENAME", argv[0]);
      exit(1);
   }

   /*initialiseProg(&p);
   readFile(&p, fp);   */
/*dynamicRead used calloc and therefore initialise itself, also doesn't mess with cw*/

   dynamicRead(&p, fp);

   prog(&p);
   freewds(&p);
   return 0;

}


