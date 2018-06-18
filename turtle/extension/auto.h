#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DOLIMIT 10
#define LINELIMIT 100
#define ANGLE 360
#define ALPHABET 26
#define MINIMUM 5
#define NUMPOLISH 5
#define MAXPOLISH 10

void wprog(FILE* fp, char* var);
void winstructlist(FILE* fp, char* var);
int randNum(int n);
void winstruction(FILE* fp, char* var);
void wpolish(FILE* fp);
void wdoFunc(FILE* fp, char* var);
void wsetFunc(FILE* fp, char* var);
char randOp(void);
char randVar(char* var);
void randVarNum(FILE* fp, char* var, int n);
void wdirection(FILE* fp, char* var, char* direction, int limit);
