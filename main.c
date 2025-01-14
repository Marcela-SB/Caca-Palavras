#include <stdio.h>
#include <stdlib.h>

#include "jogo.c"

int main(void) {
    Tabuleiro tabuleiro;
    NoAVL *resultados = NULL;
    NoTrie *palavras = criar_NoTrie();
    int opcao = -1;
    

    carregarTabuleiro("arquivos/tabuleiro.txt", &tabuleiro);
    carregarPalavras("arquivos/palavras.txt", palavras);

    printf("################ CACA PALAVRAS ################\n");

    while (opcao != 0) {
        printf("\n-----------------------------------------");
        printf("\nO que deseja fazer?\
        \n1- Ver tabuleiro\
        \n2- Ver palavras\
        \n3- Buscar palavras no tabuleiro\
        \n4- Ver palavras encontradas\
        \n0- sair\
        \n\n>> ");

        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("\n");
            exibirTabuleiro(tabuleiro);
            break;
        case 2:
            printf("PALAVRAS CARREGADAS:\n");
            imprimir_trie(palavras);
            break;
        case 3:
            printf("BUSCANDO PALAVRAS...\n");
            buscarPalavras(tabuleiro, palavras, &resultados);
            break;
        case 4:
            printf("PALAVRAS ENCONTRADAS:\n");
            imprimirResultados(resultados);
            break;
        case 0:
            printf("SAINDO...");
            break;
        default:
            printf("Valor invalido!");
            break;
        }
    }
    return 0;
}