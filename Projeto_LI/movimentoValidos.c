//
// Created by Utilizador on 20/04/2019.
//

#include "movimentoValidos.h"
#include "jogo.h"
#include "estado.h"
#include "stack.h"
#include <time.h>
#include <stdlib.h>



/**
 *
 * @param e - Estado de jogo atual
 * @return Estado de jogo com todos os movimentos váldos possíveis de realizar por parte do jogador em jogo
 */
ESTADO calculaMovimentosValidos (ESTADO e) {

    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (e.grelha[l][c] == SUG) (e.grelha[l][c] = VAZIA);
        }
    }


    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if (e.grelha [l][c] == VAZIA) {
                int no = verifica_jogada(0, &e, l, c);
                int nn = verifica_jogada(1, &e, l, c);
                int ne = verifica_jogada(2, &e, l, c);

                int oo = verifica_jogada(7, &e, l, c);
                int ee = verifica_jogada(3, &e, l, c);

                int so = verifica_jogada(4, &e, l, c);
                int ss = verifica_jogada(5, &e, l, c);
                int se = verifica_jogada(6, &e, l, c);

                if (no || nn || ne || oo || ee || so || ss || se) {
                    e.grelha [l][c] = SUG;
                }
            }
        }
    }
    return e;
}



/**
 *
 * @param e - Estado de jogo atual
 * @return Estado com as que vai escolher uma jogada possível aleatoriamente e a vai sugerir ao jogador
 */
ESTADO hint (ESTADO e)
{
    int x = 0;
    time_t t;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e.grelha[i][j] == SUG) x++;
        }
    }

    srand((unsigned) time(&t));

    x = rand() % x;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e.grelha[i][j] == SUG && x){
                e.grelha[i][j] = VAZIA;
                x--;
            }
            else if (e.grelha[i][j] == SUG){
                e.grelha[i][j] = HINT;
                x = -1;
            }
        }
    }

    return e;
}