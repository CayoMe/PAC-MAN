#ifndef pacman_functions_h
#define pacman_functions_h
#define ROWS 23
#define COLS 22
#define pacman_inicial_x 9
#define pacman_inicial_y 15
#define fantasma_inicial_x 9
#define fantasma_inicial_y 9

#include "pacman_structs.h"

char getInput();
void telaInicial();
void gerarFantasmapa(char[ROWS][COLS], char[ROWS][COLS]);
void renderGrid(char[ROWS][COLS], char[ROWS][COLS], Player*, Fantasma[], int, int *pontos);
char moverJogador(Player*, Fantasma[], int rows, int cols, char[ROWS][COLS], char[ROWS][COLS], int *pontos);
void moverFantasma(Fantasma*, char[ROWS][COLS], Player);
int mudarDirecao(Fantasma*, char[ROWS][COLS], int, int);
void saveGame(Player p, Fantasma f[]);
void reiniciarJogo(Player *p, Fantasma f[], char mapa[ROWS][COLS]);
void carregarMapa(char mapa[ROWS][COLS]);

#endif /* pacman_functions_h */