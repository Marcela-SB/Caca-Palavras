#ifndef JOGO_H
#define JOGO_H
  #include <stdio.h>
  #include <stdlib.h>

  #include "avl.c"
  #include "trie.c"

  typedef struct Tabuleiro{
      char **matriz;
      int linhas;
      int colunas;
    }Tabuleiro;

  void carregarTabuleiro(const char *caminho, Tabuleiro *t);

  void carregarPalavras(char *caminho, NoTrie *triePalavras);

  void imprimirResultados(NoAVL *no);


  void exibirTabuleiro(Tabuleiro t);

  void buscarPalavras(Tabuleiro t, NoTrie *palavras, NoAVL **resultados);

  void explorarDirecao(Tabuleiro t, int x, int y, int dx, int dy, char *palavra, NoTrie *palavras, NoAVL **resultados);

#endif