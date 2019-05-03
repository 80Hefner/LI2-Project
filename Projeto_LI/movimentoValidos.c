//
// Created by Utilizador on 20/04/2019.
//

#include "movimentoValidos.h"
#include "jogo.h"
#include "estado.h"
#include "stack.h"
#include <time.h>
#include <stdlib.h>


// Função auxiliar da função seguinte, que é introduzida da mesma maneira!
int verifica_Movimento (VALOR who, int vl, int vc, int l, int c, ESTADO *e) {

    if ((*e).grelha[l][c] == who) return 1;

    if ((vc+c<0) || (vc+c>7)) return 0;

    if ((vl+l<0) || (vl+l>7)) return 0;

    return verifica_Movimento(who,vl,vc,l+vl,c+vl,e);
}


/*
// Função que vê numa direção se movimento é valido
int movimento_valido (VALOR who, int vl, int vc, int l, int c, ESTADO *e) {
    VALOR adversario;
    if (who == VALOR_O) (adversario = VALOR_X);
    else if (who == VALOR_X) (adversario = VALOR_O);

    if ( (vl+l<0) || (vl+l>7) || (vc+c<0) || (vc+c>7) ) return 0;

    if ((*e).grelha[vl+l][vc+c] != adversario) return 0;

    if ( (vl+vl+l<0) || (vl+vl+l>7) || (vc+vc+c<0) || (vc+vc+c>7) ) return 0;

    return verifica_Movimento (who, l, c, l+vl+vl, c+vc+vc, e);
}
 */


// Função que vai returnar um estado com as posições que possam ser sugeridas para movimentos validos
ESTADO calculaMovimentosValidos (VALOR who, ESTADO e) {

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


// Recebe um estado com as possibilidades de jogadas e escolhe, aleatoriamente, uma delas
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