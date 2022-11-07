#include "ABB.h"

typedef struct Stack {
  int quant;
  node values[];
} stack;

void initStack(stack **s);
void printStack(stack *s);
void push(stack **s, node *n);
node *pop(stack **s);
