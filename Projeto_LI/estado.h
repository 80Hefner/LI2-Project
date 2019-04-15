//
// Created by pja on 27/02/2019.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"

#ifndef PROJ_ESTADO_H
#define PROJ_ESTADO_H



/**
estado.h
Definição do estado i.e. tabuleiro. Representação matricial do tabuleiro.
*/


// definição de valores possiveis no tabuleiro
typedef enum {VAZIA, VALOR_X, VALOR_O} VALOR;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
} ESTADO;


void printa(ESTADO);
void jogada(ESTADO *e, int linha, int coluna);
int verifica_jogada(int i, ESTADO *e, int l, int c);
void executa_jogada(int i, ESTADO *e, int l, int c);
void novo_jogo(ESTADO *e, char peca);
int verifica_fim_jogo(ESTADO e);
int verifica_turno(ESTADO e, int jogador);
int conta_pontos(ESTADO e, int jogador);


#endif //PROJ_ESTADO_H