#ifndef pacman_functions_h
#define pacman_functions_h
#define ROWS 7
#define COLS 9
#include "pacman_structs.h"

char getInput();
void gerarFantasmapa(char[ROWS][COLS], char[ROWS][COLS]);
void renderGrid(char[ROWS][COLS], char[ROWS][COLS], Player, Fantasma, int *pontos);
void moverJogador(Player*, int rows, int cols, char[ROWS][COLS], int *pontos);
void moverFantasma(Fantasma*, char[ROWS][COLS]);
int mudarDirecao(Fantasma*, char[ROWS][COLS]);

#endif /* pacman_functions_h */