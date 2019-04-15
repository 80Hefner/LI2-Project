#include "estado.h"


int main() {
    ESTADO e = {0};
    char opcao[50];

    // estado inicial do tabuleiro. Inicio do jogo!
    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;

    fgets(opcao, 50, stdin);

    while (toupper(opcao[0]) != 'Q') {

        switch (toupper(opcao[0])) {
            case 'N': {
                novo_jogo(&e, toupper(opcao[2]));
                printa(e);
                fgets(opcao, 50, stdin);
                break;
            }
            case 'J' : {
                jogada(&e, opcao[2], opcao[4]);
                printa(e);
                fgets(opcao, 50, stdin);
                break;
            }
        }

    }

    return 0;
}