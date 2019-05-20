//
// Created by besta80 on 03-05-2019.
//

#ifndef PROJ_BOT_H
#define PROJ_BOT_H

#include "estado.h"
#include "stack.h"

typedef struct bot {
    int valor;   ///< Valor do nodo atual
    int linha;   ///< Linha da jogada escolhida
    int coluna;   ///< Coluna da jogada escolhida
    ESTADO estado;   ///< Estado do jogo neste nodo
    struct bot * jogadas [40];   ///< Array com as jogadas possíveis, a partir deste estado
    struct bot * anterior;   ///< Apontador para o nodo anterior
} BOT;

/**
 * Função responsável por escolher qual dos bots chamar.
 * @param e - Apontador para o estado atual do jogo
 * @param stack - Apontador para a stack
 */
void jogada_bot(ESTADO *e, NODE **stack);

/**
 * Função responsável por executar o bot de nível 1.
 * @param e - Apontador para o estado atual do jogo
 * @param stack - Apontador para a stack
 */
void bot_nivel1(ESTADO *e, NODE **stack);

/**
 * Função responsável por executar o bot de nível 1.
 * @param e - Apontador para o estado atual do jogo
 * @param stack - Apontador para a stack
 */
void bot_nivel2(ESTADO *e, NODE **stack);

/**
 * Função responsável por executar o bot de nível 1.
 * @param e - Apontador para o estado atual do jogo
 * @param stack - Apontador para a stack
 */
void bot_nivel3(ESTADO *e, NODE **stack);

/**
 * Função que conta os pontos do jogador, de acordo com uma pontuação diferente
 * @param e - Estado do jogo no nodo em análise
 */
int contapontos_bot(ESTADO e);

/**
 * Função que insere um único nodo, de acordo com a sua profundidade
 * @param anterior - Apontador para o nodo anterior
 * @param i - Posição do array do nodo anterior onde será inserido o novo nodo
 * @param e - Estado atual do jogo
 * @param l - Linha da jogada a inserir
 * @param c - Coluna da jogada a inserir
 * @param depth - Profundidade atual na árvore
 */
void insere_nodo(BOT *anterior, int i, ESTADO e, int l, int c, int fundo);

/**
 * Função que cria uma árvore com as jogadas possíveis, de profundidade: fundo
 * @param anterior - Apontador para o nodo anterior
 * @param e - Estado atual do jogo
 * @param fundo - Profundidade total da árvore
 * @param depth - Profundidade atual na árvore
 */
void completa_arvore(BOT *anterior, ESTADO e, int fundo, int depth);

/**
 * Função que percorre a árvore com as jogadas e escolhe a mais adequada
 * @param nodo - Apontador para o nodo principal da árvore
 * @param linha_final - Apontador para a linha da jogada escolhida
 * @param coluna_final - Apontador para a coluna da jogada escolhida
 */
void encontra_melhor_jogada(BOT *nodo, int *linha_final, int *coluna_final);

/**
 * Função auxiliar da encontra_melhor_jogada, que percorre o resto da árvore
 * @param nodo - Apontador para o nodo anterior da árvore
 * @param depth - Profundidade atual na árvore
 */
void calcula_valor_nodo(BOT *nodo, int depth);

/**
 * Função que percorre a árvore criada e liberta os nodos da memória
 * @param nodo - Apontador para o nodo atual da árvore
 * @param indice - Indice do nodo atual, no array do nodo anterior
 */
void liberta_memoria_arvore(BOT *decisao, int indice);

#endif //PROJ_BOT_H
