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
            bot_nivel2(e, stack);
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


void bot_nivel2(ESTADO *e, NODE **stack)
{
    BOT decisao = {0};
    int l, c;

    decisao.estado = *e;
    decisao.anterior = NULL;
    decisao.valor = -10000;

    completa_arvore(&decisao, *e, 1, 1);

    encontra_melhor_jogada(&decisao, &l, &c);

    printf("\nO bot jogou na posição (%d,%d)\n", l+1, c+1);

    jogada(e, l+49, c+49, stack);

    for (int i = 0; decisao.jogadas[i] != NULL; i++)
        liberta_memoria_arvore(decisao.jogadas[i], i);

}


void bot_nivel3(ESTADO *e, NODE **stack)
{
    BOT decisao = {0};
    int l, c;

    decisao.estado = *e;
    decisao.anterior = NULL;
    decisao.valor = -10000;

    completa_arvore(&decisao, *e, 6, 1);

    encontra_melhor_jogada(&decisao, &l, &c);

    printf("\nO bot jogou na posição (%d,%d)\n", l+1, c+1);

    jogada(e, l+49, c+49, stack);

    for (int i = 0; decisao.jogadas[i] != NULL; i++)
        liberta_memoria_arvore(decisao.jogadas[i], i);

}



// Cria uma árvore com as jogadas possíveis, de profundidade: fundo
void completa_arvore(BOT *anterior, ESTADO e, int fundo, int depth)
{
    int i = 0;

    for (int l = 0; l < 8; l++){
        for (int c = 0; c < 8; c++){
            for (int k = 0, y = 1; k < 8 && y; k++){

                if (verifica_jogada(k, &e, l, c)){
                    insere_nodo(anterior, i, e, l, c, depth);
                    i++;
                    y = 0;
                }
            }
        }
    }

    if (depth < fundo) {

        for (int k = 0; anterior->jogadas[k] != NULL; k++) {
            completa_arvore(anterior->jogadas[k], anterior->jogadas[k]->estado, fundo, depth + 1);
        }
    }
}



// Insere um único nodo, de acordo com a sua profundidade
void insere_nodo(BOT *anterior, int i, ESTADO e, int l, int c, int depth)
{
    BOT *nodo = (BOT *) malloc(sizeof(BOT));

    for (int k = 0; k < 40; nodo->jogadas[k] = NULL, k++);

    if (depth % 2 == 0)
        nodo->valor = -10000;
    else
        nodo->valor = 10000;

    nodo->linha = l;
    nodo->coluna = c;
    nodo->anterior = anterior;
    anterior->jogadas[i] = nodo;

    for (int k = 0; k < 8; k++){
        if (verifica_jogada(k, &e, l, c))
            executa_jogada(k, &e, l, c);
    }

    if (anterior->estado.peca == VALOR_O)
        e.peca = VALOR_X;
    else
        e.peca = VALOR_O;

    nodo->estado = e;
}


// Percorre a árvore com as jogadas e escolhe a mais adequada
void encontra_melhor_jogada(BOT *nodo, int *linha_final, int *coluna_final)
{
    int depth = 0;

    for (int i = 0; nodo->jogadas[i] != NULL; i++){

        calcula_valor_nodo(nodo->jogadas[i], depth + 1);

        if (nodo->jogadas[i]->valor > nodo->valor){
            nodo->valor = nodo->jogadas[i]->valor;
            *linha_final = nodo->jogadas[i]->linha;
            *coluna_final = nodo->jogadas[i]->coluna;
        }
    }
}


// Função auxiliar da encontra_melhor_jogada, que percorre o resto da árvore
void calcula_valor_nodo(BOT *nodo, int depth)
{

    if (nodo->jogadas[0] != NULL){

        for (int i = 0; nodo->jogadas[i] != NULL; i++){

            calcula_valor_nodo(nodo->jogadas[i], depth + 1);

            if (depth % 2 == 0) {
                if (nodo->jogadas[i]->valor > nodo->valor) nodo->valor = nodo->jogadas[i]->valor;
            }
            else {
                if (nodo->jogadas[i]->valor < nodo->valor) nodo->valor = nodo->jogadas[i]->valor;
            }
        }

    }
    else {
        nodo->valor = contapontos_bot(nodo->estado);
    }

}


// Conta os pontos do jogador de acordo com uma pontução diferente
int contapontos_bot(ESTADO e)
{
    int x = 0;
    VALOR peca, peca_adversario;

    peca_adversario = e.peca;

    if (e.peca == VALOR_O)
        peca = VALOR_X;
    else
        peca = VALOR_O;

    /*
    VALOR pontuacao[8][8] = {{10, -5,  3,  3,  3,  3, -5, 10},
                             {-5, -5, -3, -3, -3, -3, -5, -5},
                             { 3, -3,  1,  1,  1,  1, -3,  3},
                             { 3, -3,  1,  1,  1,  1, -3,  3},
                             { 3, -3,  1,  1,  1,  1, -3,  3},
                             { 3, -3,  1,  1,  1,  1, -3,  3},
                             {-5, -5, -3, -3, -3, -3, -5, -5},
                             {10, -5,  3,  3,  3,  3, -5, 10}};
*/

    VALOR pontuacao[8][8] = {{25, -5, 14, 10, 10, 14, -5, 25},
                             {-5, -7, -4, -3, -3, -4, -7, -5},
                             {14, -4,  3,  2,  2,  3, -4, 14},
                             {10, -3,  2,  1,  1,  2, -3, 10},
                             {10, -3,  2,  1,  1,  2, -3, 10},
                             {14, -4,  3,  2,  2,  3, -4, 14},
                             {-5, -7, -4, -3, -3, -4, -7, -5},
                             {25, -5, 14, 10, 10, 14, -5, 25}};

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e.grelha[i][j] == peca) {
                x += pontuacao[i][j];
                x++;
            }
            else if (e.grelha[i][j] == peca_adversario){
                x--;
            }
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