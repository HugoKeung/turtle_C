#include<stdio.h>
#include<assert.h>

#define STACKSIZE 200

struct stackelem{
   double i;
};
typedef struct stackelem Elem;

struct thestack{
   Elem stk[STACKSIZE];
   int top;
};
typedef struct thestack Stack;

void InitialiseStack(Stack* s);
void Push(Stack* s, double n);
double Pop(Stack* s);
int Empty(Stack* s);
