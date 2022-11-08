#include <stdio.h>
#include <string.h>

// #include "ABBI/ABBI.h"
#include "ABBR/ABBR.h"

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
  inserirNodeR(&raiz, lucas);
  inserirNodeR(&raiz, gabriel);
  inserirNodeR(&raiz, bianca);
  inserirNodeR(&raiz, restaurante);
  inserirNodeR(&raiz, ana);
  inserirNodeR(&raiz, joao);
  inserirNodeR(&raiz, pedro);
  inserirNodeR(&raiz, sofia);

  printf("TESTE: contarNodes\n");
  printf("%d nodes\n", contarNodesR(raiz));

  printf("\nTESTE: imprimirNode\n");
  imprimirNode(raiz);
  imprimirNode(raiz->esq);
  imprimirNode(raiz->esq->esq);
  imprimirNode(raiz->esq->dir);
  imprimirNode(raiz->esq->esq->esq);
  imprimirNode(raiz->dir);
  imprimirNode(raiz->dir->esq);
  imprimirNode(raiz->dir->dir);

  printf("\nTESTE: imprimirArvore\n");
  imprimirArvoreR(raiz);

  printf("\nTESTE: removerNode (node sem filhos)\n");
  imprimirNode(raiz->dir); // pai do node a ser removido
  imprimirNode(raiz->dir->dir); // node a ser removido
  removerNodeR(&raiz, "Sofia S.");
  imprimirNode(raiz->dir); // a propriedade dir desse node agora está NULL
  imprimirNode(raiz->dir->dir);

  printf("\nTESTE: removerNode (node com 1 filho)\n");
  imprimirNode(raiz->esq); // pai do node a ser removido
  imprimirNode(raiz->esq->esq); // node a ser removido
  removerNodeR(&raiz, "Bianca");
  imprimirNode(raiz->esq); // a propriedade dir desse node agora está NULL
  imprimirNode(raiz->esq->esq);

  printf("\nTESTE: removerNode (node com 2 filhos)\n");
  imprimirNode(raiz->esq); // pai do node que vai substituir o node a ser removido
  imprimirNode(raiz); // node a ser removido
  removerNodeR(&raiz, "Lucas");
  imprimirNode(raiz->esq); // a propriedade dir desse node agora está NULL
  imprimirNode(raiz); // novo node que está no lugar do node que foi removido

  printf("\nTESTE: procurarNode\n");
  imprimirNode(procurarNodeR(raiz, "Gabriel"));
  imprimirNode(procurarNodeR(raiz, "Pedro da Silva"));

  printf("\nTESTE: destruirArvore\n");
  printf("%d nodes\n", contarNodesR(raiz));
  imprimirNode(raiz);
  destruirArvoreR(&raiz);
  printf("%d nodes\n", contarNodesR(raiz));
  imprimirNode(raiz);

  return 0;
}
