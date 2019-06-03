//
// Created by besta80 on 03-06-2019.
//

#include "campeonato.h"
#include "jogo.h"
#include "ficheiro.h"
#include "bot.h"

void campeonato (char *opcao, NODE **stack) {

    FILE *f;
    char aux[50];
    ESTADO e = {0};
    int a;

    // Atribui o nome do ficheiro à variável aux
    for (a = 2; opcao[a] != '\0'; a++) {
        aux[a - 2] = opcao[a];
    }
    aux[a - 3] = '\0';

    // Abre o ficheiro
    f = fopen(aux, "r");

    // Testa se o ficheiro existe
    if (!f) {
        printf("Novo campeonato.\n");

        f = fopen(aux, "w");

        e.modo = '1';
        e.peca = VALOR_X;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                e.grelha[i][j] = VAZIA;
            }
        }

        e.grelha[3][4] = VALOR_X;
        e.grelha[4][3] = VALOR_X;
        e.grelha[3][3] = VALOR_O;
        e.grelha[4][4] = VALOR_O;

        e.nivel = '3';
        e.score_x = conta_pontos(e, 'X');
        e.score_o = conta_pontos(e, 'O');
        e.peca_bot = VALOR_O;

        fprintf(f, "A");

        if (e.peca == VALOR_X)
            fprintf(f, " X");
        else
            fprintf(f, " O");

        fprintf(f, " %c", e.nivel);
        fprintf(f, "\n");

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                if (e.grelha[i][j] == VALOR_X)
                    fprintf(f, "X ");
                else if (e.grelha[i][j] == VALOR_O)
                    fprintf(f, "O ");
                else
                    fprintf(f, "- ");
            }
            fprintf(f, "\n");
        }

        fclose(f);

        printa(e);
        return;

    } else {

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
        if (e.modo == '1') {
            fseek(f, 1, SEEK_CUR);
            fscanf(f, "%c", aux);

            if (aux[0] == '1')
                e.nivel = '1';
            else if (aux[0] == '2')
                e.nivel = '2';
            else
                e.nivel = '3';
        }

        fseek(f, 1, SEEK_CUR);

        // Atualiza a grelha da variável e, conforme o ficheiro
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

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

        e.score_o = conta_pontos(e, 'O');
        e.score_x = conta_pontos(e, 'X');

        // Fecha o ficheiro
        fclose(f);

        // Atualiza a peça do bot, caso o jogo esteja em modo automático
        if (e.modo == '1') {
            if (e.peca == VALOR_X)
                e.peca_bot = VALOR_O;
            else
                e.peca_bot = VALOR_X;
        }

        printf("Tabuleiro recebido:\n");
        printa(e);

        jogada_bot(&e, stack);

        while (verifica_turno(e) == 0) {

            if (verifica_fim_jogo(e))
                break;

            if (e.peca == VALOR_X) e.peca = VALOR_O;
            else e.peca = VALOR_X;

            jogada_bot(&e, stack);

        }

        if (verifica_fim_jogo(e) != 0) {

            for (a = 2; opcao[a] != '\0'; a++) {
                aux[a - 2] = opcao[a];
            }
            aux[a - 3] = '\0';


            for (a = 0; aux[a] != '.'; a++);
            a++;

            aux[a++] = 'g';

            if (verifica_fim_jogo(e) == 'X')
                aux[a++] = 'X';
            else if (verifica_fim_jogo(e) == 'O')
                aux[a++] = 'O';
            else
                aux[a++] = '-';

            aux[a] = '\0';

            printf("Fim do jogo:\n");
            printf("O: %d\n", conta_pontos(e, 'O'));
            printf("X: %d\n", conta_pontos(e, 'X'));

            if (verifica_fim_jogo(e) == 'O')
                printf("Vitória: O\n");
            else if (verifica_fim_jogo(e) == 'X')
                printf("Vitória: X\n");
            else
                printf("Empate.\n");

        }
        else {
            printf("Tabuleiro enviado:\n");
            printa(e);

            for (a = 2; opcao[a] != '\0'; a++) {
                aux[a - 2] = opcao[a];
            }
            aux[a - 3] = '\0';

        }


        fopen(aux, "w");

        fprintf(f, "A");

        if (e.peca == VALOR_X)
            fprintf(f, " X");
        else
            fprintf(f, " O");

        fprintf(f, " %c", e.nivel);

        fprintf(f, "\n");

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

        fclose(f);
    }

}
