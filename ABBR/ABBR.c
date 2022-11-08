#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ABBR.h"

void imprimirNode(node *n) {
  if (n == NULL) {
    printf("(nil)\n");
    return;
  }

  printf("(%p) = { %s, %s }, %p, %p\n", n, n->contato.nome, n->contato.telefone, n->esq, n->dir);
}

// imprime nodes em-ordem
void imprimirArvore(node *raiz) {
  if (raiz == NULL) return;

  imprimirArvore(raiz->esq);
  imprimirNode(raiz);
  imprimirArvore(raiz->dir);
}

void criarNode(node **ref, contato c) {
  *ref = (node *) malloc(sizeof(node));

  (*ref)->contato = c;
  (*ref)->esq = NULL;
  (*ref)->dir = NULL;
}

// percorre a árvore p/ encontrar o node folha em que adicionar o novo contato
void inserirNode(node **raiz, contato c) {
  if (c.nome[0] >= 97 && c.nome[0] <= 122) c.nome[0] -= 32;
  if (procurarNode(*raiz, c.nome)) return;

  node **n = raiz;

  while (*n != NULL) {
    n = strcmp(c.nome, (*n)->contato.nome) < 0 ? &(*n)->esq : &(*n)->dir;
  }

  criarNode(n, c);
}

node **retornarDescendenteMaisADireita(node **raiz) {
  if ((*raiz)->dir == NULL) return raiz;

  return retornarDescendenteMaisADireita(&(*raiz)->dir);
}

// percorre a árvore p/ encontar o node com o exato nome e removê-lo
void removerNode(node **raiz, char *nome) {
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
    node **d = retornarDescendenteMaisADireita(&(*n)->esq);

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

// percorre toda a árvore em pré-ordem p/ calcular o número total de nodes
int contarNodes(node *raiz) {
  if (raiz == NULL) return 0;

  return 1 + contarNodes(raiz->esq) + contarNodes(raiz->dir);
}

// // percorre a árvore p/ encontrar o contato com o exato nome e retorná-lo
node *procurarNode(node *raiz, char *nome) {
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
void destruirArvore(node **raiz) {
  if (*raiz == NULL) return;

  destruirArvore(&(*raiz)->esq);
  destruirArvore(&(*raiz)->dir);
  free(*raiz);
  *raiz = NULL;
}
