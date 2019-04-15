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

    if ((*e).grelha[l][c] == VAZIA) {

        for (int i = 0; i < 8; i++) {
            if (verifica_jogada(i, e, l, c)) {
                switch (i) {
                    case 0:
                        executa_jogada(i, e, l - 1, c - 1);
                        break;
                    case 1:
                        executa_jogada(i, e, l - 1, c);
                        break;
                    case 2:
                        executa_jogada(i, e, l - 1, c + 1);
                        break;
                    case 3:
                        executa_jogada(i, e, l, c + 1);
                        break;
                    case 4:
                        executa_jogada(i, e, l + 1, c + 1);
                        break;
                    case 5:
                        executa_jogada(i, e, l + 1, c);
                        break;
                    case 6:
                        executa_jogada(i, e, l + 1, c - 1);
                        break;
                    case 7:
                        executa_jogada(i, e, l, c - 1);
                        break;
                }
                x = 1;
            }
        }
    }

    if (x) {
        (*e).grelha[l][c] = (*e).peca;
        if ((*e).peca == VALOR_X) (*e).peca = VALOR_O;
        else (*e).peca = VALOR_X;
        printa(*e);
    }
    else printf("Jogada inválida!\n");
}

int verifica_jogada(int i, ESTADO *e, int l, int c){ // retorna 1 se a jogada for possível
    int x = 0;
    VALOR peca = (*e).peca;
    VALOR peca_adversario;

    if (peca == VALOR_X) peca_adversario = VALOR_O;
    else peca_adversario = VALOR_X;

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

    printa(*e);
}

int verifica_fim_jogo(ESTADO e){ // retorna: 0 se o jogo não acabou; 1 se o jogador X ganhou; 2 se o jogador O ganhou.
    int x = 1;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e.grelha[i][j] == VAZIA) x = 0;
        }
    }

    if (!verifica_turno(e, 1) && !verifica_turno(e, 2)) x = 1;

    if (x == 1){
        if (conta_pontos(e, 1) > conta_pontos(e, 2)) x = 1;
        else x = 2;
    }

    return x;
}

int verifica_turno(ESTADO e, int jogador){ // retorna 1 se o jogador  pode efetuar jogadas

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++){
                if (verifica_jogada(k, &e, i, j)) return 1;
            }
        }
    }

    return 0;
}



int conta_pontos (ESTADO e, int jogador){
    int conta = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            switch (jogador){
                case 1:
                    if (e.grelha[i][j] == VALOR_X) conta++;
                    break;
                case 2:
                    if (e.grelha[i][j] == VALOR_O) conta++;
                    break;
            }
        }
    }
    return conta;
}