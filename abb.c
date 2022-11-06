#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abb.h"

void imprimirNode(node *n) {
  if (n == NULL) {
    printf("(nil)\n");
    return;
  }

  printf("(%p) = { %s, %s }, %p, %p\n", n, n->contato.nome, n->contato.telefone, n->esq, n->dir);
}

// imprime nodes em ordem
void imprimirArvore(node *raiz) {
  if (raiz == NULL) return;

  imprimirArvore(raiz->esq);
  imprimirNode(raiz);
  // printf("%s: %s\n", raiz->contato.nome, raiz->contato.telefone);
  imprimirArvore(raiz->dir);
}

// recursivamente percorre a árvore p/ encontrar o contato desejado
node *procurarNode(node *raiz, char *nome) {
  if (raiz == NULL) return NULL;

  int cmp = strcmp(nome, raiz->contato.nome);

  if ( cmp == 0 ) return raiz;
  return procurarNode(cmp < 0 ? raiz->esq : raiz->dir, nome);
}

void criarNode(node **ref, contato c) {
  *ref = (node *) malloc(sizeof(node));

  (*ref)->contato = c;
  (*ref)->esq = NULL;
  (*ref)->dir = NULL;
}

void inserirNodeAux(node **raiz, contato c) {
  // n é o endereço do node da esquerda ou da direita
  // depende da direção em que o novo contato deve ser inserido
  node **n = strcmp(c.nome, (*raiz)->contato.nome) < 0 ? &((*raiz)->esq) : &((*raiz)->dir);

  // caso node n não esteja vazio
  // use recursão para executar essa função novamente dessa vez usando n como raiz
  if (*n != NULL) {
    inserirNodeAux(n, c);
    return;
  }

  // caso node n esteja vazio, insira o novo contato
  criarNode(n, c);
}

// recursivamente percorre a árvore p/ encontrar a folha em que adicionar o novo contato
void inserirNode(node **raiz, contato c) {
  // a primeira letra dos nomes dos contatos devem sempre estar em maiúscula
  if (c.nome[0] >= 97 && c.nome[0] <= 122) c.nome[0] -= 32;

  // os nodes de árvores binárias de busca devem ser únicos
  if (procurarNode(*raiz, c.nome)) return;

  // caso a árvore esteja vazia, adicione o primeiro elemento
  if ( *raiz == NULL ) { 
    criarNode(raiz, c);
    return;
  }

  // caso a árvore já possua nodes
  inserirNodeAux(raiz, c);
}

node **retornarDescendenteMaisADireita(node **raiz) {
  if ((*raiz)->dir == NULL) return raiz;

  return retornarDescendenteMaisADireita(&(*raiz)->dir);
}

// recursivamente percorre a árvore p/ encontar o node a ser removido
void removerNode(node **raiz, char *nome) {
  if (*raiz == NULL) return;

  int cmp = strcmp(nome, (*raiz)->contato.nome);

  if (cmp == 0) { // caso raiz é o contato a ser removido

    // caso node a ser removido é um node folha, simplesmente remova-o
    if ( (*raiz)->esq == NULL && (*raiz)->dir == NULL ) {
      free(*raiz);
      *raiz = NULL;

    // caso node a ser removido possua 2 filhos
    // substitua-o por o seu node predecessor ou sucessor em ordem, ou seja:
    // - o node mais à direita da sub-árvore do filho da esquerda
    // - o node mais à esquerda da sub-árvore do filho da direita
    } else if ( (*raiz)->esq != NULL && (*raiz)->dir != NULL ) {
      node **n = retornarDescendenteMaisADireita(&(*raiz)->esq);

      node *tmp = *raiz; // salva raiz em uma variável temporária
      *raiz = *n; // substitui raiz por o descendente mais à direita do seu filho esquerdo

      if ( *raiz != tmp->esq ) {
        (*raiz)->esq = tmp->esq;
      }

      if ( *raiz != tmp->dir ) {
        (*raiz)->dir = tmp->dir;
      }

      *n = NULL; // caso contrário a nova raiz ainda será filho do seu antigo pai

      free(tmp);
      tmp = NULL;

    // caso node a ser removido possua apenas um filho — esq ou dir
    // substitua o node a ser removido por o seu único filho
    } else {
      node **child = (*raiz)->esq != NULL ? &(*raiz)->esq : &(*raiz)->dir;

      free(*raiz);
      *raiz = *child;
    }

    return;
  }

  removerNode(cmp < 0 ? &(*raiz)->esq : &(*raiz)->dir, nome);
}

// recursivamente percorre a árvore e adiciona 1 ao total a cada node percorrido
int contarNodes(node *raiz) {
  if (raiz == NULL) return 0;

  return 1 + contarNodes(raiz->esq) + contarNodes(raiz->dir);
}

void destruirArvoreAux(node *raiz) {
  if (raiz == NULL) return;

  destruirArvoreAux(raiz->esq);
  destruirArvoreAux(raiz->dir);
  free(raiz);
}

// recursivamente percorre a árvore em pós-ordem p/ deletar todos os nodes
void destruirArvore(node **raiz) {
  destruirArvoreAux(*raiz);
  
  // atribua NULL para a raiz para que não haja nenhuma variável apontado para os nodes deletados
  *raiz = NULL;
}
