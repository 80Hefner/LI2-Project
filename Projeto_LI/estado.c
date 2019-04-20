//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"


// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e)
{
    char c = ' ';

    printf("\n");

    for (int i = 0; i < 8; i++) {
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
            }
            printf("%c ", c);

        }
        printf("\n");

    }

    //printf("\n");
    if (e.peca == VALOR_O) printf("(O)");
    else printf("(X)");
    printf("\n(? - Help)\n");
    printf("\n");
}
