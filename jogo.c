#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "jogo.h"

Tabuleiro inicializarTabuleiro(Tabuleiro t){
    t.linhas = 0;
    t.colunas = 0;
    t.matriz = NULL;
    return t;
}

void carregarTabuleiro(const char *caminho, Tabuleiro *t) {
    int i, j;

    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo do tabuleiro!\n");  // Exibe o erro específico
        return;
    }

    // Lê a primeira linha com os tamanhos
    if (fscanf(arquivo, "%d %d", &t->linhas, &t->colunas) != 2 || t->linhas <= 0 || t->colunas <= 0) {
        fprintf(stderr, "Dimensões inválidas para o tabuleiro!\n");
        fclose(arquivo);
        return;
    }

    // Alocando memória para o tabuleiro
    t->matriz = (char **)malloc(t->linhas * sizeof(char *));
    if (t->matriz == NULL) {
        printf("Erro na alocação de memória para o tabuleiro!\n");
        fclose(arquivo);
        return;
    }

    for (i = 0; i < t->linhas; i++) {
        t->matriz[i] = (char *)malloc(t->colunas * sizeof(char));
        if (t->matriz[i] == NULL) {
            printf("Erro na alocação de memória para a linha %d!\n", i);
            fclose(arquivo);
            return;
        }
    }

    // Lê os caracteres do tabuleiro
    for (i = 0; i < t->linhas; ++i) {
        for (j = 0; j < t->colunas; ++j) {
            char ch;
            if (fscanf(arquivo, " %c", &ch) != 1) {
                fprintf(stderr, "Erro ao ler o caractere na posição [%d][%d]!\n", i, j);
                fclose(arquivo);
                return;
            }
            t->matriz[i][j] = ch;
        }
    }

    fclose(arquivo);
}


void carregarPalavras(char *caminho, NoTrie *triePalavras) {
    FILE *arquivo = fopen(caminho, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de palavras!\n");  // Exibe o erro específico
        return;
    }

    char palavra[51];
    while (fscanf(arquivo, "%50s", palavra) == 1) {
        inserir_NoTrie(triePalavras, palavra);
    }

    fclose(arquivo);
}


void buscarPalavras(Tabuleiro t, NoTrie *palavras, NoAVL **resultados) {
    int i, j;
    char palavra[50]; // palavras formadas

    for (i = 0; i < t.linhas; i++) {
        for (j = 0; j < t.colunas; j++) {
            // Explorar nas 8 direções possíveis: horizontal, vertical, e diagonais
            // Direção 1: Para a direita (horizontal)
            explorarDirecao(t, i, j, 0, 1, palavra, palavras, resultados); 

            // Direção 2: Para a esquerda (horizontal)
            explorarDirecao(t, i, j, 0, -1, palavra, palavras, resultados);

            // Direção 3: Para baixo (vertical)
            explorarDirecao(t, i, j, 1, 0, palavra, palavras, resultados);  // Direção para baixo
            // Direção 4: Para cima (vertical)
            explorarDirecao(t, i, j, -1, 0, palavra, palavras, resultados);

            // Direção 5: Diagonal inferior direita
            explorarDirecao(t, i, j, 1, 1, palavra, palavras, resultados);  // Diagonal para baixo à direita
            // Direção 6: Diagonal superior esquerda
            explorarDirecao(t, i, j, -1, -1, palavra, palavras, resultados);

            // Direção 7: Diagonal inferior esquerda
            explorarDirecao(t, i, j, 1, -1, palavra, palavras, resultados);

            // Direção 8: Diagonal superior direita
            explorarDirecao(t, i, j, -1, 1, palavra, palavras, resultados);
        }
    }
}

void explorarDirecao(Tabuleiro t, int x, int y, int dx, int dy, char *palavra, NoTrie *palavras, NoAVL **resultados) {
    int i = 0;
    int tamanho_max_palavra = 50;
    while (x >= 0 && x < t.linhas && y >= 0 && y < t.colunas && i < tamanho_max_palavra) {
        // Formar palavra
        palavra[i++] = t.matriz[x][y];
        palavra[i] = '\0';

        // Verificar se a palavra é válida na Trie
        if (buscar_NoTrie(palavras, palavra)) {
            *resultados = inserir_NoAVL(*resultados, palavra);
        }

        // Avançar na direção
        x += dx;
        y += dy;
    }
}


void imprimirResultados(NoAVL *no) {
    if (no == NULL) {
        printf("Nenhuma palavra encontrada...");
    }
    else{
        imprimir_em_ordem(no);
    }
}


void exibirTabuleiro(Tabuleiro t) {
    printf("Tabuleiro:\n");
    int y, x;
    for (y = 0; y < t.linhas; y++) {
        for (x = 0; x < t.colunas; x++) {
            printf("%c ", t.matriz[y][x]); 
        }
        printf("\n");
    }
}