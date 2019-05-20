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
    BOT decisao = {0};

    decisao.estado = *e;
    decisao.anterior = NULL;

    completa_arvore(&decisao, *e, 2);

    int l, c;

    encontra_melhor_jogada(&decisao, 3, &l, &c);

    printf("\nO bot jogou na posição (%d,%d)\n", l+1, c+1);

    jogada(e, l+49, c+49, stack);

    for (int i = 0; decisao.jogadas[i] != NULL; i++)
        liberta_memoria_arvore(decisao.jogadas[i], i);


}

void completa_arvore(BOT *anterior, ESTADO e, int profundidade)
{
    int i = 0;

    for (int l = 0; l < 8; l++){
        for (int c = 0; c < 8; c++){
            for (int k = 0, y = 1; k < 8 && y; k++){

                if (verifica_jogada(k, &e, l, c)){
                    insere_nodo(anterior, i, e, l, c, profundidade);
                    i++;
                    y = 0;
                }
            }
        }
    }

    if (profundidade) {

        for (int k = 0; anterior->jogadas[k] != NULL; k++) {
            completa_arvore(anterior->jogadas[k], anterior->jogadas[k]->estado, profundidade - 1);
        }
    }
}

void insere_nodo(BOT *anterior, int i, ESTADO e, int l, int c, int profundidade)
{
    BOT *nodo = (BOT *) malloc(sizeof(BOT));

    for (int k = 0; k < 20; nodo->jogadas[k] = NULL, k++);

    if (profundidade == 2)
        nodo->valor = 10000;
    else
        nodo->valor = -10000;

    nodo->linha = l;
    nodo->coluna = c;
    nodo->anterior = anterior;
    anterior->jogadas[i] = nodo;

    for (int k = 0; k < 8; k++){
        if (verifica_jogada(k, &e, l, c))
            executa_jogada(k, &e, l, c);
    }

    if (profundidade == 1)
        e.peca = VALOR_X;
    else
        e.peca = VALOR_O;

    nodo->estado = e;
}


void encontra_melhor_jogada(BOT *nodo, int profundidade, int *linha_final, int *coluna_final)
{

    int x;

    for (int i = 0; nodo->jogadas[i] != NULL; i++){

        x = calcula_valor_nodo(nodo->jogadas[i], profundidade-1);

        if (x > nodo->valor){
            nodo->valor = x;
            *linha_final = nodo->jogadas[i]->linha;
            *coluna_final = nodo->jogadas[i]->coluna;
        }
    }
}


int calcula_valor_nodo(BOT *nodo, int profundidade)
{

    int x;

    if (nodo->jogadas[0] != NULL){

        for (int i = 0; nodo->jogadas[i] != NULL; i++){
            x = calcula_valor_nodo(nodo->jogadas[i], profundidade-1);

            if (profundidade == 2) {
                if (x < nodo->valor) nodo->valor = x;
            }
            else if (profundidade == 1) {
                if (x > nodo->valor) nodo->valor = x;
            }
        }
        x = nodo->valor;
    }
    else {
        x = contapontos_bot(nodo->estado);
    }

    return x;
}


int contapontos_bot(ESTADO e)
{
    int x = 0;
    VALOR peca = e.peca;

    /*
    Sistema de pontuação usado

    10 -5  3  3  3  3 -5 10
    -5 -5 -3 -3 -3 -3 -5 -5
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
     3 -3  1  1  1  1 -3  3
    -5 -5 -3 -3 -3 -3 -5 -5
    10 -5  3  3  3  3 -5 10
    */

    if (e.grelha[0][0] == peca) x += 10;
    if (e.grelha[0][7] == peca) x += 10;
    if (e.grelha[7][0] == peca) x += 10;
    if (e.grelha[7][7] == peca) x += 10;


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


void liberta_memoria_arvore(BOT *nodo, int indice)
{
    if (nodo != NULL) {

        for (int i = 0; nodo->jogadas[i] != NULL; i++) {
            liberta_memoria_arvore(nodo->jogadas[i], i);
        }

        nodo->anterior->jogadas[indice] = NULL;
        free(nodo);

    }
}