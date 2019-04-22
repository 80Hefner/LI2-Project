#include "estado.h"
#include "jogo.h"
#include "stack.h"
#include "movimentoValidos.h"
#include "ficheiro.h"


int main() {
    //ESTADO e = {0};
    char opcao[50];


    printf("Insira o seu comando: ");
    fgets(opcao, 50, stdin);

    while (toupper(opcao[0]) != 'Q') {

        switch (toupper(opcao[0])) {
            case 'N': {
                novo_jogo(opcao);
                break;
            }
            case 'L': {
                ler_jogo(opcao);
            }
        }

        printf("\nInsira o seu comando: ");
        fgets(opcao, 50, stdin);
    }

    return 0;
}