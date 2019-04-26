//
// Created by besta80 on 22-04-2019.
//

#include "ficheiro.h"
#include "estado.h"
#include "movimentoValidos.h"
#include "jogo.h"
#include <stdio.h>


void grava_jogo (char *opcao, ESTADO e)
{
    FILE *f;
    char aux [50];
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
        fprintf(f, "X ");
    else
        fprintf(f, "O ");

    if (e.modo == '1')
        fprintf(f, "%c ", e.nivel);

    fprintf(f, "\n");

    //A primeira linha está impressa, falta imprimir a grelha do jogo


    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){

            if (e.grelha[i][j] == VALOR_X)
                fprintf(f, "X ");
            else if (e.grelha[i][j] == VALOR_O)
                fprintf(f, "O ");
            else
                fprintf(f, "- ");
        }
        fprintf(f, "\n");
    }

    //O ficheiro está impresso com o estado do jogo, falta fechar o fichiero

    fclose(f);

    printf("\nJogo gravado com sucesso!\n");

}

void ler_jogo (char *opcao, NODE **stack)
{
    FILE *f;
    char aux [50];
    ESTADO e = {0};

    // Atribui o nome do ficheiro à variável aux
    for (int i = 2; opcao[i] != '\0' ; i++){
        aux[i-2] = opcao[i];
    }

    // Abre o ficheiro
    f = fopen(aux, "r");

    // Testa se o ficheiro existe
    if (!f)
        printf("O ficheiro não existe!");
    else {

        // Atualiza o modo de jogo da variável e, conforme o ficheiro
        fscanf(f, "%c", aux);
        fseek(f, 1, SEEK_CUR);

        if (aux[0] == 'M')
            e.modo = '0';
        else
            e.modo = '1';

        // Atualiza a peca do próximo jogador a jogar da variável e, conforme o ficheiro
        fscanf(f, "%c", aux);
        fseek(f, 1, SEEK_CUR);

        if (aux[0] == 'X')
            e.peca = VALOR_X;
        else
            e.peca = VALOR_O;

        // Atualiza o nível do bot, caso esteja em modo automático
        if (e.modo == '1'){
            fscanf(f, "%c", aux);
            fseek(f, 1, SEEK_CUR);

            if (aux[0] == '1')
                e.nivel = '1';
            else if (aux[0] == '2')
                e.nivel = '2';
            else
                e.nivel = '3';
        }

        fseek(f, 1, SEEK_CUR);

        // Atualiza a grelha da variável e, conforme o ficheiro
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){

                fscanf(f, "%c", aux);
                fseek(f, 1, SEEK_CUR);

                if (aux[0] == 'X')
                    e.grelha[i][j] = VALOR_X;
                else if (aux[0] == 'O')
                    e.grelha[i][j] = VALOR_O;
                else
                    e.grelha[i][j] = VAZIA;
            }
            fseek(f, 1, SEEK_CUR);
        }

        // Fecha o ficheiro
        fclose(f);

        // Começa um jogo, a partir da variável e
        jogovsplayer(opcao, e, stack);

    }



}

