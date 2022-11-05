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

void criarNode(node **ref, contato c) {
  *ref = malloc(sizeof(node));

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
        printf("!!! esq\n");
        (*raiz)->esq = tmp->esq;
      }

      if ( *raiz != tmp->dir ) {
        printf("!!! dir\n");
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

// recursivamente percorre a árvore p/ encontrar o contato desejado
node *procurarNode(node *raiz, char *nome) {
  if (raiz == NULL) return NULL;

  int cmp = strcmp(nome, raiz->contato.nome);

  if ( cmp == 0 ) return raiz;
  return procurarNode(cmp < 0 ? raiz->esq : raiz->dir, nome);
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

int main() {
  contato harry = { "Harry", "7777-7777" };
  contato hermione = { "Hermione Granger", "1234-5678" };
  contato ron = { "Ron", "0000-0000" };
  contato dumbledore = { "Albus Dumbledore", "1212-1212" };
  contato snape = { "Severus Snape", "9669-6996" };
  contato luna = { "Luna", "7981-6134" };
  contato hogwarts = { "Hogwarts School of Magic", "+44 1234-4321" };

  node *raiz = NULL;

  imprimirNode(raiz);

  inserirNode(&raiz, luna);
  inserirNode(&raiz, hermione);
  inserirNode(&raiz, ron);
  inserirNode(&raiz, harry);
  inserirNode(&raiz, snape);
  inserirNode(&raiz, dumbledore);
  inserirNode(&raiz, hogwarts);

  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // imprimirNode(raiz->esq->esq);
  // imprimirNode(raiz->esq->dir);
  // imprimirNode(raiz->esq->esq->esq);
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->dir);

  // printf("\n");
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->dir);
  // removerNode(&raiz, "Severus Snape");
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->dir);

  // printf("\n");

  // imprimirNode(raiz);
  // node *d = raiz->dir;
  // imprimirNode(d);
  // imprimirNode(raiz->dir->dir);
  // removerNode(&(raiz->dir), "Ron");
  // imprimirNode(raiz);
  // imprimirNode(raiz->dir);
  // imprimirNode(d);

  // destruirArvore(&raiz);
  // imprimirNode(raiz);

  // printf("\n");

  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // node *r = raiz->esq;
  // removerNode(&raiz, "Hermione Granger");
  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // imprimirNode(r);

  // printf("\n");
  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // imprimirNode(raiz->esq->esq);
  // imprimirNode(raiz->esq->dir);
  // imprimirNode(raiz->esq->esq->esq);
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->dir);

  // imprimirNode(raiz);
  // node *r = raiz;
  // removerNode(&raiz, "Luna");
  // imprimirNode(raiz);
  // imprimirNode(r);

  // printf("\n");
  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // imprimirNode(raiz->esq->esq);
  // imprimirNode(raiz->esq->dir);
  // imprimirNode(raiz->esq->esq->esq);
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->dir);

  printf("\n");
  imprimirArvore(raiz);

  printf("\n");
  printf("%d\n", contarNodes(raiz));

  printf("\n");
  imprimirNode(procurarNode(raiz, "Hogwarts School of Magic"));
  imprimirNode(procurarNode(raiz, "Minerva"));
  imprimirNode(procurarNode(raiz, "Severus Snape"));

  printf("\n");
  imprimirArvore(raiz);

  return 0;
}
