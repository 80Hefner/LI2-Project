#include <stdio.h>
#include "estado.h"


int main()
{
    ESTADO e = {0};


    // estado inicial do tabuleiro. Inicio do jogo!
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;


    //e.grelha[2][2] = VALOR_X;

    escolheModoJogo (&e);
    if (e.modo == '0') printf("Esta a jogar em modo Manual.\n");
    if (e.modo == '1') (printf("Esta a jogar contra o CPU.\n"));

    printf("\n");
    printa(e);
    printf("\n");

    return 0;
}