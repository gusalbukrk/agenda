#include <stdio.h>
#include <string.h>

#include "ABB.h"
#include "stack.h"

// https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack

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
