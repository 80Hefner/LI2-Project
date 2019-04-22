//
// Created by besta80 on 15-04-2019.
//

#include "jogo.h"
#include "estado.h"
#include "stack.h"
#include "movimentoValidos.h"
#include "ficheiro.h"

//Função que cria uma variável do tipo ESTADO e prepara-a para um novo jogo
void novo_jogo(char *opcao)
{
    ESTADO e = {0};

    if (toupper(opcao[2]) == 'X') e.peca = VALOR_X;
    else e.peca = VALOR_O;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            e.grelha[i][j] = VAZIA;
        }
    }

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;
    e.modo = '0';

    jogovsplayer(opcao, e);
}

// Corre um jogo entre 2 jogadores. Quando a função é chamada o jogo não tem necessariamente de estar no seu estado inicial.
// Isto permite correr um jogo a partir de um ficheiro, com o jogo já a meio
void jogovsplayer(char *opcao, ESTADO e){

    push(e);
    printa(e);

    while (toupper(opcao[0]) != 'Q' && !verifica_fim_jogo(e)) {

        if (verifica_turno(e)) {
            printf("\nInsira o seu comando: ");
            fgets(opcao, 50, stdin);

            switch (toupper(opcao[0])) {
                case 'J': {
                    jogada(&e, opcao[2], opcao[4]);
                    break;
                }
                case 'U': {
                    pop(&e);
                    printa(e);
                    break;
                }
                case 'S' : {
                    printa(calculaMovimentosValidos ((e.peca) , e));
                    break;
                }
                case '?': {
                    menuAjuda();
                    break;
                }
                case 'E': {
                    grava_jogo(opcao, e);
                }
            }
        }
        else {
            if (e.peca == VALOR_X) e.peca = VALOR_O;
            else e.peca = VALOR_X;

            printf("O jogador não tem jogadas possíveis.\n");
            printa(e);
        }
    }

    if (verifica_fim_jogo(e) == 'X') {
        opcao[0] = 'Q';
        printf("\nO jogador X ganhou!!!");
    }
    else if (verifica_fim_jogo(e) == 'O') {
        opcao[0] = 'Q';
        printf("\nO jogador O ganhou!!!");
    }
    else printf("Jogo interrompido.\n");

    reinicia_stack();
}


// Recebe o estado do jogo e a posição onde se quer efetuar a jogada. Testa se a jogada é possível e executa-a
void jogada(ESTADO *e, int l, int c) {
    l -= 49;  //subtrai-se 48 do código ASCII e 1 pois a posição (1,1) corresponde à posição (0,0) da grelha
    c -= 49;
    int x = 0;  // x=1 se o jogador efetuar uma jogada com sucesso; x=0 se o jogador efetuar uma jogada inválida

    if ((*e).grelha[l][c] != VALOR_X && (*e).grelha[l][c] != VALOR_O) {

        for (int i = 0; i < 8; i++) {
            if (verifica_jogada(i, e, l, c)) {
                switch (i) {
                    case 0:
                        executa_jogada(i, e, l - 1, c - 1);
                        break;
                    case 1:
                        executa_jogada(i, e, l - 1, c);
                        break;
                    case 2:
                        executa_jogada(i, e, l - 1, c + 1);
                        break;
                    case 3:
                        executa_jogada(i, e, l, c + 1);
                        break;
                    case 4:
                        executa_jogada(i, e, l + 1, c + 1);
                        break;
                    case 5:
                        executa_jogada(i, e, l + 1, c);
                        break;
                    case 6:
                        executa_jogada(i, e, l + 1, c - 1);
                        break;
                    case 7:
                        executa_jogada(i, e, l, c - 1);
                        break;
                }
                x = 1;
            }
        }
    }


    if (x) {
        (*e).grelha[l][c] = (*e).peca;
        if ((*e).peca == VALOR_X) (*e).peca = VALOR_O;
        else (*e).peca = VALOR_X;
        push(*e);
        printa(*e);
    }
    else printf("Jogada inválida!\n");

}

