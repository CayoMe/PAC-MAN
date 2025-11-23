#ifndef pacman_functions_h
#define pacman_functions_h
#define ROWS 23
#define COLS 22
#include "pacman_structs.h"

char getInput();
void telaInicial();
void gerarFantasmapa(char[ROWS][COLS], char[ROWS][COLS]);
void renderGrid(char[ROWS][COLS], char[ROWS][COLS], Player, Fantasma[], int, int *pontos);
void moverJogador(Player*, int rows, int cols, char[ROWS][COLS], char[ROWS][COLS], int *pontos);
void moverFantasma(Fantasma*, char[ROWS][COLS], Player);
int mudarDirecao(Fantasma*, char[ROWS][COLS], int, int);

#endif /* pacman_functions_h */