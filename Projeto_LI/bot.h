//
// Created by besta80 on 03-05-2019.
//

#ifndef PROJ_BOT_H
#define PROJ_BOT_H

#include "estado.h"
#include "stack.h"

int contapontos_bot(ESTADO e, int linha, int coluna);
void bot_nivel1(ESTADO *e, NODE **stack);
void bot_nivel3(ESTADO *e, NODE **stack);
void jogada_bot(ESTADO *e, NODE **stack);

#endif //PROJ_BOT_H
