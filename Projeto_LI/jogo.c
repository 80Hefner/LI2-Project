//
// Created by besta80 on 15-04-2019.
//

#include "jogo.h"
#include "estado.h"
#include "stack.h"
#include "movimentoValidos.h"
#include "ficheiro.h"
#include "bot.h"


/**
 * Função que cria uma variável do tipo ESTADO e prepara-a para um novo jogo
 * @param opcao - Opção recebida no interpertdor que contém o tipo de jogo que quer (BOT ou Vs.Player) e o jogador que pretende ser
 * @param stack - Stack que contém todos os Estados de Jogo
 */
void novo_jogo(char *opcao, NODE **stack)
{
    ESTADO e = {0};

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            e.grelha[i][j] = VAZIA;
        }
    }

    e.grelha[3][4] = VALOR_X;
    e.grelha[4][3] = VALOR_X;
    e.grelha[3][3] = VALOR_O;
    e.grelha[4][4] = VALOR_O;

    e.score_x = conta_pontos(e, 'X');
    e.score_o = conta_pontos(e, 'O');

    if (toupper(opcao[0]) == 'N'){
        if (toupper(opcao[2]) == 'X') e.peca = VALOR_X;
        else e.peca = VALOR_O;

        e.modo = '0';
        jogovsplayer(opcao, e, stack);
    }
    else{
        if (toupper(opcao[2]) == 'X') e.peca_bot = VALOR_X;
        else e.peca_bot = VALOR_O;

        e.peca = VALOR_X;
        e.modo = '1';
        e.nivel = opcao[4];
        jogovsbot(opcao, e, stack);
    }

}



/**
 * Corre um jogo entre 2 jogadores. Quando a função é chamada o jogo não tem necessariamente de estar no seu estado inicial. Isto permite correr um jogo a partir de um ficheiro, com o jogo já a meio.
 * @param opcao - Opção recebida no interpertdor que contem o tipo de comando que quer realizar
 * @param e - Estado atual de Jogo
 * @param stack - Stack que contém todos os Estados de Jogo
 */
void jogovsplayer(char *opcao, ESTADO e, NODE **stack)
{
    push(e, stack);
    printa(e);

    while (toupper(opcao[0]) != 'Q' && !verifica_fim_jogo(e)) {

        if (verifica_turno(e)) {
            printf("\n\nInsira o seu comando: ");
            fgets(opcao, 50, stdin);

            switch (toupper(opcao[0])) {
                case 'J': {
                    jogada(&e, opcao[2], opcao[4], stack);
                    break;
                }
                case 'U': {
                    pop(&e, stack);
                    printa(e);
                    break;
                }
                case 'S' : {
                    printa(calculaMovimentosValidos (e));
                    break;
                }
                case '?': {
                    menuAjuda(2);
                    break;
                }
                case 'E': {
                    grava_jogo(opcao, e);
                    break;
                }
                case 'H': {
                    printa(hint(calculaMovimentosValidos(e)));
                    break;
                }
            }
        }
        else {
            if (e.peca == VALOR_X) e.peca = VALOR_O;
            else e.peca = VALOR_X;

            printf("\nO jogador não tem jogadas possíveis.\n");
            printa(e);
        }
    }

    if (verifica_fim_jogo(e) == 'X') {
        opcao[0] = 'Q';
        printf("\nO jogador X ganhou!!!\n");
    }
    else if (verifica_fim_jogo(e) == 'O') {
        opcao[0] = 'Q';
        printf("\nO jogador O ganhou!!!\n");
    }
    else if (verifica_fim_jogo(e) == 'E') {
        opcao[0] = 'Q';
        printf("\nEmpate!!!\n");
    }
    else printf("Jogo interrompido.\n");

    reinicia_stack(stack);
}



/**
 *  Corre um jogo contra um bot
 * @param opcao - Opção recebida no interpertdor que contem o tipo de comando que quer realizar
 * @param e - Estado atual de Jogo
 * @param stack - Stack que contém todos os Estados de Jogo
 */
void jogovsbot(char *opcao, ESTADO e, NODE ** stack)
{
    push(e, stack);
    printa(e);

    while (toupper(opcao[0]) != 'Q' && !verifica_fim_jogo(e)) {

        if (verifica_turno(e)) {

            if (e.peca == e.peca_bot)
                jogada_bot(&e, stack);
            else{
                printf("\n\nInsira o seu comando: ");
                fgets(opcao, 50, stdin);

                switch (toupper(opcao[0])) {
                    case 'J': {
                        jogada(&e, opcao[2], opcao[4], stack);
                        break;
                    }
                    case 'U': {
                        pop(&e, stack);
                        printa(e);
                        break;
                    }
                    case 'S' : {
                        printa(calculaMovimentosValidos(e));
                        break;
                    }
                    case '?': {
                        menuAjuda(2);
                        break;
                    }
                    case 'E': {
                        grava_jogo(opcao, e);
                        break;
                    }
                    case 'H': {
                        printa(hint(calculaMovimentosValidos(e)));
                        break;
                    }
                }
            }

        }
        else {
            if (e.peca == VALOR_X) e.peca = VALOR_O;
            else e.peca = VALOR_X;

            printf("\nO jogador não tem jogadas possíveis.\n");
            printa(e);
        }
    }

    if (verifica_fim_jogo(e) == 'X') {
        opcao[0] = 'Q';
        printf("\nO jogador X ganhou!!!\n");
    }
    else if (verifica_fim_jogo(e) == 'O') {
        opcao[0] = 'Q';
        printf("\nO jogador O ganhou!!!\n");
    }
    else if (verifica_fim_jogo(e) == 'E') {
        opcao[0] = 'Q';
        printf("\nEmpate!!!\n");
    }
    else printf("Jogo interrompido.\n");

    reinicia_stack(stack);

}


