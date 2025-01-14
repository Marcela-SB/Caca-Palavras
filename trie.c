#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "trie.h"

NoTrie *criar_NoTrie() {
  NoTrie *novo_no = (NoTrie *)malloc(sizeof(NoTrie));
  
  if(novo_no) {
    novo_no->fim_da_palavra = false;
    int i;
    for (i = 0; i < ALFABETO; i++) {
      novo_no->filhos[i] = NULL;
    }
  }
  
  return novo_no;
}


void inserir_NoTrie(NoTrie *raiz, char *palavra) {
  NoTrie *atual = raiz;
  
  int i;
  for (i = 0; palavra[i] != '\0'; i++) {
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      atual->filhos[indice] = criar_NoTrie();

    atual = atual->filhos[indice];
  }
  
  atual->fim_da_palavra = true;
}


bool buscar_NoTrie(NoTrie *raiz, char *palavra) {
  NoTrie *atual = raiz;
  
  int i;
  for (i = 0; palavra[i] != '\0'; i++) {
    palavra[i] = tolower(palavra[i]); // Converte o caractere para minúscula
  }
  for (i = 0; palavra[i] != '\0'; i++) {
    int indice = palavra[i] - 'a';

    if(atual->filhos[indice] == NULL)
      return false;

    atual = atual->filhos[indice];
  }
  
  return atual->fim_da_palavra;
}


void liberar_trie(NoTrie *raiz) {
  if(raiz == NULL)
    return;

  int i;
  for(i = 0; i < ALFABETO; i++)
        liberar_trie(raiz->filhos[i]);

  free(raiz);
}


// Função auxiliar para imprimir as palavras da TRIE
void imprimir_trie_aux(NoTrie *no, char *prefixo, int comprimento) {
    // Se o nó for nulo, não há nada a imprimir
    if (no == NULL) {
        return;
    }

    // Se for o fim de uma palavra, imprime o prefixo até aqui
    if (no->fim_da_palavra) {
        prefixo[comprimento] = '\0'; // Termina a string
        printf("%s\n", prefixo); // Imprime a palavra
    }

    // Recorre nos filhos, um por um, para construir palavras
    int i;
    for (i = 0; i < ALFABETO; i++) {
        if (no->filhos[i] != NULL) {
            // Adiciona a letra correspondente ao prefixo
            prefixo[comprimento] = 'a' + i;
            imprimir_trie_aux(no->filhos[i], prefixo, comprimento + 1);
        }
    }
}

// Função principal para imprimir todas as palavras armazenadas na TRIE
void imprimir_trie(NoTrie *raiz) {
    char prefixo[100]; // Supondo que as palavras não sejam maiores que 100 caracteres
    imprimir_trie_aux(raiz, prefixo, 0);
}


/*int main(void) {
  No *raiz = criar_no();

  const char *palavras1[] = {"casa","carro","casaco","cadeira","sapato"};
  const char *palavras2[] = {"casa","carro","casaco","cadeira","sapato","casco","nuvem","prato"};

  for(int i=0; i<5; i++)
   inserir(raiz, palavras1[i]);
  
  for(int i=0; i<8; i++)
    if(buscar(raiz, palavras2[i]))
      printf("A palavra %s esta na Trie.\n", palavras2[i]);
    else
      printf("A palavra %s nao esta na Trie.\n", palavras2[i]);
    
  liberar_trie(raiz);

  return 0;
}
*/