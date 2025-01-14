#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"


int obter_altura(NoAVL* no) {
  if(no == NULL)
    return -1;
  else
    return no->altura;
}



int calcular_fator_de_balanceamento(NoAVL* no) {
  if(no == NULL)
    return 0;
  else
    return obter_altura(no->esquerdo) - obter_altura(no->direito);
}



NoAVL *criar_NoAVL(char *palavra) {
    NoAVL *novo_no = (NoAVL *)malloc(sizeof(NoAVL));

    if (novo_no) {
        novo_no->palavra = (char *)malloc(strlen(palavra) + 1);
        strcpy(novo_no->palavra, palavra);

        novo_no->esquerdo = NULL;
        novo_no->direito = NULL;
        novo_no->altura = 1;  // A altura inicial do nó é 1
    }

    return novo_no;
}



void liberar_NoAVL(NoAVL *raiz) {
    if (raiz == NULL)
        return;

    liberar_NoAVL(raiz->esquerdo);
    liberar_NoAVL(raiz->direito);

    free(raiz->palavra);
    free(raiz);
}



NoAVL* rotacao_direita(NoAVL* y) {
  NoAVL* x = y->esquerdo;
  NoAVL* z = x->direito;

  x->direito = y;
  y->esquerdo = z;

  if(obter_altura(y->esquerdo) > obter_altura(y->direito))
    y->altura = 1 + obter_altura(y->esquerdo);
  else
    y->altura = 1 + obter_altura(y->direito);

  if(obter_altura(x->esquerdo) > obter_altura(x->direito))
    x->altura = 1 + obter_altura(x->esquerdo);
  else
    x->altura = 1 + obter_altura(x->direito);

  return x;
}



NoAVL* rotacao_esquerda(NoAVL* x) {
  NoAVL* y = x->direito;
  NoAVL* z = y->esquerdo;

  y->esquerdo = x;
  x->direito = z;

  if(obter_altura(x->esquerdo) > obter_altura(x->direito))
    x->altura = 1 + obter_altura(x->esquerdo);
  else
    x->altura = 1 + obter_altura(x->direito);

  if (obter_altura(y->esquerdo) > obter_altura(y->direito))
    y->altura = 1 + obter_altura(y->esquerdo);
  else
    y->altura = 1 + obter_altura(y->direito);

  return y;
}



NoAVL* inserir_NoAVL(NoAVL* no, char* palavra) {
  if (no == NULL) {
    return criar_NoAVL(palavra);
  }

  // Comparando as palavras lexicograficamente
  if (strcmp(palavra, no->palavra) < 0) {
    no->esquerdo = inserir_NoAVL(no->esquerdo, palavra);  
  }
  else if (strcmp(palavra, no->palavra) > 0) {
    no->direito = inserir_NoAVL(no->direito, palavra);  
  }
  else {
    // Palavra duplicada, não inserir
    return no;
  }

  // Atualiza a altura do nó atual
  if(obter_altura(no->esquerdo) > obter_altura(no->direito))
    no->altura = 1 + obter_altura(no->esquerdo);
  else
    no->altura = 1 + obter_altura(no->direito);

  // Calcula o fator de balanceamento do nó atual
  int balanceamento = calcular_fator_de_balanceamento(no);

  // Caso 1: Desbalanceamento à esquerda (Rotação à direita).
  if (balanceamento > 1 && strcmp(palavra, no->esquerdo->palavra) < 0) {
    return rotacao_direita(no);
  }

  // Caso 2: Desbalanceamento à direita (Rotação à esquerda).
  if (balanceamento < -1 && strcmp(palavra, no->direito->palavra) > 0) {
    return rotacao_esquerda(no);
  }

  // Caso 3: Desbalanceamento esquerda-direita (Rotação dupla esquerda-direita).
  if (balanceamento > 1 && strcmp(palavra, no->esquerdo->palavra) > 0) {
    no->esquerdo = rotacao_esquerda(no->esquerdo);
    return rotacao_direita(no);
  }

  // Caso 4: Desbalanceamento direita-esquerda (Rotação dupla direita-esquerda).
  if (balanceamento < -1 && strcmp(palavra, no->direito->palavra) < 0) {
    no->direito = rotacao_direita(no->direito);
    return rotacao_esquerda(no);
  }

  return no;  // Retorna o nó (pode ter sido rotacionado)
}



