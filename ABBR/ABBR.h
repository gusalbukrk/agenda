#ifndef ABBR
#define ABBR

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
  void imprimirArvore(node *raiz);
  void inserirNode(node **raiz, contato c);
  void removerNode(node **raiz, char *nome);
  node *procurarNode(node *raiz, char *nome);
  int contarNodes(node *raiz);
  void destruirArvore(node **raiz);

#endif
