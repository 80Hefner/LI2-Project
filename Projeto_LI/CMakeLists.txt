cmake_minimum_required(VERSION 3.13)
project(proj C)

set(CMAKE_C_STANDARD 99)

add_executable(proj main.c estado.h estado.c jogo.c stack.c movimentoValidos.c ficheiro.c bot.c campeonato.c campeonato.h)