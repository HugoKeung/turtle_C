#include "auto.h"

void wprog(FILE* fp, char* var){

/*every code starts with {*/
   fprintf(fp, "%s ", "{");

   winstructlist(fp, var);

   return;

}

/*if comes back from loop, then weight of } is higher*/
void winstructlist(FILE* fp,char* var){
   static int i = 1;
   int random;

   random = randNum(i);
   i++;

/* random range increases as it goes, so more and more likely for '}' afterwards*/
   
/*MINIMUM is the minimum number of instructions wanted before possible '}'*/
   if (random < MINIMUM){
      winstruction(fp, var);
      winstructlist(fp, var);
   }
   else{
      fprintf(fp, "%s ", "}");
   }


}
void winstruction(FILE* fp, char* var){

   int random = randNum(100);
/*different likelihood for each one (eqifilant to 100%)*/
   if (random < 45){
      wdirection(fp, var, "FD", LINELIMIT);
   }
   else if (random < 65){
      wdirection(fp, var, "RT", ANGLE);
   }
   else if (random < 85){
      wdirection(fp, var, "LT", ANGLE);
   }

   else if (random < 95){
      wdoFunc(fp, var);
   }
   else{
      wsetFunc(fp, var);
   }

}

void wdirection(FILE* fp, char* var, char* direction, int limit){

      fprintf(fp, "%s ", direction);
      randVarNum(fp, var, limit);
   
}

void wdoFunc(FILE* fp, char* var){

/*(DOLIMIT)+2 so minimum is 2, so no meaningless loop*/
   fprintf(fp, "%s %c %s %c %s %d %s ", "DO", randVar(var), "FROM", '1', "TO", randNum(DOLIMIT)+2, "{");
   winstructlist(fp, var);
}

void wsetFunc(FILE* fp, char* var){
   fprintf(fp, "%s %c %s ", "SET", randVar(var), ":=");
   wpolish(fp);
}

/*polish is not truely word by word' random, as as that will very likely output a non-valid expression*/
void wpolish(FILE* fp){
   int i;
   int n = randNum(NUMPOLISH)+1;

   for (i = 0; i < n; i++){
      fprintf(fp, "%d ", randNum(MAXPOLISH));
   }

   for (i = 0; i < n-1; i++){
      fprintf(fp, "%c ", randOp());
   }

   fprintf(fp, "%s ", ";");

/*

   int random = randNum(3);
   switch(random){
      case 0:
         fprintf(fp, "%c ", randOp());
         wpolish(fp);
         return;
      case 1:
         fprintf(fp, "%d ", randVarNum(fp, var, MAXPOLISH));
         wpolish(fp);
         return;
      case 2:
         fprintf(fp, "%s ", ";");
         return;
   } 
*/
      

}

char randOp(void){
   int random = randNum(4);
   switch(random){
      case 0:
         return '+';
      case 1:
         return '-';
      case 2:
         return '*';
      case 3:
         return '/';
      default:
         fprintf(stderr, "randOP unexpected error");
         exit (1);
   }
}

int randNum(int n){
   return (int)rand()%n;
}

char randVar(char* var){
   int random = randNum(ALPHABET);
   int i = 0;
/*find free space, store it*/
   while (var[i] != 0){
      i++;
   }
   var[i] = random+'A';
   
   return random+'A';
}
/*get the last var initialised*/
int varCnt(char* var){
   int i = 0;

   while (var[i] != 0){
      i++;
   }
   
   return i;
}
void randVarNum(FILE* fp, char* var, int n){

   int random = randNum(2);
/*first check if there are any variable initialised*/
   if (varCnt(var) == 0 || random == 0){
      fprintf(fp, "%d ", randNum(n));
   }
   
   else {
      fprintf(fp, "%c ", var[randNum(varCnt(var))]);
   }
      
}

