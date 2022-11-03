#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contato {
  char nome[50];
  char telefone[20];
} contato;

// estrutura dos nós da árvore binária de busca
typedef struct Node {
  contato contato;
  struct Node *esq;
  struct Node *dir;
} node;

void printNode(node *n) {
  if (n == NULL) {
    printf("(nil)\n");
    return;
  }

  printf("(%p) = { %s, %s }, %p, %p\n", n, n->contato.nome, n->contato.telefone, n->esq, n->dir);
}

void criaNode(node **ref, contato c) {
  *ref = malloc(sizeof(node));

  (*ref)->contato = c;
  (*ref)->esq = NULL;
  (*ref)->dir = NULL;
}

void inserirNodeRecursiva(node **raiz, contato c) {
  // n é o endereço do node da esquerda ou da direita
  // depende da direção em que o novo contato deve ser inserido
  node **n = strcmp(c.nome, (*raiz)->contato.nome) < 0 ? &((*raiz)->esq) : &((*raiz)->dir);

  // caso node n não esteja vazio
  // use recursão para executar essa função novamente dessa vez usando n como raiz
  if (*n != NULL) {
    inserirNodeRecursiva(n, c);
    return;
  }

  // caso node n esteja vazio, insira o novo contato
  criaNode(n, c);
}

void inserirNode(node **raiz, contato c) {
  // caso a árvore esteja vazia, adicione o primeiro elemento
  if ( *raiz == NULL ) { 
    criaNode(raiz, c);
    return;
  }

  // caso a árvore já possua nodes
  // vasculhe a árvore recursivamente até encontrar a folha em que adicionar o novo contato
  inserirNodeRecursiva(raiz, c);
}

int main() {
  contato harry = { "Harry", "7777-7777" };
  contato hermione = { "Hermione Granger", "1234-5678" };
  contato ron = { "Ron", "0000-0000" };
  contato dumbledore = { "Alvus Dumbledore", "1212-1212" };
  contato snape = { "Severus Snape", "9669-6996" };
  contato luna = { "Luna", "7981-6134" };

  node *raiz = NULL;

  printNode(raiz);

  inserirNode(&raiz, luna);
  inserirNode(&raiz, hermione);
  inserirNode(&raiz, ron);
  inserirNode(&raiz, harry);
  inserirNode(&raiz, snape);

  printNode(raiz);
  printNode(raiz->esq);
  printNode(raiz->esq->esq);
  printNode(raiz->dir);
  printNode(raiz->dir->dir);

  return 0;
}
