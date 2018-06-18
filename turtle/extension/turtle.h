#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"stack.h"
#include"neillsdl2.h"

#define MAXIMUMTOKENS 20
#define MAXTOKENSIZE 7
#define AtoZ 26
#define PI 3.14159265358979323846

enum direction{invalid, FD, LT, RT};
enum boolean{false, true};

struct turtle{
   double angle;
   int oldX;
   int oldY;
   int loop;
   
}; typedef struct turtle Turtle;

struct prog{

 /*  char wds[MAXIMUMTOKENS][MAXTOKENSIZE];*/
   char** wds;
   int cw;
   double var[AtoZ];
   Turtle t;
   SDL_Simplewin sw;
}; typedef struct prog Prog;



void prog(Prog* p, SDL_Simplewin* sw);
int isOp(char* str);
int isVar(char* str);
int isNum(char* str);
int isVarNum(char* str);
int isDirection(Prog* p);
int lengthCheck(char* str);
void instruction(Prog* p, SDL_Simplewin* sw);
void instructlist(Prog* p, SDL_Simplewin* sw);
void polish(Prog* p, Stack* s);
void doFunc(Prog* p, SDL_Simplewin* sw);
void setFunc(Prog* p);
void readFile(Prog* p, FILE* fp);
void initialiseProg(Prog* p);

void calculate(Stack* s, char op);

void startLoop(Prog* p, char letter, int from, int to, SDL_Simplewin* sw);

void setVar(Prog* p, char letter, double n);

double getVar(Prog* p, char letter);

double getNum(Prog* p, char* str);

void draw(SDL_Simplewin* sw, Prog* p, int direction, double n);

void dynamicRead(Prog* p, FILE* fp);
void expand(Prog* p, int size);
void freewds(Prog* p);
