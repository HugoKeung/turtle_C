#include "turtle.h"

int main(int argc, char* argv[]){

   FILE* fp;
   Prog p;

   SDL_Simplewin sw;
   initialiseProg(&p);
   if (argc == 2){
      fp = fopen(argv[1], "r");
   }
   else {
      fprintf(stderr, "INCORRECT USAGE OF PROGRAMME\n %s FILENAME", argv[0]);
      exit(1);
   }

   Neill_SDL_Init(&sw);
   Neill_SDL_SetDrawColour(&sw, 255, 255, 255);
   /*readFile(&p, fp);   */
   dynamicRead(&p, fp);

   prog(&p, &sw);
      
   do{
      Neill_SDL_Events(&sw);
   }while(!sw.finished);
   fclose(fp); 
   freewds(&p);
   return 0;

   
}

