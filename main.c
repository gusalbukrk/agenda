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

// recursivamente percorre a árvore p/ encontrar a folha em que adicionar o novo contato
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
  criaNode(n, c);
}

void inserirNode(node **raiz, contato c) {
  // caso a árvore esteja vazia, adicione o primeiro elemento
  if ( *raiz == NULL ) { 
    criaNode(raiz, c);
    return;
  }

  // caso a árvore já possua nodes
  inserirNodeAux(raiz, c);
}

node *retornarDescendenteMaisADireita(node *raiz) {
  if (raiz->dir == NULL) return raiz;

  return retornarDescendenteMaisADireita(raiz->dir);
}

// recursivamente percorre a árvore p/ encontar o node a ser removido
// caso raiz.contato.nome é igual a nome, raiz será removida
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
      node *n = retornarDescendenteMaisADireita((*raiz)->esq);

      // free(*raiz);
      // *raiz = n;

      // (*raiz)->contato = n->contato;

      node *tmp = *raiz;

      *raiz = n;

      if ( *raiz != tmp->esq ) {
        printf("!!! esq\n");
        (*raiz)->esq = tmp->esq;
      }

      if ( *raiz != tmp->dir ) {
        printf("!!! dir\n");
        (*raiz)->dir = tmp->dir;
      }

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

// recursivamente percorre a árvore em pós-ordem p/ deletar todos os nodes
void destruirArvoreAux(node *raiz) {
  if (raiz == NULL) return;

  destruirArvoreAux(raiz->esq);
  destruirArvoreAux(raiz->dir);
  free(raiz);
}

void destruirArvore(node **raiz) {
  destruirArvoreAux(*raiz);
  
  // atribua NULL para a raiz para que não haja nenhuma variável apontado para os nodes deletados
  *raiz = NULL;
}

int main() {
  contato harry = { "Harry", "7777-7777" };
  contato hermione = { "Hermione Granger", "1234-5678" };
  contato ron = { "Ron", "0000-0000" };
  contato dumbledore = { "Albus Dumbledore", "1212-1212" };
  contato snape = { "Severus Snape", "9669-6996" };
  contato luna = { "Luna", "7981-6134" };
  contato hogwarts = { "Hogwarts School of Magic", "+44 1234-4321" };

  node *raiz = NULL;

  printNode(raiz);

  inserirNode(&raiz, luna);
  inserirNode(&raiz, hermione);
  inserirNode(&raiz, ron);
  inserirNode(&raiz, harry);
  inserirNode(&raiz, snape);
  inserirNode(&raiz, dumbledore);
  inserirNode(&raiz, hogwarts);

  printNode(raiz);
  printNode(raiz->esq);
  printNode(raiz->esq->esq);
  printNode(raiz->esq->dir);
  printNode(raiz->esq->esq->esq);
  printNode(raiz->dir);
  printNode(raiz->dir->dir);

  // printf("\n");
  // printNode(raiz->dir);
  // printNode(raiz->dir->dir);
  // removerNode(&raiz, "Severus Snape");
  // printNode(raiz->dir);
  // printNode(raiz->dir->dir);

  // printf("\n");

  // printNode(raiz);
  // node *d = raiz->dir;
  // printNode(d);
  // printNode(raiz->dir->dir);
  // removerNode(&(raiz->dir), "Ron");
  // printNode(raiz);
  // printNode(raiz->dir);
  // printNode(d);

  // destruirArvore(&raiz);
  // printNode(raiz);

  printf("\n");

  printNode(raiz);
  printNode(raiz->esq);
  node *r = raiz->esq;
  removerNode(&raiz, "Hermione Granger");
  printNode(raiz);
  printNode(raiz->esq);
  printNode(r);

  printf("\n");
  printNode(raiz);
  printNode(raiz->esq);
  printNode(raiz->esq->esq);
  printNode(raiz->esq->dir);
  printNode(raiz->esq->esq->esq);
  printNode(raiz->dir);
  printNode(raiz->dir->dir);

  // printNode(raiz);
  // node *r = raiz;
  // removerNode(&raiz, "Luna");
  // printNode(raiz);
  // printNode(r);

  // printf("\n");
  // printNode(raiz);
  // printNode(raiz->esq);
  // printNode(raiz->esq->esq);
  // printNode(raiz->esq->dir);
  // printNode(raiz->esq->esq->esq);
  // printNode(raiz->dir);
  // printNode(raiz->dir->dir);

  return 0;
}
