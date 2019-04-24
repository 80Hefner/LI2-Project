//
// Created by besta80 on 19-04-2019.
//

#ifndef PROJ_STACK_H
#define PROJ_STACK_H

#include "estado.h"

//Declarar o nodo da lista-ligada
typedef struct Node {
    ESTADO e;
    struct Node* next;
}NODE;


void push(ESTADO e, NODE **stack);
void pop(ESTADO *e, NODE **stack);
void reinicia_stack(NODE **stack);

#endif //PROJ_STACK_H
