#include "estado.h"
#include "jogo.h"


int main() {
    ESTADO e = {0};
    char opcao[50];


    printf("Insira o seu comando: ");
    fgets(opcao, 50, stdin);

    while (toupper(opcao[0]) != 'Q') {

        switch (toupper(opcao[0])) {
            case 'N': {
                jogovsplayer(&e, opcao);
                break;
            }
        }

        printf("\nInsira o seu comando: ");
        fgets(opcao, 50, stdin);
    }

    return 0;
}