/**
 * Recebe o estado do jogo e a posição onde se quer efetuar a jogada. Testa se a jogada é possível e executa-a
 * @param e - Estado atual de Jogo
 * @param l - Linha
 * @param c - Coluna
 * @param stack - Stack que contém todos os Estados de Jogo
 */
void jogada(ESTADO *e, int l, int c, NODE **stack) {
    l -= 49;  //subtrai-se 48 do código ASCII e 1 pois a posição (1,1) corresponde à posição (0,0) da grelha
    c -= 49;
    int x = 0;  // x=1 se o jogador efetuar uma jogada com sucesso; x=0 se o jogador efetuar uma jogada inválida

    for (int i = 0; i < 8; i++) {
        if (verifica_jogada(i, e, l, c)) {
            executa_jogada(i, e, l, c);
            x = 1;
        }
    }

    if (x) {
        e->grelha[l][c] = e->peca;

        if (e->peca == VALOR_X)
            e->peca = VALOR_O;
        else
            e->peca = VALOR_X;

        e->score_x = conta_pontos(*e, 'X');
        e->score_o = conta_pontos(*e, 'O');
        push(*e, stack);
        printa(*e);
    }
    else printf("\nJogada inválida!");

}



/**
 * Recebe um indicador i (0 se verificar a jogador para a esquerda/cima; 1 para cima; 2 para a direita/cima; 3 para a direita; 4 para a direita/baixo; 5 para baixo; 6 para a esquerda/baixo; 7 para a esquerda)
 * @param i - Indicador
 * @param e - Estado atual de Jogo
 * @param l - Linha em que pertende Jogar
 * @param c - Coluna em que pertende jogar
 * @return 1 se a jogada for possível
 */
int verifica_jogada(int i, ESTADO *e, int l, int c){ // retorna 1 se a jogada for possível
    int x = 0;
    VALOR peca = e->peca;
    VALOR peca_adversario;

    if (peca == VALOR_X) peca_adversario = VALOR_O;
    else peca_adversario = VALOR_X;

    if (e->grelha[l][c] == VAZIA) {
        switch (i) {
            case 0: {
                while (c > 1 && l > 1 && !x) {
                    if (e->grelha[l - 1][c - 1] == peca_adversario && e->grelha[l - 2][c - 2] == peca)
                        x = 1;
                    else if (e->grelha[l - 1][c - 1] == peca_adversario && e->grelha[l - 2][c - 2] == peca_adversario){
                        l--;
                        c--;
                    }
                    else
                        x = 2;
                }
                break;
            }
            case 1: {
                while (l > 1 && !x) {
                    if (e->grelha[l - 1][c] == peca_adversario && e->grelha[l - 2][c] == peca)
                        x = 1;
                    else if (e->grelha[l - 1][c] == peca_adversario && e->grelha[l - 2][c] == peca_adversario)
                        l--;
                    else
                        x = 2;
                }
                break;
            }
            case 2: {
                while (c < 6 && l > 1 && !x) {
                    if (e->grelha[l - 1][c + 1] == peca_adversario && e->grelha[l - 2][c + 2] == peca)
                        x = 1;
                    else if (e->grelha[l - 1][c + 1] == peca_adversario && e->grelha[l - 2][c + 2] == peca_adversario) {
                        l--;
                        c++;
                    }
                    else
                        x = 2;
                }
                break;
            }
            case 3: {
                while (c < 6 && !x) {
                    if (e->grelha[l][c + 1] == peca_adversario && e->grelha[l][c + 2] == peca)
                        x = 1;
                    else if (e->grelha[l][c + 1] == peca_adversario && e->grelha[l][c + 2] == peca_adversario)
                        c++;
                    else
                        x = 2;
                }
                break;
            }
            case 4: {
                while (l < 6 && c < 6 && !x) {
                    if (e->grelha[l + 1][c + 1] == peca_adversario && e->grelha[l + 2][c + 2] == peca)
                        x = 1;
                    else if (e->grelha[l + 1][c + 1] == peca_adversario && e->grelha[l + 2][c + 2] == peca_adversario) {
                        l++;
                        c++;
                    }
                    else
                        x = 2;
                }
                break;
            }
            case 5: {
                while (l < 6 && !x) {
                    if (e->grelha[l + 1][c] == peca_adversario && e->grelha[l + 2][c] == peca)
                        x = 1;
                    else if (e->grelha[l + 1][c] == peca_adversario && e->grelha[l + 2][c] == peca_adversario)
                        l++;
                    else
                        x = 2;
                }
                break;
            }
            case 6: {
                while (l < 6 && c > 1 && !x) {
                    if (e->grelha[l + 1][c - 1] == peca_adversario && e->grelha[l + 2][c - 2] == peca)
                        x = 1;
                    else if (e->grelha[l + 1][c - 1] == peca_adversario && e->grelha[l + 2][c - 2] == peca_adversario) {
                        l++;
                        c--;
                    }
                    else
                        x = 2;
                }
                break;
            }
            case 7: {
                while (c > 1 && !x) {
                    if (e->grelha[l][c - 1] == peca_adversario && e->grelha[l][c - 2] == peca)
                        x = 1;
                    else if (e->grelha[l][c - 1] == peca_adversario && e->grelha[l][c - 2] == peca_adversario)
                        c--;
                    else
                        x = 2;
                }
                break;
            }
        }
    }

    return (x == 1);
}




