/*generate random file and interpret it if no file argument is entered*/

#include"auto.h"
#include"turtle.h"
void openFile(int argc, FILE** fp, char* argv[]);

int main(int argc, char* argv[]){

   FILE* fp = NULL;

   Prog p;
   SDL_Simplewin sw;
   initialiseProg(&p);
   openFile(argc, &fp, argv);
   Neill_SDL_Init(&sw);
   Neill_SDL_SetDrawColour(&sw, 255, 255, 255);
   dynamicRead(&p, fp);

   prog(&p, &sw);
      
   do{
      Neill_SDL_Events(&sw);
   }while(!sw.finished);

   fclose(fp);
   freewds(&p);

   return 0;
}

void openFile(int argc, FILE** fp, char* argv[]){
   
   if (argc == 1){
      char var[ALPHABET] = {0};
      srand(time(NULL));
      *fp = fopen("aAaAaAaA.txt", "w");
      wprog(*fp, var);
      fclose(*fp);
      *fp = fopen("aAaAaAaA.txt", "r");
   }

   else if (argc == 2){
      *fp = fopen(argv[1], "r");
   }
   else {
      fprintf(stderr, "INCORRECT USAGE OF PROGRAMME\n %s FILENAME", argv[0]);
      exit(1);
   }
}
