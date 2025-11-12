#include "pacman_functions.h"

char mapa[ROWS][COLS] = {{'#', '#', '#', '#', '#', '#', '#', '#', '#'}, // Infelizmente por enquanto o tamanho dos mapas vai ter que ser declarado em toda variável
                         {'#', '.', '.', '#', '.', '.', '.', '.', '#'}, // É BEM complicado mexer com matrizes em C, e eu tô meio atolado...
                         {'#', '.', '.', '#', '.', '.', '.', '.', '#'},
                         {'#', '.', '.', '.', '.', '#', '.', '.', '#'},
                         {'#', '.', '.', '.', '.', '#', '.', '.', '#'},
                         {'#', '.', '.', '.', '.', '#', '.', '.', '#'},
                         {'#', '#', '#', '#', '#', '#', '#', '#', '#'}};
char fantasmapa[ROWS][COLS]; // Mapa dos fantasmas



char* main(void) {
    int p = 0;
    int *pontos = &p; // pontuação 

    // Inicializando player e fantasmas
    gerarFantasmapa(mapa, fantasmapa);

    Player p1 = {1, 1};
    Fantasma f1 = {'F', 1, 3, 1, 0};

    renderGrid(mapa, fantasmapa, p1, f1, pontos);

    // Loop principal do jogo
    while (1)
    {
        moverJogador(&p1, ROWS, COLS, mapa, pontos);
        moverFantasma(&f1, fantasmapa); // Mudará para moverFantasmas() assim que completarmos a função
        renderGrid(mapa, fantasmapa, p1, f1, pontos);
    }

    return "🥴";
}
