#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "ABB.h"

// https://www.geeksforgeeks.org/problem-with-using-fgets-gets-scanf-after-scanf-in-c/
void flush() {
  char c;
  while((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
  node *raiz = NULL;

  while (true) {

    printf("1 - Inserir contato\n");
    printf("2 - Excluir contato\n");
    printf("3 - Listar contatos\n");
    printf("4 - Procurar contato\n");
    printf("5 - Calcular tamanho da agenda\n");
    printf("6 - Destruir agenda\n");
    printf("0 - Sair\n");
    printf("\n");

    int option = 0;
    printf("Opção: ");
    if (scanf("%d", &option)) {}
    flush(); printf("\n");

    switch (option) {
      case 1 :
      {
        contato c;
        printf("Nome: ");
        if (scanf("%[^\n]s", c.nome)) {}
        flush();
        
        printf("Telefone: ");
        if (scanf("%[^\n]s", c.telefone)) {}
        flush();

        inserirNode(&raiz, c);

        break;
      }

      case 2:
      {
        char nome[50];
        printf("Nome: ");
        if (scanf("%[^\n]s", nome)) {}
        flush();

        removerNode(&raiz, nome);

        break;
      }

      case 3:
      {
        if (raiz == NULL) printf("\033[A");
        else imprimirArvore(raiz);

        break;
      }

      case 4:
      {
        char nome[50];
        printf("Nome: ");
        if (scanf("%[^\n]s", nome)) {}
        flush();

        node *n = procurarNode(raiz, nome);

        if ( n != NULL) {
          printf("\n");
          imprimirNode(n);
        }

        break;
      }

      case 5:
      {
        printf("quant. de nós: %d\n", contarNodes(raiz));

        break;
      }

      case 6:
      {
        destruirArvore(&raiz);

        break;
      }

      case 0:
      {
        return 0;
        break;
      }

      default:
      {
        printf("ERRO: opção inválida\n");
      }
    }

    printf("\n");
  }
}
