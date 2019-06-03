//
// Created by besta80 on 22-04-2019.
//

#include "ficheiro.h"
#include "estado.h"
#include "movimentoValidos.h"
#include "jogo.h"
#include <stdio.h>

/**
 *
 * @param opcao - opção recebida no interpertdor que contém o nome do ficheiro que pretende gravar.
 * @param e - Estado de jogo atual.
 */
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
        fprintf(f, "M");
    else
        fprintf(f, "A");

    if (e.peca == VALOR_X)
        fprintf(f, " X");
    else
        fprintf(f, " O");

    if (e.modo == '1')
        fprintf(f, " %c", e.nivel);

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


/**
 *
 * @param opcao - opção recebida no interpertdor que contém o nome do ficheiro que pretende carregar.
 * @param stack - Stack que contém todos os Estados de Jogo
 */
void ler_jogo (char *opcao, NODE **stack)
{
    FILE *f;
    char aux [50];
    ESTADO e = {0};
    int a;

    // Atribui o nome do ficheiro à variável aux
    for (a = 2; opcao[a] != '\0' ; a++){
        aux[a-2] = opcao[a];
    }
    aux[a-3] = '\0';

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

        if (aux[0] == 'X')
            e.peca = VALOR_X;
        else
            e.peca = VALOR_O;

        // Atualiza o nível do bot, caso esteja em modo automático
        if (e.modo == '1'){
            fseek(f, 1, SEEK_CUR);
            fscanf(f, "%c", aux);

            if (aux[0] == '1')
                e.nivel = '1';
            else if (aux[0] == '2')
                e.nivel = '2';
            else
                e.nivel = '3';
        }

        // Verifica se tem que saltar um espaço
        fscanf(f, "%c", aux);

        if (aux[0] == ' ') {
            fseek(f, 1, SEEK_CUR);
        }


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

            fseek(f, -1, SEEK_CUR);

            // Verifica se tem que saltar um espaço
            fscanf(f, "%c", aux);

            if (aux[0] == ' ') {
                fseek(f, 1, SEEK_CUR);
            }
        }

        e.score_o = conta_pontos(e, 'O');
        e.score_x = conta_pontos(e, 'X');

        // Fecha o ficheiro
        fclose(f);

        // Atualiza a peça do bot, caso o jogo esteja em modo automático
        if (e.modo == '1'){
            if (e.peca == VALOR_X)
                e.peca_bot = VALOR_O;
            else
                e.peca_bot = VALOR_X;
        }

        // Começa um jogo, a partir da variável e
        if (e.modo == '0')
            jogovsplayer(opcao, e, stack);
        else
            jogovsbot(opcao, e, stack);

    }

}


