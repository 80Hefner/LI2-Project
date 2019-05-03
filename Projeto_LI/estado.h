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
typedef enum {VAZIA, VALOR_X, VALOR_O, SUG, HINT} VALOR;

/**
Estrutura que armazena o estado do jogo
*/
typedef struct estado {
    VALOR peca; // peça do jogador que vai jogar!
    VALOR grelha[8][8];
    char modo; // modo em que se está a jogar! 0-> manual, 1-> contra computador
    char nivel; // nivel de dificuldade do bot
    int score_x; // score do jogador X
    int score_o; // score do jogador O
    VALOR peca_bot; // peça do bot
} ESTADO;

void printa(ESTADO);


#endif //PROJ_ESTADO_H