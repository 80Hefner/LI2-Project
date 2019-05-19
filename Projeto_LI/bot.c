//
// Created by besta80 on 03-05-2019.
//

#include "bot.h"
#include "jogo.h"
#include "movimentoValidos.h"

// Recebe o estado do jogo e decide uma jogada autonomamente
void jogada_bot(ESTADO *e, NODE **stack)
{
    if (e -> nivel == '1'){

        ESTADO e_aux;

        e_aux = hint(calculaMovimentosValidos(*e));

        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if (e_aux.grelha[i][j] == HINT)
                    jogada(e, i+49, j+49, stack);  //adiciona 49 pois o função jogada começa por retirar 49 ao valor recebido
            }
        }

    }


}