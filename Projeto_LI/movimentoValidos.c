//
// Created by Utilizador on 20/04/2019.
//

#include "movimentoValidos.h"
#include "jogo.h"
#include "estado.h"
#include "stack.h"



// Função auxiliar da função seguinte, que é introduzida da mesma maneira!
int verifica_Movimento (VALOR who, int vl, int vc, int l, int c, ESTADO *e) {

    if ((*e).grelha[l][c] == who) return 1;

    if ((vc+c<0) || (vc+c>7)) return 0;

    if ((vl+l<0) || (vl+l>7)) return 0;

    return verifica_Movimento(who,vl,vc,l+vl,c+vl,e);
}

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

// Função que vai returnar um estado com as posições que possam ser sugeridas para movimentos validos
ESTADO calculaMovimentosValidos (VALOR who, ESTADO *e) {

    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if ((*e).grelha[l][c] == SUG) ((*e).grelha[l][c] = VAZIA);
        }
    }


    for (int l = 0; l < 8; l++) {
        for (int c = 0; c < 8; c++) {
            if ((*e).grelha [l][c] == VAZIA) {
                int no = movimento_valido (who,-1,-1,l,c,e);
                int nn = movimento_valido (who,-1, 0,l,c,e);
                int ne = movimento_valido (who,-1, 1,l,c,e);

                int oo = movimento_valido (who, 0,-1,l,c,e);
                int ee = movimento_valido (who, 0, 1,l,c,e);

                int so = movimento_valido (who, 1,-1,l,c,e);
                int ss = movimento_valido (who, 1, 0,l,c,e);
                int se = movimento_valido (who, 1, 1,l,c,e);

                if (no || nn || ne || oo || ee || so || ss || se) {
                    (*e).grelha [l][c] = SUG;
                }
            }
        }
    }
    return *e;
}
