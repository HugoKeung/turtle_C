#include "turtle.h"

#define ERROR(PHRASE) {fprintf(stderr, "Fatal Error. %sError Location: Word number: %d Word: %s\n", PHRASE, p->cw+1, p->wds[p->cw]); exit(2);}


void readFile(Prog* p, FILE* fp){
    
   int i = 0;
   if (fp==NULL){
      fprintf(stderr, "No such file\n");
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

/*   for (i=0; i < MAXIMUMTOKENS; i++){
      p->wds[i][0] = '\0';
   }
*/

   for (i=0; i < AtoZ; i++){
      p->var[i] = 0;
   }
   p->cw = 0;
   p->t.angle = 0;
   p->t.oldX = WWIDTH/2;
   p->t.oldY = WHEIGHT/2;
   p->t.loop = true;

}

/*this function is essentially <MAIN> check
"{"<INSTRUCTLIST>
*/
void prog(Prog* p, SDL_Simplewin* sw){

   p->cw = 0;
   if(strcmp(p->wds[0], "{") != 0){
      ERROR("Program didn't start with '{'\n");
   }
   
   p->cw = p->cw+1;

   instructlist(p, sw);

   if(p->wds[p->cw][0] != '\0'){
      ERROR("Excess characters at the end\n");
   }
   
   return;
}

/*<INSTRUCTLIST> grammar
"}"| <INSTRUCTION><INSTRUCTLIST>
*/
void instructlist(Prog* p, SDL_Simplewin* sw){
   if (strcmp(p->wds[p->cw], "}")==0){
      p->cw = p->cw+1;
      return;
   }

   instruction(p, sw);

   instructlist(p, sw);
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
   char c = str[0];
/*cannot be <VAR> if longer than 1 character,
therefore only str[0] is relevant*/
   if (strlen(str) > 1){
      return false;
   }
   
/*check if upper case AND alphabet*/
   if (isupper(c)){
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
int isDirection(Prog* p){
   
   int direction;

   if (strcmp(p->wds[p->cw], "FD") == 0){
      direction = FD;
   }
   
   else if (strcmp(p->wds[p->cw], "LT") == 0){
      direction = LT;
   }   
   
   else if (strcmp(p->wds[p->cw], "RT") == 0){
      direction = RT;
   }

   else return invalid;
/*only cw+1 if it is a direction, else have to let other function read it*/
   p->cw = p->cw+1;

   return direction;

}

/*<INSTRUCTION> grammar
<FD>|<LT>|<RT>|<DO>|<SET>
*/
void instruction(Prog* p, SDL_Simplewin* sw){
/*check direction, and store it*/
   int direction = isDirection(p);

/*<FD> <LT> <RT> grammar
"FD"<VARNUM>
*/
   if (direction != invalid){      
   
      if (isVarNum(p->wds[p->cw]) == 0){
         ERROR("Expected variable/number\n");
      }
      if (p->t.loop == true){
         draw(sw, p, direction, getNum(p, p->wds[p->cw]));
      }
      p->cw = p->cw+1;
      return;
   }
   if (strcmp(p->wds[p->cw], "DO") ==0){
      p->cw = p->cw+1;
      doFunc(p, sw);
      return;
   }
   if (strcmp(p->wds[p->cw], "SET") ==0){
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
/*since we can't do DO loop of double to double (it doesn't make sense), therefore integers are used, and the decimal points are ignored)*/
void doFunc(Prog* p, SDL_Simplewin* sw){
   int from, to;
   char letter;
   if (isVar(p->wds[p->cw]) == 0){
      ERROR("Expected variable\n");
   }
   letter = p->wds[p->cw][0];
   p->cw = p->cw+1;
   
   if (strcmp(p->wds[p->cw], "FROM") != 0){
      ERROR("Expected FROM\n");
   }   
   p->cw = p->cw+1;

   if(isVarNum(p->wds[p->cw])== 0){
      ERROR("Expected variable/number\n");
   }
   
   from = getNum(p, p->wds[p->cw]);
   setVar(p, letter, from);
   p->cw = p->cw+1;

   if (strcmp(p->wds[p->cw], "TO") != 0){
      ERROR("Expected TO\n");
   }
   p->cw = p->cw+1;

   if(isVarNum(p->wds[p->cw])==0){
      ERROR("Expected variable/number\n");
   }
   to = getNum(p, p->wds[p->cw]);
   p->cw = p->cw+1;

   if (strcmp(p->wds[p->cw], "{") != 0){
      ERROR("Expected {\n");
   }
   p->cw = p->cw+1;
   startLoop(p, letter, from, to, sw);
   
}


/*<SET> grammar
"SET<VAR>":="<POLISH>
already checked "SET" in previous function
*/
void setFunc(Prog* p){
   char var;
/*stack needed to calculate polish*/
   Stack s;
   InitialiseStack(&s);
   if (isVar(p->wds[p->cw])== false){
      ERROR("Expected variable\n");
   }
   var = p->wds[p->cw][0];
   p->cw = p->cw+1;
   if (strcmp(p->wds[p->cw], ":=") != 0){
      ERROR("Expected :=\n");
   }
   p->cw = p->cw+1;
   polish(p, &s);
   if (p->t.loop == true){
      setVar(p, var, Pop(&s));
   }
   return;
}
/*<POLISH> grammar
";"|<VARNUM><POLISH>|<OP><POLISH>
*/
void polish(Prog* p, Stack* s){
   if (strcmp(p->wds[p->cw], ";")== 0){
      
      p->cw = p->cw+1;
      return;

   }
   if (isVarNum(p->wds[p->cw]) == true){
      Push(s, getNum(p, p->wds[p->cw]));

      p->cw = p->cw+1;
      polish(p, s);
      return;
   }   
   if (isOp(p->wds[p->cw]) == true){
      calculate(s, p->wds[p->cw][0]);
      p->cw = p->cw+1;
      polish(p, s);
      return;
   }
   ERROR("incorrect polish notation\n");
   
}

/*calculate what is inside the stack using polish notation*/
void calculate(Stack* s, char op){
   double a, b, result;
   a = Pop(s);
   b = Pop(s);

   switch(op){
      case'+':
         result = b+a;
         break;
      case '-':
         result = b-a;
         break;
      case'*':
         result = b*a;
         break;
      case'/':
         if (b < 0.000001 && b > -0.000001){
            fprintf(stderr, "cannot divided by 0\n");
            exit(1);
         }
         result = b/a;
         break;
      default:
         fprintf(stderr, "unexpected error in calculate\n");
         exit(1);
   } 
   Push(s, result);

}
/*set variable to a number*/
void setVar(Prog* p, char letter, double n){
   p->var[letter-'A'] = n;
}
/*get the number stored in the variable*/
double getVar(Prog* p, char letter){
   return p->var[letter-'A'];
}
/*get the number of the string, depends if it is num or variable*/
double getNum(Prog* p, char* str){
   if (isNum(str) == true){
      return atof(str);
   }
   else {
      return getVar(p, str[0]);
   }
      
}


void draw(SDL_Simplewin* sw, Prog* p, int direction, double n){
   int newX, newY;
   double radian = PI/180;

   switch(direction){

      case FD:
/*+0.5 to round it up/down*/
         newX = (int)( n * sin(p->t.angle * radian) + p->t.oldX + 0.5);

         newY = (int) (p->t.oldY -  n * cos(p->t.angle * radian) + 0.5);

         if (!sw->finished){
            SDL_RenderDrawLine(sw->renderer, p->t.oldX, p->t.oldY, newX, newY);
            SDL_RenderPresent(sw->renderer);    
            SDL_UpdateWindowSurface(sw->win);  
            Neill_SDL_Events(sw);
         }
         p->t.oldX = newX;
         p->t.oldY = newY;
         return;

      case LT:
         p->t.angle -= n;
         return;

      case RT:
         p->t.angle += n;
         return;

   }

}

void startLoop(Prog* p, char letter, int from, int to, SDL_Simplewin* sw){
/*oldcw to mark the start of do loop*/
   int oldcw = p->cw;
/*don't draw if it is -ve for loop*/

   if ((to - from) < 0){
      p->t.loop = false;
   }
   do{
      p->cw = oldcw;
      setVar(p, letter, from);
      instructlist(p, sw);
      from++;

   }while(from <= to);
   /*reset loop after outside do loop scope*/
   p->t.loop = true;

}
