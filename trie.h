#ifndef TRIE_H
#define TRIE_H

  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>

  #define ALFABETO 26

  typedef struct NoTrie{
    struct NoTrie *filhos[ALFABETO];
    bool fim_da_palavra;
  }NoTrie;

  NoTrie *criar_NoTrie();

  void inserir_NoTrie(NoTrie *raiz, char *palavra);

  bool buscar_NoTrie(NoTrie *raiz, char *palavra);

  void liberar_trie(NoTrie *raiz);

void imprimir_trie_aux(NoTrie *no, char *prefixo, int comprimento);
void imprimir_trie(NoTrie *raiz);

#endif