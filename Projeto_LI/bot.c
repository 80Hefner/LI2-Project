//
// Created by besta80 on 03-05-2019.
//

#include "bot.h"
#include "jogo.h"
#include "movimentoValidos.h"
#include <stdlib.h>
#include <time.h>

// Recebe o estado do jogo e decide uma jogada autonomamente
void jogada_bot(ESTADO *e, NODE **stack)
{

    switch (e->nivel){
        case '1': {
            bot_nivel1(e, stack);
            break;
        }
        case '2': {
            int x;
            time_t t;
            srand((unsigned) time(&t));

            x = rand();

            if (x % 2)
                bot_nivel1(e, stack);
            else
                bot_nivel3(e, stack);
            break;
        }
        case '3':{
            bot_nivel3(e, stack);
            break;
        }
    }

}



void bot_nivel1(ESTADO *e, NODE **stack)
{
    ESTADO e_aux;

    e_aux = hint(calculaMovimentosValidos(*e));

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e_aux.grelha[i][j] == HINT){
                printf("\nO bot jogou na posição (%d,%d)", i+1, j+1);
                jogada(e, i+49, j+49, stack);  // adiciona 49 pois o função jogada começa por retirar 49 ao valor recebido
            }
        }
    }

}



void bot_nivel3(ESTADO *e, NODE **stack)
{
    int maximo = 0, linha, coluna, x;
    int y = 1;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8 && y; k++){

                if (verifica_jogada(k, e, i, j)){
                    x = contapontos_bot(*e, i, j);
                    if (x > maximo){
                        linha = i; coluna = j; maximo = x;
                    }
                    y = 0;
                }
            }
            y = 1;
        }
    }
    printf("\nO bot jogou na posição (%d,%d)", linha+1, coluna+1);

    jogada(e, linha+49, coluna+49, stack);  // adiciona 49 pois o função jogada começa por retirar 49 ao valor recebido

}



int contapontos_bot(ESTADO e, int linha, int coluna)
{
    int x = 0;
    VALOR peca = e.peca_bot;

    for (int i = 0; i < 8; i++) {
        if (verifica_jogada(i, &e, linha, coluna))
            executa_jogada(i, &e, linha, coluna);

    }

    /*
    Sistema de pontuação usado

     5 -5  3  3  3  3 -5  5
    -5 -5 -3 -3 -3 -3 -5 -5
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
    -5 -5 -3 -3 -3 -3 -5 -5
     5 -5  3  3  3  3 -5  5
    */

    if (e.grelha[0][0] == peca) x += 5;
    if (e.grelha[0][7] == peca) x += 5;
    if (e.grelha[7][0] == peca) x += 5;
    if (e.grelha[7][7] == peca) x += 5;


    for (int i = 2; i < 6; i++){
        if (e.grelha[0][i] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[7][i] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[i][0] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[i][7] == peca) x += 3;
    }


    if (e.grelha[0][1] == peca) x -= 5;
    if (e.grelha[0][6] == peca) x -= 5;
    if (e.grelha[1][0] == peca) x -= 5;
    if (e.grelha[1][1] == peca) x -= 5;
    if (e.grelha[1][6] == peca) x -= 5;
    if (e.grelha[1][7] == peca) x -= 5;
    if (e.grelha[6][0] == peca) x -= 5;
    if (e.grelha[6][1] == peca) x -= 5;
    if (e.grelha[6][6] == peca) x -= 5;
    if (e.grelha[6][7] == peca) x -= 5;
    if (e.grelha[7][1] == peca) x -= 5;
    if (e.grelha[7][6] == peca) x -= 5;


    for (int i = 2; i < 6; i++){
        if (e.grelha[1][i] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[6][i] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[i][1] == peca) x += 3;
    }

    for (int i = 2; i < 6; i++){
        if (e.grelha[i][6] == peca) x += 3;
    }


    for (int i = 2; i < 6; i++){
        for (int j = 2; j < 6; j++){
            if (e.grelha[i][j] == peca) x++;
        }
    }

    return x;

}