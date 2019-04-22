//
// Created by besta80 on 22-04-2019.
//

#include "ficheiro.h"
#include "estado.h"
#include "movimentoValidos.h"
#include <stdio.h>


void grava_jogo (char *opcao, ESTADO e)
{
    FILE *f;
    char aux [50];
    ESTADO e_aux;
    char grelha_jogo[8][8];

    for (int i = 2; opcao[i] != '\0' ; i++){
        aux[i-2] = opcao[i];
    }

    f = fopen(aux, "w");

    //Neste momento temos o ficheiro aberto na variável f, vamos começar a escrever nele

    if (e.modo == '0')
        fprintf(f, "M ");
    else
        fprintf(f, "A ");

    if (e.peca == VALOR_X)
        fprintf(f, "X\n");
    else
        fprintf(f, "O\n");

    //A primeira linha está impressa, falta imprimir o estado do jogo

    e_aux = calculaMovimentosValidos(e.peca, e);

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if (e_aux.grelha[i][j] == VALOR_X)
                fprintf(f, "X ");
            else if (e_aux.grelha[i][j] == VALOR_O)
                fprintf(f, "O ");
            else if (e_aux.grelha[i][j] == VAZIA)
                fprintf(f, "- ");
            else
                fprintf(f, ". ");
        }
        fprintf(f, "\n");
    }

    //O ficheiro está impresso com o estado do jogo, falta fechar o fichiero

    fclose(f);

    printf("\nJogo gravado com sucesso!\n");

}
