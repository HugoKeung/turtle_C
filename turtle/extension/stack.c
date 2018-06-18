#include"stack.h"
void InitialiseStack(Stack* s){
   s->top = 0;
}

void Push(Stack *s, double n){
/*make sure stack doesn't overflow*/
   assert(s->top < STACKSIZE);
   s->stk[s->top].i = n;
   s->top = s->top +1;
}

double Pop(Stack* s){
/*can't pop empty stack (underflow)*/
   assert(s->top > 0);
   s->top = s->top -1;
   return s->stk[s->top].i;
}
int Empty(Stack* s){
   if (s->top == 0){
      return 1;
   }
   else return 0;

}

