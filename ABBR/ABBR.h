#ifndef ABBR
#define ABBR // Árvore Binária de Busca - recursiva

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
  void imprimirArvoreR(node *raiz);
  void inserirNodeR(node **raiz, contato c);
  void removerNodeR(node **raiz, char *nome);
  node *procurarNodeR(node *raiz, char *nome);
  int contarNodesR(node *raiz);
  void destruirArvoreR(node **raiz);

#endif
