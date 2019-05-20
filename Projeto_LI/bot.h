//
// Created by besta80 on 03-05-2019.
//

#ifndef PROJ_BOT_H
#define PROJ_BOT_H

#include "estado.h"
#include "stack.h"

typedef struct bot {
    int valor;
    int linha;
    int coluna;
    ESTADO estado;
    struct bot * jogadas [20];
    struct bot * anterior;
} BOT;

void jogada_bot(ESTADO *e, NODE **stack);
void bot_nivel1(ESTADO *e, NODE **stack);
void bot_nivel2(ESTADO *e, NODE **stack);
void bot_nivel3(ESTADO *e, NODE **stack);
int contapontos_bot(ESTADO e);
void insere_nodo(BOT *anterior, int i, ESTADO e, int l, int c, int profundidade);
void completa_arvore(BOT *anterior, ESTADO e, int profundidade);
void encontra_melhor_jogada(BOT *nodo, int profundidade, int *linha_final, int *coluna_final);
int calcula_valor_nodo(BOT *nodo, int profundidade);
void liberta_memoria_arvore(BOT *decisao, int indice);

#endif //PROJ_BOT_H
