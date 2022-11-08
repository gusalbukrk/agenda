#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ABBI.h"
#include "stack.h"

void preorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  node *atual = raiz, *prevNode = NULL;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      callback(atual);
      push(&s, atual);
      atual = atual->esq;
    } else {
      prevNode = pop(&s);
      atual = prevNode->dir;
    }
  }
}

void inorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  node *atual = raiz;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      push(&s, atual);
      atual = atual->esq;
    } else {
      atual = pop(&s);
      callback(atual);
      atual = atual->dir;
    }
  }
}

void postorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  stack *dir = NULL; initStack(&dir);
  node *atual = raiz;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      if (atual->dir != NULL) push(&dir, atual->dir);
      push(&s, atual);
      atual = atual->esq;
    } else {
      atual = &(s->values[0]);
      if (
        dir->quant != 0 &&
        ( atual->dir != NULL && (strcmp(atual->dir->contato.nome, dir->values[0].contato.nome) == 0) )
      ) {
        atual = pop(&dir);
      } else {
        callback(atual);
        pop(&s);
        atual = NULL;
      }
    }
  }
}

void imprimirNode(node *n) {
  if (n == NULL) {
    printf("(nil)\n");
    return;
  }

  printf("(%p) = { %s, %s }, %p, %p\n", n, n->contato.nome, n->contato.telefone, n->esq, n->dir);
}

// imprime nodes em-ordem
void imprimirArvoreI(node *raiz) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  node *atual = raiz;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      push(&s, atual);
      atual = atual->esq;
    } else {
      atual = pop(&s);
      imprimirNode(atual);
      atual = atual->dir;
    }
  }
}

void criarNode(node **ref, contato c) {
  *ref = (node *) malloc(sizeof(node));

  (*ref)->contato = c;
  (*ref)->esq = NULL;
  (*ref)->dir = NULL;
}

void inserirNodeI(node **raiz, contato c) {
  if (c.nome[0] >= 97 && c.nome[0] <= 122) c.nome[0] -= 32;
  if (procurarNodeI(*raiz, c.nome)) return;

  node **n = raiz;

  while (*n != NULL) {
    n = strcmp(c.nome, (*n)->contato.nome) < 0 ? &(*n)->esq : &(*n)->dir;
  }

  criarNode(n, c);
}

void removerNodeI(node **raiz, char *nome) {
  if (raiz == NULL) return;

  node **n = raiz;

  int cmp;

  while ( (cmp = strcmp(nome, (*n)->contato.nome)) != 0 ) {
    n = cmp < 0 ? &((*n)->esq) : &((*n)->dir);
    
    if (*n == NULL) return;
  }

  // caso node a ser removido é um node folha, simplesmente remova-o
  if ( (*n)->esq == NULL && (*n)->dir == NULL ) {
    free(*n);
    *n = NULL;

  // caso node a ser removido possua 2 filhos
  // substitua-o por o seu node predecessor ou sucessor em ordem, ou seja:
  // - o node mais à direita da sub-árvore do filho da esquerda
  // - o node mais à esquerda da sub-árvore do filho da direita
  } else if ( (*n)->esq != NULL && (*n)->dir != NULL ) {
    node **d = &(*n)->esq;
    while ( (*d)->dir != NULL ) d = &((*d)->dir);

    node *tmp = *n; // salva raiz em uma variável temporária
    *n = *d; // substitui raiz por o descendente mais à direita do seu filho esquerdo

    if ( *n != tmp->esq ) {
      (*n)->esq = tmp->esq;
    }

    if ( *n != tmp->dir ) {
      (*n)->dir = tmp->dir;
    }

    *d = NULL; // caso contrário a nova raiz ainda será filho do seu antigo pai

    free(tmp);
    tmp = NULL;

  // caso node a ser removido possua apenas um filho — esq ou dir
  // substitua o node a ser removido por o seu único filho
  } else {
    node **child = (*n)->esq != NULL ? &(*n)->esq : &(*n)->dir;

    free(*n);
    *n = *child;
  }
}

// percorre toda a árvore p/ calcular o número total de nodes
// a ordem em que a árvore será percorrida é irrelevante, usaremos pré-ordem
// pois as alternativas (em-ordem e pós-ordem) já foram utilizadas em outras funções
int contarNodesI(node *raiz) {
  if (raiz == NULL) return 0;

  stack *s = NULL; initStack(&s);
  node *atual = raiz, *prevNode = NULL;

  int contador = 0;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      contador += 1;
      push(&s, atual);
      atual = atual->esq;
    } else {
      prevNode = pop(&s);
      atual = prevNode->dir;
    }
  }

  return contador;
}

node *procurarNodeI(node *raiz, char *nome) {
  if (raiz == NULL) return NULL;

  node *n = raiz;

  int cmp;

  while ( (cmp = strcmp(nome, n->contato.nome)) != 0 ) {
    n = cmp < 0 ? n->esq : n->dir;
    
    if (n == NULL) return NULL;
  }

  return n;
}

// percorre a árvore em pós-ordem p/ deletar todos os nodes
void destruirArvoreI(node **raiz) {
  if (*raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  stack *dir = NULL; initStack(&dir);
  node *atual = *raiz;

  while ( s->quant != 0 || atual != NULL ) {
    if (atual != NULL) {
      if (atual->dir != NULL) push(&dir, atual->dir);
      push(&s, atual);
      atual = atual->esq;
    } else {
      atual = &(s->values[0]);
      if (
        dir->quant != 0 &&
        ( atual->dir != NULL && (strcmp(atual->dir->contato.nome, dir->values[0].contato.nome) == 0) )
      ) {
        atual = pop(&dir);
      } else {
        free(*raiz); *raiz = NULL;
        pop(&s);
        atual = NULL;
      }
    }
  }
}
