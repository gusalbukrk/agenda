#include "ABB.h"

typedef struct Stack {
  int quant;
  node values[];
} stack;

void printStack(stack *s);
void push(stack **s, node *n);
node *pop(stack **s);
