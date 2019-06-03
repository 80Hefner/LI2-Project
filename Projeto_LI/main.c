#include "estado.h"
#include "jogo.h"
#include "stack.h"
#include "movimentoValidos.h"
#include "ficheiro.h"
#include "campeonato.h"

/**
 * Função principal que faz com que o jogo possa aconteçer! Permite-nos escolher as opções do Menú Inicial para começar um novo jogo, etc.
 * @return
 */
int main() {
    //ESTADO e = {0};
    char opcao[50];
    static NODE* stack = NULL;


    printf("Insira o seu comando: ");
    fgets(opcao, 50, stdin);

    while (toupper(opcao[0]) != 'Q') {

        switch (toupper(opcao[0])) {
            case 'N': {
                novo_jogo(opcao, &stack);
                break;
            }
            case 'L': {
                ler_jogo(opcao, &stack);
                break;
            }
            case 'A': {
                novo_jogo(opcao, &stack);
                break;
            }
            case '?': {
                menuAjuda(1);
                break;
            }
            case 'C': {
                campeonato (opcao, &stack);
                break;
            }
        }

        printf("\nInsira o seu comando: ");
        fgets(opcao, 50, stdin);
    }

    return 0;
}