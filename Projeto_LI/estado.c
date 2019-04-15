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
            }
            printf("%c ", c);

        }
        printf("\n");
    }

    printf("\n");
    if (e.peca == VALOR_O) printf("O jogador atual é: O");
    else printf("O jogador atual é: X");
    printf("\n");
}

void jogada(ESTADO *e, int l, int c){
    l -= 49;  //subtrai-se 48 do código ASCII e 1 pois a posição (1,1) corresponde à posição (0,0) da grelha
    c -= 49;
    int x = 0;

    for (int i = 0; i < 8; i++){
        if (verifica_jogada(i, e, l, c)) {
            switch (i) {
                case 0: executa_jogada(i, e, l-1, c-1);
                    break;
                case 1: executa_jogada(i, e, l-1, c);
                    break;
                case 2: executa_jogada(i, e, l-1, c+1);
                    break;
                case 3: executa_jogada(i, e, l, c+1);
                    break;
                case 4: executa_jogada(i, e, l+1, c+1);
                    break;
                case 5: executa_jogada(i, e, l+1, c);
                    break;
                case 6: executa_jogada(i, e, l+1, c-1);
                    break;
                case 7: executa_jogada(i, e, l, c-1);
                    break;
            }
            x = 1;
        }
    }

    if (x) {
        (*e).grelha[l][c] = (*e).peca;
        if ((*e).peca == VALOR_X) (*e).peca = VALOR_O;
        else (*e).peca = VALOR_X;
    }
}

int verifica_jogada(int i, ESTADO *e, int l, int c){
    int x = 0;
    VALOR peca = (*e).peca;
    VALOR peca_adversario;

    if (peca == VALOR_X) peca_adversario = VALOR_O;
    else peca_adversario = VALOR_X;

    if ((*e).grelha[l][c] != VAZIA) return 0;

    switch (i){
        case 0: {
            if ((*e).grelha[l-1][c-1] == peca_adversario && (*e).grelha[l-2][c-2] == peca) x = 1;
            else if ((*e).grelha[l-1][c-1] == peca_adversario && (*e).grelha[l-2][c-2] == peca_adversario) x = verifica_jogada(i, e, l-1, c-1);
            break;
        }
        case 1: {
            if ((*e).grelha[l-1][c] == peca_adversario && (*e).grelha[l-2][c] == peca) x = 1;
            else if ((*e).grelha[l-1][c] == peca_adversario && (*e).grelha[l-2][c] == peca_adversario) x = verifica_jogada(i, e, l-1, c);
            break;
        }
        case 2: {
            if ((*e).grelha[l-1][c+1] == peca_adversario && (*e).grelha[l-2][c+2] == peca) x = 1;
            else if ((*e).grelha[l-1][c+1] == peca_adversario && (*e).grelha[l-2][c+2] == peca_adversario) x = verifica_jogada(i, e, l-1, c+1);
            break;
        }
        case 3: {
            if ((*e).grelha[l][c+1] == peca_adversario && (*e).grelha[l][c+2] == peca) x = 1;
            else if ((*e).grelha[l][c+1] == peca_adversario && (*e).grelha[l][c+2] == peca_adversario) x = verifica_jogada(i, e, l, c+1);
            break;
        }
        case 4: {
            if ((*e).grelha[l+1][c+1] == peca_adversario && (*e).grelha[l+2][c+2] == peca) x = 1;
            else if ((*e).grelha[l+1][c+1] == peca_adversario && (*e).grelha[l+2][c+2] == peca_adversario) x = verifica_jogada(i, e, l+1, c+1);
            break;
        }
        case 5: {
            if ((*e).grelha[l+1][c] == peca_adversario && (*e).grelha[l+2][c] == peca) x = 1;
            else if ((*e).grelha[l+1][c] == peca_adversario && (*e).grelha[l+2][c] == peca_adversario) x = verifica_jogada(i, e, l+1, c);
            break;
        }
        case 6: {
            if ((*e).grelha[l+1][c-1] == peca_adversario && (*e).grelha[l+2][c-2] == peca) x = 1;
            else if ((*e).grelha[l+1][c-1] == peca_adversario && (*e).grelha[l+2][c-2] == peca_adversario) x = verifica_jogada(i, e, l+1, c-1);
            break;
        }
        case 7: {
            if ((*e).grelha[l][c-1] == peca_adversario && (*e).grelha[l][c-2] == peca) x = 1;
            else if ((*e).grelha[l][c-1] == peca_adversario && (*e).grelha[l][c-2] == peca_adversario) x = verifica_jogada(i, e, l, c-1);
            break;
        }
    }
    return x;
}

void executa_jogada(int i, ESTADO *e, int l, int c) {

    VALOR peca = (*e).peca;

    if ((*e).grelha[l][c] != peca) {

        (*e).grelha[l][c] = peca;

        switch (i) {
            case 0: executa_jogada(i, e, l-1, c-1);
                break;
            case 1: executa_jogada(i, e, l-1, c);
                break;
            case 2: executa_jogada(i, e, l-1, c+1);
                break;
            case 3: executa_jogada(i, e, l, c+1);
                break;
            case 4: executa_jogada(i, e, l+1, c+1);
                break;
            case 5: executa_jogada(i, e, l+1, c);
                break;
            case 6: executa_jogada(i, e, l+1, c-1);
                break;
            case 7: executa_jogada(i, e, l, c-1);
                break;
        }
    }
}

void novo_jogo(ESTADO *e, char peca){

    if (peca == 'X') (*e).peca = VALOR_X;
    else (*e).peca = VALOR_O;
}