//
// Created by besta80 on 15-04-2019.
//

#include "estado.h"

#ifndef PROJ_JOGO_H
#define PROJ_JOGO_H


void novo_jogo(char *opcao);
void jogovsplayer(char *opcao, ESTADO e);
void jogada(ESTADO *e, int linha, int coluna);
int verifica_jogada(int i, ESTADO *e, int l, int c);
void executa_jogada(int i, ESTADO *e, int l, int c);
char verifica_fim_jogo(ESTADO e);
int verifica_turno(ESTADO e);
int conta_pontos(ESTADO e, char jogador);
void menuAjuda ();



#endif //PROJ_JOGO_H
