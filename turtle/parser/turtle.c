 #include "turtle.h"

#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error. %sError Location: Word number: %d Word: %s\n", PHRASE, p->cw+1, p->wds[p->cw]); exit(2);}

void readFile(Prog* p, FILE* fp){
    
   int i = 0;
   if (fp==NULL){
      printf("No such file\n");
      exit(1);
   }
/*all words got put into p->wds*/

   while(fscanf(fp, "%s", p->wds[i++]) != EOF && i < MAXIMUMTOKENS);      
   
}

void dynamicRead(Prog* p, FILE* fp){
   int size = MAXIMUMTOKENS, cnt = 0;   

   char* token = calloc(MAXTOKENSIZE, sizeof(char));
   if (fp==NULL){
      printf("No such file\n");
      exit(1);
   }
   p->wds = calloc(size, sizeof(char*));
   while (fscanf(fp, "%s", token) != EOF){
      if (cnt >= size){
         size = size*2;
         expand(p, size);
      }
         
      p->wds[cnt] = calloc(MAXTOKENSIZE, sizeof(char));
      strcpy(p->wds[cnt], token);
      cnt++;
   }

   p->wds[cnt] = calloc(1, sizeof(char));
   p->wds[cnt][0] = '\0';
   free(token);

}

void expand(Prog* p, int size){
   char**tmpwds;
   tmpwds = calloc(size, sizeof(char*));
   memcpy(tmpwds, p->wds, sizeof(char*)*size/2);
   free(p->wds);
   p->wds = tmpwds;

}

void freewds(Prog* p){
   int i=0;
   while( p->wds[i][0] != '\0'){
      free(p->wds[i++]);
   }
   free(p->wds[i]);
   free(p->wds);
}

/*set default value to \0 or 0 for the variables*/
void initialiseProg(Prog* p){
   int i;
   for (i=0; i < MAXIMUMTOKENS; i++){
      p->wds[i][0] = '\0';
   }

   p->cw = 0;
}

/*this function is <MAIN> check
"{"<INSTRUCTLIST>
*/
void prog(Prog* p){

   p->cw = 0;
   if(strcmp(p->wds[0], "{") != 0){
      ERROR("Program didn't start with '{'\n");
   }
   
   p->cw = p->cw+1;

   instructlist(p);

   if(p->wds[p->cw][0] != '\0'){
      ERROR("Excess characters at the end\n");
   }

   
   return;
}

/*<INSTRUCTLIST> grammar
"}"| <INSTRUCTION><INSTRUCTLIST>
*/
void instructlist(Prog* p){
   if (strcmp(p->wds[p->cw], "}")==0){
      p->cw = p->cw+1;
      return;
   }

   instruction(p);

   instructlist(p);
   return;

}

/*<OP> grammar
"+"|"-"|"*"|"/"
*/
int isOp(char* str){

   if (strcmp(str, "+")==0 || strcmp(str, "-")==0 || strcmp(str, "*")==0 || strcmp(str, "/")==0 ){
      return true;
   }
   else return false;
}

/*<VAR> grammar
[A-Z]
*/
int isVar(char* str){
   /*char c = str[0];*/
/*cannot be <VAR> if longer than 1 character,
therefore only str[0] is relevant*/
   if (strlen(str) > 1){
      return false;
   }
      
/*check if upper case AND alphabet*/
   if (isupper(str[0])){
      return true;
   }
   else return false;

}

/*check if is number*/
int isNum(char* str){


   char* rubbish;
   strtod(str, &rubbish);

   if (rubbish[0] != '\0'){
      return false;
   }

   return true;

}

/*<VARNUM> grammar
number|<VAR>
*/
int isVarNum(char* str){
   if(isNum(str)== false && isVar(str)== false){
      return false;
   }
   return true;
}

/*return the direction (or 'invalid' if is not a direction)*/
int isDirection(char* str){
   
   if (strcmp(str, "FD")==0 || strcmp(str, "RT")==0 || strcmp(str, "LT")==0){
      return true;
   }

   else return false;

}

/*<INSTRUCTION> grammar
<FD>|<LT>|<RT>|<DO>|<SET>
*/
void instruction(Prog* p){

/*<FD> <LT> <RT> grammar
"FD"<VARNUM>
*/
   if (isDirection(p->wds[p->cw]) == true){   
      p->cw = p->cw+1;
      if (isVarNum(p->wds[p->cw]) == false){
         ERROR("Expected variable/number\n");
      }

      p->cw = p->cw+1;
      return;
   }
   else if (strcmp(p->wds[p->cw], "DO") ==0){
      p->cw = p->cw+1;
      doFunc(p);
      
      return;
   }
   else if (strcmp(p->wds[p->cw], "SET") ==0){
      p->cw = p->cw+1;
      setFunc(p);
      return;
   }

   ERROR("Expected instructions\n");
}
/*<DO> grammar
"DO"<VAR>"FROM"<VARNUM>"TO"<VARNUM>"{"<INSTRUCTLIST>
already check"DO" is previous function
*/

void doFunc(Prog* p){

   if (isVar(p->wds[p->cw]) == 0){
      ERROR("Expected variable\n");
   }
   p->cw = p->cw+1;
   
   if (strcmp(p->wds[p->cw], "FROM") != 0){
      ERROR("Expected FROM\n");
   }   
   p->cw = p->cw+1;
   if(isVarNum(p->wds[p->cw])== 0){
      ERROR("Expected variable/number\n");
   }
   p->cw = p->cw+1;

   if (strcmp(p->wds[p->cw], "TO") != 0){
      ERROR("Expected TO\n");
   }
   p->cw = p->cw+1;

   if(isVarNum(p->wds[p->cw])==0){
      ERROR("Expected variable/number\n");
   }
   p->cw = p->cw+1;

   if (strcmp(p->wds[p->cw], "{") != 0){
      ERROR("Expected {\n");
   }
   p->cw = p->cw+1;
   instructlist(p);
   
}
/*<SET> grammar
"SET<VAR>":="<POLISH>
already checked "SET" in previous function
*/
void setFunc(Prog* p){

   if (isVar(p->wds[p->cw])== false){
      ERROR("Expected variable\n");
   }

   p->cw = p->cw+1;
   if (strcmp(p->wds[p->cw], ":=") != 0){
      ERROR("Expected :=\n");
   }
   p->cw = p->cw+1;
   polish(p);

   return;
}
/*<POLISH> grammar
";"|<VARNUM><POLISH>|<OP><POLISH>
*/
void polish(Prog* p){
   if (strcmp(p->wds[p->cw], ";")== 0){
      p->cw = p->cw+1;
      return;

   }
   if (isVarNum(p->wds[p->cw]) == true){
      p->cw = p->cw+1;
      polish(p);
      return;
   }   
   if (isOp(p->wds[p->cw]) == true){
      p->cw = p->cw+1;
      polish(p);
      return;
   }
   ERROR("incorrect polish notation\n");
   
}

