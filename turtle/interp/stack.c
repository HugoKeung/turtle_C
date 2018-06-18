#include"stack.h"

void InitialiseStack(Stack* s){
   s->top = 0;
}

void Push(Stack *s, double n){
/*make sure stack doesn't overflow*/
   if (s->top >= STACKSIZE){
      SERROR("Overflow, too many numbers entered\n");
   }
   s->stk[s->top].i = n;
   s->top = s->top +1;
}

double Pop(Stack* s){
/*can't pop empty stack (underflow)*/
   if (s->top <= 0){
      SERROR("Underflow, too little numbers / too many operators\n");
   }
   s->top = s->top -1;
   return s->stk[s->top].i;
}
int Empty(Stack* s){
   if (s->top == 0){
      return 1;
   }
   else return 0;

}