// Recebe um indicador i (0 se verificar a jogador para a esquerda/cima; 1 para cima; 2 para a direita/cima;
// 3 para a direita; 4 para a direita/baixo; 5 para baixo; 6 para a esquerda/baixo; 7 para a esquerda), o estado do jogo
// e a posição para a qual quer verificar a jogada
int verifica_jogada(int i, ESTADO *e, int l, int c){ // retorna 1 se a jogada for possível
    int x = 0;
    VALOR peca = (*e).peca;
    VALOR peca_adversario;

    if (peca == VALOR_X) peca_adversario = VALOR_O;
    else peca_adversario = VALOR_X;

    switch (i){
        case 0: {
            if (c > 1 && l > 1) {
                if ((*e).grelha[l - 1][c - 1] == peca_adversario && (*e).grelha[l - 2][c - 2] == peca) x = 1;
                else if ((*e).grelha[l - 1][c - 1] == peca_adversario && (*e).grelha[l - 2][c - 2] == peca_adversario)
                    x = verifica_jogada(i, e, l - 1, c - 1);
            }
            break;
        }
        case 1: {
            if (l > 1) {
                if ((*e).grelha[l - 1][c] == peca_adversario && (*e).grelha[l - 2][c] == peca) x = 1;
                else if ((*e).grelha[l - 1][c] == peca_adversario && (*e).grelha[l - 2][c] == peca_adversario)
                    x = verifica_jogada(i, e, l - 1, c);
            }
            break;
        }
        case 2: {
            if (c < 6 && l > 1) {
                if ((*e).grelha[l - 1][c + 1] == peca_adversario && (*e).grelha[l - 2][c + 2] == peca) x = 1;
                else if ((*e).grelha[l - 1][c + 1] == peca_adversario && (*e).grelha[l - 2][c + 2] == peca_adversario)
                    x = verifica_jogada(i, e, l - 1, c + 1);
            }
            break;
        }
        case 3: {
            if (c < 6) {
                if ((*e).grelha[l][c + 1] == peca_adversario && (*e).grelha[l][c + 2] == peca) x = 1;
                else if ((*e).grelha[l][c + 1] == peca_adversario && (*e).grelha[l][c + 2] == peca_adversario)
                    x = verifica_jogada(i, e, l, c + 1);
            }
            break;
        }
        case 4: {
            if (l < 6 && c < 6) {
                if ((*e).grelha[l + 1][c + 1] == peca_adversario && (*e).grelha[l + 2][c + 2] == peca) x = 1;
                else if ((*e).grelha[l + 1][c + 1] == peca_adversario && (*e).grelha[l + 2][c + 2] == peca_adversario)
                    x = verifica_jogada(i, e, l + 1, c + 1);
            }
            break;
        }
        case 5: {
            if (l < 6) {
                if ((*e).grelha[l + 1][c] == peca_adversario && (*e).grelha[l + 2][c] == peca) x = 1;
                else if ((*e).grelha[l + 1][c] == peca_adversario && (*e).grelha[l + 2][c] == peca_adversario)
                    x = verifica_jogada(i, e, l + 1, c);
            }
            break;
        }
        case 6: {
            if (l < 6 && c > 1) {
                if ((*e).grelha[l + 1][c - 1] == peca_adversario && (*e).grelha[l + 2][c - 2] == peca) x = 1;
                else if ((*e).grelha[l + 1][c - 1] == peca_adversario && (*e).grelha[l + 2][c - 2] == peca_adversario)
                    x = verifica_jogada(i, e, l + 1, c - 1);
            }
            break;
        }
        case 7: {
            if (c > 1) {
                if ((*e).grelha[l][c - 1] == peca_adversario && (*e).grelha[l][c - 2] == peca) x = 1;
                else if ((*e).grelha[l][c - 1] == peca_adversario && (*e).grelha[l][c - 2] == peca_adversario)
                    x = verifica_jogada(i, e, l, c - 1);
            }
            break;
        }
    }
    return x;
}

// Recebe o indicador da jogada, o estado do jogo e uma posição e executa uma jogada
void executa_jogada(int i, ESTADO *e, int l, int c) {

    VALOR peca = (*e).peca;

    if ((*e).grelha[l][c] != peca) {

        (*e).grelha[l][c] = peca;

        switch (i) {
            case 0: executa_jogada(i, e, l-1, c-1);
                break;
            case 1: executa_jogada(i, e, l-1, c);
                break;
            case 2: executa_jogada(i, e, l-1, c+1);
                break;
            case 3: executa_jogada(i, e, l, c+1);
                break;
            case 4: executa_jogada(i, e, l+1, c+1);
                break;
            case 5: executa_jogada(i, e, l+1, c);
                break;
            case 6: executa_jogada(i, e, l+1, c-1);
                break;
            case 7: executa_jogada(i, e, l, c-1);
                break;
        }
    }
}


// Recebe o estado do jogo e verifica se este terminou
char verifica_fim_jogo(ESTADO e){ // retorna: 0 se o jogo não acabou; 'X' se o jogador X ganhou; 'O' se o jogador O ganhou.
    char x = 1;
    ESTADO e2 = e;

    if (e.peca == VALOR_X) e2.peca = VALOR_O;
    else e2.peca = VALOR_X;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (e.grelha[i][j] == VAZIA) x = 0;
        }
    }

    if (!verifica_turno(e) && !verifica_turno(e2)){
        if (conta_pontos(e, 'X') > conta_pontos(e, 'O')) x = 'X';
        else x = 'O';
    }

    return x;
}

// Recebe o estado do jogo e verifica se o próximo jogador tem jogadas disponíveis
int verifica_turno(ESTADO e){ // retorna 1 se o jogador pode efetuar jogadas; 0 caso contrário

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++){
                if (verifica_jogada(k, &e, i, j)) return 1;
            }
        }
    }

    return 0;
}

// Recebe o estado do jogo e o char correspondente a um jogador e conta o seu número de pontos
int conta_pontos (ESTADO e, char jogador){
    int conta = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            switch (jogador){
                case 'X':
                    if (e.grelha[i][j] == VALOR_X) conta++;
                    break;
                case 'O':
                    if (e.grelha[i][j] == VALOR_O) conta++;
                    break;
            }
        }
    }
    return conta;
}

// Função que quando se pressione '?' aparece um menu de ajuda com todas as opções;
void menuAjuda () {
    printf("- Presse n ou N para comecar um novo Jogo!\n");
    printf("- Presse j ou J para realizar uma jogada inserindo depois a linha e a coluna!\n");
    printf("- Presse q ou Q para sair do Jogo!\n");
    printf("- Presse ? a qualquer momento para ajuda!\n");
}