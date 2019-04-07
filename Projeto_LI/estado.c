//
// Created by pja on 28/02/2019.
//
#include <stdio.h>
#include "estado.h"


// exemplo de uma função para imprimir o estado (Tabuleiro)
void printa(ESTADO e) {

    char c = ' ';


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
            }
            printf("%c ", c);

        }
        printf("\n");
    }

}


void escolheModoJogo (ESTADO *e) {

    printf ("Escolha o modo de jogo que quer:\n  0 - Contra outro jogador (manual)\n  1 - Contra o computador!\n\n");

    scanf("%c", &(*e).modo);


    while ((*e).modo!='0' && (*e).modo!='1') {

        printf("Introduza um modo de jogo válido!:\n");

        scanf("%c", &(*e).modo);}

}