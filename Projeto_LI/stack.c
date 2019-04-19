//
// Created by besta80 on 19-04-2019.
//

#include <malloc.h>
#include <stdio.h>
#include "stack.h"

//Inserir elementos no inicio
void push(ESTADO e)
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
    temp->next = top;

    //tornar temp o topo da stack
    top = temp;
}


//Remover o elemento no topo da stack
void pop(ESTADO *e)
{
    NODE* temp;

    //verificar se esta vazia
    if (top->next == NULL)
        printf("\nImpossível retroceder mais.\n");
    else {
        //top fica com o valor de temp
        temp = top;

        //o nodo seguinte passa a ser o topo
        top = top->next;

        //libertar memoria do nodo de topo
        free(temp);

        //atualiza o estado do jogo
        *e = top->e;
    }
}


//Limpa a stack após o fim de um jogo
void reinicia_stack()
{
    NODE* temp;

    while(top){
        temp = top->next;
        free(top);
        top = temp;
    }

}