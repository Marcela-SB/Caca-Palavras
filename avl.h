#ifndef AVL_H
#define AVL_H

  #include <stdio.h>
  #include <stdlib.h>

  typedef struct NoAVL{
    char *palavra;
    struct NoAVL* esquerdo;
    struct NoAVL* direito;
    int altura;
  }NoAVL;


  int obter_altura(NoAVL* NoAVL);
  int calcular_fator_de_balanceamento(NoAVL* NoAVL);
  NoAVL* criar_NoAVL(char *palavra);
  void liberar_NoAVL(NoAVL *raiz);
  NoAVL* rotacao_direita(NoAVL* y);
  NoAVL* rotacao_esquerda(NoAVL* x);
  NoAVL* inserir_NoAVL(NoAVL* NoAVL, char *palavra);
  NoAVL* menor_valorNoAVL(NoAVL* NoAVL);
  NoAVL* remover_NoAVL(NoAVL* raiz, char *palavra);
  void imprimir_em_ordem(NoAVL* raiz);

#endif