//
// Created by besta80 on 03-05-2019.
//

#include "bot.h"
#include "jogo.h"

// Recebe o estado do jogo e decide uma jogada autonomamente
void jogada_bot(ESTADO *e, NODE **stack)
{
    int x = 1;

    for (int i = 0; i < 8 && x; i++){
        for (int j = 0; j < 8 && x; j++){
            for (int k = 0; k < 8 && x; k++){
                if (verifica_jogada(k, e, i, j)){
                    jogada(e, i+49, j+49, stack);
                    x = 0;
                }
            }
        }
    }


}