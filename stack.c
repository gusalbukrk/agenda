#include <stdio.h>
#include <stdlib.h>

#include "ABB.h"
#include "stack.h"

void printStack(stack *s) {
  for (int i = 0; i < s->quant; i++) {
    node n = s->values[i];
    printf("%s: %s\n", n.contato.nome, n.contato.telefone);
  }
}

void push(stack **s, node *n) {
  int newQuant = (*s) == NULL ? 1 : (*s)->quant + 1;
  *s = realloc( *s, sizeof(stack) + (sizeof(node) * newQuant) );

  for (int i = newQuant - 1; i > 0; i--) {
    (*s)->values[i] = (*s)->values[i - 1];
  }

  node *t = malloc(sizeof(node));
  t->contato = n->contato;
  t->esq = n->esq;
  t->dir = n->dir;
  (*s)->values[0] = *t;

  (*s)->quant = newQuant;
}

node *pop(stack **s) {
  node *t = malloc(sizeof(node)); // save popped element
  t->contato = (*s)->values[0].contato;
  t->esq = (*s)->values[0].esq;
  t->dir = (*s)->values[0].dir;

  // dislocate each piece one position to the left
  for (int i = 0; i < (*s)->quant - 1; i++) {
    (*s)->values[i] = (*s)->values[i + 1];
  }
  
  *s = realloc( *s, sizeof(stack) + (sizeof(node) * ((*s)->quant - 1)) );

  (*s)->quant--;

  return t;
}
