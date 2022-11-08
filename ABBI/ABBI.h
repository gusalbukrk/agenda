#ifndef ABBI
#define ABBI

  typedef struct Contato {
    char nome[50];
    char telefone[20];
  } contato;

  // estrutura dos nodes da Árvore Binária de Busca (ABB)
  typedef struct Node {
    contato contato;
    struct Node *esq;
    struct Node *dir;
  } node;

  void imprimirNode(node *n);
  void imprimirArvoreI(node *raiz);
  void inserirNodeI(node **raiz, contato c);
  void removerNodeI(node **raiz, char *nome);
  node *procurarNodeI(node *raiz, char *nome);
  int contarNodesI(node *raiz);
  void destruirArvoreI(node **raiz);

#endif