NoAVL* menor_valorNoAVL(NoAVL* no) {
  NoAVL* atual = no;
  
  while(atual->esquerdo != NULL)
    atual = atual->esquerdo;

  return atual;
}



NoAVL* remover_NoAVL(NoAVL* raiz, char* palavra) {
  if (raiz == NULL) {
    return raiz;
  }

  // Comparando as palavras lexicograficamente
  if (strcmp(palavra, raiz->palavra) < 0) {
    raiz->esquerdo = remover_NoAVL(raiz->esquerdo, palavra);
  } 
  else if (strcmp(palavra, raiz->palavra) > 0) {
    raiz->direito = remover_NoAVL(raiz->direito, palavra);
  } 
  else {
    // Nó com apenas um filho ou nenhum.
    if ((raiz->esquerdo == NULL) || (raiz->direito == NULL)) {
      NoAVL* temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;
      
      if (temp == NULL) {  // Caso de nenhum filho
        temp = raiz;
        raiz = NULL;
      } 
      else {   // Caso com um filho
        *raiz = *temp;
      }

      free(temp);  // Libera o nó removido
    }
    else { // Caso de dois filhos: obtém o sucessor. 
      NoAVL* temp = menor_valorNoAVL(raiz->direito);
      raiz->palavra = temp->palavra;
      raiz->direito = remover_NoAVL(raiz->direito, temp->palavra);
    }
  }

  // Se a árvore tinha apenas um nó
  if (raiz == NULL) {
    return raiz;
  }

  if(obter_altura(raiz->esquerdo) > obter_altura(raiz->direito))
    raiz->altura = 1 + obter_altura(raiz->esquerdo);
  else
    raiz->altura = 1 + obter_altura(raiz->direito);

  int balanceamento = calcular_fator_de_balanceamento(raiz);

  // Caso 1: Desbalanceamento à esquerda
  if (balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) >= 0) {
    return rotacao_direita(raiz);
  }

  // Caso 2: Desbalanceamento esquerda-direita
  if (balanceamento > 1 && calcular_fator_de_balanceamento(raiz->esquerdo) < 0) {
    raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
    return rotacao_direita(raiz);
  }

  // Caso 3: Desbalanceamento à direita
  if (balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) <= 0) {
    return rotacao_esquerda(raiz);
  }

  // Caso 4: Desbalanceamento direita-esquerda
  if (balanceamento < -1 && calcular_fator_de_balanceamento(raiz->direito) > 0) {
    raiz->direito = rotacao_direita(raiz->direito);
    return rotacao_esquerda(raiz);
  }

  return raiz;
}



void imprimir_em_ordem(NoAVL* raiz) {
  if(raiz != NULL){
    imprimir_em_ordem(raiz->esquerdo);
    printf("- %s\n", raiz->palavra);
    imprimir_em_ordem(raiz->direito);
  }
}


/*
int main(void) {
  NoAVL* raiz = NULL;

  raiz = inserir_NoAVL(raiz, 10);
  raiz = inserir_NoAVL(raiz, 20);
  raiz = inserir_NoAVL(raiz, 30);
  raiz = inserir_NoAVL(raiz, 40);
  raiz = inserir_NoAVL(raiz, 50);
  raiz = inserir_NoAVL(raiz, 25);

  printf("Arvore AVL em ordem: ");
  imprimir_em_ordem(raiz);
  printf("\n");

  raiz = remover_no(raiz, 40);

  printf("Arvore AVL apos remocao: ");
  imprimir_em_ordem(raiz);
  printf("\n");

  return 0;
}
*/