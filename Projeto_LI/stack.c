//
// Created by besta80 on 19-04-2019.
//

#include <malloc.h>
#include <stdio.h>
#include "stack.h"


/**
 * Insere Estado no início da Stack
 * @param e - Estado de Jogo Atual
 * @param stack - Stack que contém todos os Estados de Jogo anteriores
 */
void push(ESTADO e, NODE **stack)
{
    //criar um novo nodo temp e alocar memoria
    NODE* temp;
    temp = (NODE*) malloc(sizeof(NODE));

    //verificar se a stack esta cheia“out-of-memory”
    if (!temp) {
        printf("\nStack sobrelotada\n");
    }

    //introduzir os dados no respetivo campo em temp
    temp->e = e;

    //direcionar o apontador top para temp
    temp->next = *stack;

    //tornar temp o topo da stack
    *stack = temp;
}



/**
 *
 * @param e - Estado de Jogo Atual
 * @param stack - Stack que contém todos os Estados de Jogo anteriores
 */
void pop(ESTADO *e, NODE **stack)
{
    NODE* temp;

    //verificar se esta vazia
    if ((*stack)->next == NULL)
        printf("\nImpossível retroceder mais.\n");
    else {
        //top fica com o valor de temp
        temp = (*stack);

        //o nodo seguinte passa a ser o topo
        (*stack) = (*stack)->next;

        //libertar memoria do nodo de topo
        free(temp);

        //atualiza o estado do jogo
        *e = (*stack)->e;
    }
}


/**
 * Vai limpar a Stack após o fim de um jogo.
 * @param stack - Stack que contém todos os Estados de Jogo anteriores
 */
void reinicia_stack(NODE **stack)
{
    NODE* temp;

    while(*stack){
        temp = (*stack)->next;
        free(*stack);
        *stack = temp;
    }

}