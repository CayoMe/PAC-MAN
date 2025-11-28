#include "pacman_functions.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>// Para aceitar o TEXT
#include <mmsystem.h>//Biblioteca para poder colocar o Som do Jogo

const char MAPA_ORIGINAL[ROWS][COLS] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','o','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','o','#'},
    {'#','.','#','#','.','#','#','#','#','.','#','#','.','#','#','#','#','.','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','.','#','.','#','#','#','#','#','#','#','#','.','#','.','#','#','.','#'},
    {'#','.','.','.','.','#','.','.','.','.','#','#','.','.','.','.','#','.','.','.','.','#'},
    {'#','#','#','#','.','#','#','#','#',' ','#','#',' ','#','#','#','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ','#','#','#','_','_','#','#','#',' ','#','.','#','#','#','#'},
    {'#','.','.','.','.',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','.','.','.','.','#'},
    {'#','#','#','#','.','#',' ','#','#','#','#','#','#','#','#',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ','#','#','#','#','#','#','#','#','.','#','.','#','#','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.',' ','.','.','.','.','#'},
    {'#','.','#','#','.','#','#','#','#','.','#','#','.','#','#','#','#','.','#','#','.','#'},
    {'#','o','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','.','o','#'},
    {'#','#','.','#','.','#','.','#','#','#','#','#','#','#','#','.','#','.','#','.','#','#'},
    {'#','.','.','.','.','#','.','.','.','.','#','#','.','.','.','.','#','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

char mapa[ROWS][COLS] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','o','.','.','.','.','.','.','.','.','#','#','.','.','.','.','.','.','.','.','o','#'},
    {'#','.','#','#','.','#','#','#','#','.','#','#','.','#','#','#','#','.','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','.','#','#','.','#','.','#','#','#','#','#','#','#','#','.','#','.','#','#','.','#'},
    {'#','.','.','.','.','#','.','.','.','.','#','#','.','.','.','.','#','.','.','.','.','#'},
    {'#','#','#','#','.','#','#','#','#',' ','#','#',' ','#','#','#','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ','#','#','#','_','_','#','#','#',' ','#','.','#','#','#','#'},
    {'#','.','.','.','.',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','.','.','.','.','#'},
    {'#','#','#','#','.','#',' ','#','#','#','#','#','#','#','#',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','.','#','#','#','#'},
    {'#','#','#','#','.','#',' ','#','#','#','#','#','#','#','#','.','#','.','#','#','#','#'},
    {'#','.','.','.','.','.','.','.','.','.','#','#','.','.','.','.',' ','.','.','.','.','#'},
    {'#','.','#','#','.','#','#','#','#','.','#','#','.','#','#','#','#','.','#','#','.','#'},
    {'#','o','.','#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#','.','o','#'},
    {'#','#','.','#','.','#','.','#','#','#','#','#','#','#','#','.','#','.','#','.','#','#'},
    {'#','.','.','.','.','#','.','.','.','.','#','#','.','.','.','.','#','.','.','.','.','#'},
    {'#','.','#','#','#','#','#','#','#','.','#','#','.','#','#','#','#','#','#','#','.','#'},
    {'#','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};
char fantasmapa[ROWS][COLS]; // Mapa dos fantasmas



char* main(void) {

    //Musiquinha do Games
    // Colocando o som do jogo em 50% do volume para ficar show
    DWORD volume = 0x80008000; 
    // Como precisa colocar para os dois lados do ouvido o esquerdo e direito
    // fica 0x8000-8000 = 50% de volume nos dois. conforme a documentação

    //Coloca para a saida de audio ser a sua atual do computador, a padrão
    waveOutSetVolume(0, volume);

    //Toca a Musiquinha do Games
    PlaySound(TEXT("..\\assets\\som.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    //Os parametros que usei foram o SND_FILENAME para dizer que estamos passando um arquivo
    // O SND_ASYNC para ele tocar sem travar o programa
    // E o SND_LOOP para ele ficar tocando em loop até mandarmos parar

    char mapa[ROWS][COLS];
    carregarMapa(mapa);
    telaInicial();
    int p = 0;
    int *pontos = &p; // pontuação 

    // Inicializando player e fantasmas
    gerarFantasmapa(mapa, fantasmapa);

    // Inicializando player e fantasmas
    Player p1 = {pacman_inicial_x, pacman_inicial_y, 'd'}; // Usando a posição do #define para não dar erros no carregamento do savefile

    Fantasma fantasmas[4] = {
        {'F', 0, 0, 0, 0}, // Fantasma 1 (vermelho)
        {'P', 0, 0, 0, 0}, // Fantasma 2 (rosa)
        {'I', 0, 0, 0, 0}, // Fantasma 3 (azul)
        {'O', 0, 0, 0, 0}  // Fantasma 4 (laranja)
    };

    // Abrindo save file
    FILE *save = fopen("../assets/savefile.txt", "r");
    if (save == NULL)
    {
        printf("no save file!\n");
    }

    char buffer[20];
    int esseFan = 0; // Contador para acessar cada fantasma do array

    while(fgets(buffer, sizeof(buffer), save) != NULL)
    {
        // Se a linha for a primeira, a linha do Pacman...
        if (buffer[0] == 'p')
        {
            // Altera x e y do Pacman
            sscanf(buffer, "p,%i,%i", &p1.xPos, &p1.yPos);
        }
        else
        {
            // Altera as coordenadas e velocidade do fantasma
            sscanf(buffer, "%d,%d,%d,%d",
                &fantasmas[esseFan].xPos,
                &fantasmas[esseFan].yPos,
                &fantasmas[esseFan].xVel,
                &fantasmas[esseFan].yVel
            );

            // Vai para o próximo fantasma
            esseFan++;
        }
    }

    fclose(save);
    
    int num_fantasmas = 4;

    renderGrid(mapa, fantasmapa, &p1, fantasmas, num_fantasmas, pontos);

    // Loop principal do jogo
    while (1)
    {
        char input = moverJogador(&p1, fantasmas, ROWS, COLS, mapa, fantasmapa, pontos);

        // Loop para mover TODOS os fantasmas
        for (int i = 0; i < num_fantasmas; i++) {
            moverFantasma(&fantasmas[i], fantasmapa, p1);
        }

        // Renderiza tudo para criar o frame
        renderGrid(mapa, fantasmapa, &p1, fantasmas, num_fantasmas, pontos);
    }

    return "🥴";
}
