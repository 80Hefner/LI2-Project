//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"


// exemplo de uma função para imprimir o estado (Tabuleiro)
/**
 * Função responsável por imprimir taubleiro para um Estado de jogo dado.
 * @param e - Estado atual do jogo
 */
void printa(ESTADO e)
{
    char c = ' ';

    printf("\n");
    printf("  1 2 3 4 5 6 7 8\n");

    for (int i = 0; i < 8; i++) {
        printf("%d ", i+1);

        for (int j = 0; j < 8; j++) {
            switch (e.grelha[i][j]) {
                case VALOR_O: {
                    c = 'O';
                    break;
                }
                case VALOR_X: {
                    c = 'X';
                    break;
                }
                case VAZIA: {
                    c = '-';
                    break;
                }
                case SUG: {
                    c = '.';
                    break;
                }
                case HINT: {
                    c = '?';
                    break;
                }
            }
            printf("%c ", c);

        }
        printf("\n");

    }

    printf("Score jogador X: %d\n", e.score_x);
    printf("Score jogador O: %d\n", e.score_o);

    if (e.modo == '0' || (e.modo == '1' && e.peca != e.peca_bot)){
        if (e.peca == VALOR_O) printf("(O)\n");
        else printf("(X)\n");

        printf("(?) Ajuda");
    }
}