/**
 *
 * @param i - Indicador da Jogada
 * @param e - Estado Atual do Jogo
 * @param l - Linha em que pretende executar jogada
 * @param c - Coluna em que pretende executar jogada
 */
void executa_jogada(int i, ESTADO *e, int l, int c) {

    VALOR peca = e->peca;

    switch (i) {
        case 0:
            l--; c--;
            break;
        case 1:
            l--;
            break;
        case 2:
            l--; c++;
            break;
        case 3:
            c++;
            break;
        case 4:
            l++; c++;
            break;
        case 5:
            l++;
            break;
        case 6:
            l++; c--;
            break;
        case 7:
            c--;
            break;
    }

    while (e->grelha[l][c] != peca) {

        e->grelha[l][c] = peca;

        switch (i) {
            case 0:
                l--; c--;
                break;
            case 1:
                l--;
                break;
            case 2:
                l--; c++;
                break;
            case 3:
                c++;
                break;
            case 4:
                l++; c++;
                break;
            case 5:
                l++;
                break;
            case 6:
                l++; c--;
                break;
            case 7:
                c--;
                break;
        }

    }
}



/**
 * verifica se jogo já terminou.
 * @param e - Estado atual do Jogo
 * @return 0 se o jogo não acabou, 'X' se o jogador X ganhou e 'O' se o jogador O ganhou.
 */
char verifica_fim_jogo(ESTADO e){ // retorna: 0 se o jogo não acabou; 'X' se o jogador X ganhou; 'O' se o jogador O ganhou, 'E' em caso de empate.
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
        else if (conta_pontos(e, 'X') < conta_pontos(e, 'O')) x = 'O';
        else x = 'E';
    }

    return x;
}


/**
 *
 * @param e - Estado atual do Jogo
 * @return 1 se o jogador pode efetuar jogadas e 0 caso contrário
 */
int verifica_turno(ESTADO e){ // retorna 1 se o jogador pode efetuar jogadas; 0 caso contrário

    int x = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            for (int k = 0; k < 8; k++){
                if (verifica_jogada(k, &e, i, j))
                    x = 1;
            }
        }
    }

    return x;
}



/**
 *
 * @param e - Estado atual do Jogo
 * @param jogador - Jogador
 * @return Número de pontos do Jogador dado
 */
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



/**
 * Função que quando se pressione '?' aparece um menu de ajuda com todas as opções: Quando x é 1 imprime a ajuda do menu principal e quando x é 2 imprime a ajuda do menu de jogo.
 * @param x - Tipo de ajuda que vai fornecer
 */
void menuAjuda (int x) {

    if (x == 1){
        printf("N <peça>: para novo jogo em que o primeiro a jogar é o jogador com <peça>.\n");
        printf("A <peça> <nível>: para novo jogo contra um bot em que o bot joga com <peça> num nível de dificuldade "
               "<nível> (3 níveis possíveis). Neste modo quem joga primeiro é sempre o jogador com a peça X.\n");
        printf("L <ficheiro>: para ler um jogo de <ficheiro>.\n");
        printf("?: para abrir o menu de ajuda.\n");
        printf("Q: para sair.\n");
    }
    else{
        printf("J <L> <C>: para jogar peça atual na posição (L,C).\n");
        printf("U: para desfazer a última jogada(Undo).\n");
        printf("S: para imprimir um ponto ‘.’ nas posições com jogada válida.\n");
        printf("H: para sugestão de jogada. Coloca um ‘?’ no sitio sugerido.\n");
        printf("E <ficheiro>: para escrever o estado do jogo em <ficheiro>.\n");
        printf("?: para abrir o menu de ajuda.\n");
        printf("Q: para sair do jogo.\n");
    }

}