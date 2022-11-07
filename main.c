#include <stdio.h>
#include <string.h>

#include "ABB.h"
#include "stack.h"

// https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack

void preorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  node *currNode = raiz, *prevNode = NULL;

  while ( s->quant != 0 || currNode != NULL ) {
    if (currNode != NULL) {
      callback(currNode);
      push(&s, currNode);
      currNode = currNode->esq;
    } else {
      prevNode = pop(&s);
      currNode = prevNode->dir;
    }
  }
}

void inorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  node *currNode = raiz;

  while ( s->quant != 0 || currNode != NULL ) {
    if (currNode != NULL) {
      push(&s, currNode);
      currNode = currNode->esq;
    } else {
      currNode = pop(&s);
      callback(currNode);
      currNode = currNode->dir;
    }
  }
}

void postorder(node *raiz, void callback(node *n)) {
  if (raiz == NULL) return;

  stack *s = NULL; initStack(&s);
  stack *dir = NULL; initStack(&dir);
  node *currNode = raiz;

  while ( s->quant != 0 || currNode != NULL ) {
    if (currNode != NULL) {
      if (currNode->dir != NULL) push(&dir, currNode->dir);
      push(&s, currNode);
      currNode = currNode->esq;
    } else {
      currNode = &(s->values[0]);
      if (
        dir->quant != 0 &&
        ( currNode->dir != NULL && (strcmp(currNode->dir->contato.nome, dir->values[0].contato.nome) == 0) )
      ) {
        currNode = pop(&dir);
      } else {
        callback(currNode);
        pop(&s);
        currNode = NULL;
      }
    }
  }
}

int main() {
  contato ana = { "Ana Pereira", "99261-9761" };
  contato bianca = { "Bianca", "(61) 99281-7747" };
  contato gabriel = { "Gabriel", "981123773" };
  contato joao = { "João Guilherme", "(64) 2352-9821" };
  contato lucas = { "Lucas", "+55 (11) 3213-7698" };
  contato pedro = { "Pedro da Silva", "3441-9822" };
  contato restaurante = { "Restaurante", "(64) 3411-2388" };
  contato sofia = { "Sofia S.", "(11) 99268-9821" };

  node *raiz = NULL;

  //             Lucas
  //      Gabriel     Restaurante
  //   Bianca  João  Pedro   Sofia
  //  Ana
  inserirNode(&raiz, lucas);
  inserirNode(&raiz, gabriel);
  inserirNode(&raiz, bianca);
  inserirNode(&raiz, restaurante);
  inserirNode(&raiz, ana);
  inserirNode(&raiz, joao);
  inserirNode(&raiz, pedro);
  inserirNode(&raiz, sofia);

  printf("TESTE: contarNodes\n");
  printf("%d nodes\n", contarNodes(raiz));

  // printf("\nTESTE: imprimirNode\n");
  // imprimirNode(raiz);
  // imprimirNode(raiz->esq);
  // imprimirNode(raiz->esq->esq);
  // imprimirNode(raiz->esq->dir);
  // imprimirNode(raiz->esq->esq->esq);
  // imprimirNode(raiz->dir);
  // imprimirNode(raiz->dir->esq);
  // imprimirNode(raiz->dir->dir);

  // printf("\nTESTE: imprimirArvore\n");
  // imprimirArvore(raiz);

  // printf("\nTESTE: removerNode (node sem filhos)\n");
  // imprimirNode(raiz->dir); // pai do node a ser removido
  // imprimirNode(raiz->dir->dir); // node a ser removido
  // removerNode(&raiz, "Sofia S.");
  // imprimirNode(raiz->dir); // a propriedade dir desse node agora está NULL
  // imprimirNode(raiz->dir->dir);

  // printf("\nTESTE: removerNode (node com 1 filho)\n");
  // imprimirNode(raiz->esq); // pai do node a ser removido
  // imprimirNode(raiz->esq->esq); // node a ser removido
  // removerNode(&raiz, "Bianca");
  // imprimirNode(raiz->esq); // a propriedade dir desse node agora está NULL
  // imprimirNode(raiz->esq->esq);

  // printf("\nTESTE: removerNode (node com 2 filhos)\n");
  // imprimirNode(raiz->esq); // pai do node que vai substituir o node a ser removido
  // imprimirNode(raiz); // node a ser removido
  // removerNode(&raiz, "Lucas");
  // imprimirNode(raiz->esq); // a propriedade dir desse node agora está NULL
  // imprimirNode(raiz); // novo node que está no lugar do node que foi removido

  // printf("\nTESTE: procurarNode\n");
  // imprimirNode(procurarNode(raiz, "Gabriel"));
  // imprimirNode(procurarNode(raiz, "Pedro da Silva"));

  // printf("\nTESTE: destruirArvore\n");
  // printf("%d nodes\n", contarNodes(raiz));
  // imprimirNode(raiz);
  // destruirArvore(&raiz);
  // printf("%d nodes\n", contarNodes(raiz));
  // imprimirNode(raiz);

  // printf("\n");
  // stack *s = NULL;
  // push(&s, raiz);
  // push(&s, raiz->esq);
  // pop(&s);
  // push(&s, raiz->dir);
  // printStack(s);

  void (*fn)(node *n) = &imprimirNode;

  printf("\nPREORDER\n");
  preorder(raiz, fn);
  printf("\nINORDER\n");
  inorder(raiz, fn);
  printf("\nPOSTORDER\n");
  postorder(raiz, fn);

  return 0;
}
