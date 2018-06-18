#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define MAXIMUMTOKENS 20
#define MAXTOKENSIZE 7

enum boolean{false, true};

struct prog{
   /*char wds[MAXIMUMTOKENS][MAXTOKENSIZE];*/
   char** wds;
   int cw;
}; typedef struct prog Prog;



void prog(Prog* p);
int isOp(char* str);
int isVar(char* str);
int isNum(char* str);
int isVarNum(char* str);
int isDirection(char* str);
int lengthCheck(char* str);
void instruction(Prog* p);
void instructlist(Prog* p);
void polish(Prog* p);
void doFunc(Prog* p);
void setFunc(Prog* p);
void readFile(Prog* p, FILE* fp);
void initialiseProg(Prog* p);


void dynamicRead(Prog*p, FILE* fp);
void freewds(Prog* p);
void expand(Prog* p, int size);
