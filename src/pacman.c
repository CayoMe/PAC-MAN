#include <stdio.h>
#include <conio.h> // Biblioteca para receber as setas como entrada do usuário
#include <stdlib.h>


char mapa[5][5] = {{'#', '#', '#', '#', '#'}, // Infelizmente por enquanto o tamanho dos mapas vai ter que ser declarado em toda variável
                   {'#', '.', '.', '.', '#'}, // É BEM complicado mexer com matrizes em C, e eu tô meio atolado...
                   {'#', '.', '.', '.', '#'},
                   {'#', '.', '.', '.', '#'},
                   {'#', '#', '#', '#', '#'}};

// STRUCTS ------------------------------

typedef struct // Talvez seria interessante fazer uma estrutura "Entidade" que possa ser o Pacman e o fantasma?
{
    int posX, posY;
} Player;

typedef struct
{
    int posX, posY;
    int Xvel, Yvel;
} Fantasma;

// PROTÓTIPOS ---------------------------

char getInput();
void renderGrid(int rows, int cols, char[rows][cols], Player);
void makeMove(Player*, int rows, int cols, char mapa[rows][cols]);
// void makeMove();
// void checkWin();


char *main(void) {
    Player p1;
    p1.posX = 1; p1.posY = 1; // Colocando o player na coordenada (1, 1)

    renderGrid(5, 5, mapa, p1);

    // Loop principal do jogo
    while (1)
    {
        makeMove(&p1, 5, 5, mapa);
        renderGrid(5, 5, mapa, p1);
    }

    return "🥴";
}

// FUNÇÕES ----------------------------

// Retorna um char representando a seta que o jogador apertou no formato 'u' (up), 'd' (down), 'l' (left), 'r' (right)
// Não retorna nada caso o usuário entre com qualquer tecla que não seja uma setinha
char getInput()
{
    char output;

    while (!output)
    {
        int input = getch(); // É uma função estranha que recebe uma tecla sem escrever na tela
    
        if (input == 224)
        {
            input = getch(); // Ela tem que ser chamada duas vezes pra alguns tipos de teclas, como as setinhas

            switch (input) // TODO: criar mais teclas de controle, como [r]einiciar, [s]air, etc.
            {
            case 72:
                output = 'u';
                break;
            
            case 80:
                output = 'd';
                break;

            case 75:
                output = 'l';
                break;

            case 77:
            output = 'r';
                break;

            default:
                break;
            }
        }
        else if (input == 113)
        {
            exit(0); // Fecha o programa
        }
    }

    return output;
}

void renderGrid(int rows, int cols, char map[rows][cols], Player player)
{
    system("cls");

    // Colocando o Pacman na sua coordenada
    map[player.posY][player.posX] = 'C';

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

// TODO: contabilizar pontos quando o pacman se move para uma casa onde havia uma bolinha
void makeMove(Player *pacman, int rows, int cols, char mapa[rows][cols])
{
    char proxMov;
    int pacX = pacman->posX;
    int pacY = pacman->posY;

    while (1)
    {
        int deltaX = 0, deltaY = 0; // Incrementos da coordenada do jogador
        proxMov = getInput();

        // Incrementa os deltas dependendo da entrada do jogador
        if (proxMov == 'r')
            deltaX++;
        else if (proxMov == 'l')
            deltaX--;
        else if (proxMov == 'u')
            deltaY--;
        else if (proxMov == 'd')
            deltaY++;
        else // Talvez não precise dessa parte
        {
            printf("movimento inválido!\n");
            break;
        }

        // Verificando se o movimento é válido
        if (mapa[pacY + deltaY][pacX + deltaX] == '#')
        {
            printf("vc acertaria uma parede\n");
        }
        else
        {
            // Esvaziando o local atual do jogador e movendo- o para o próximo
            mapa[pacY][pacX] = ' ';
            mapa[pacY + deltaY][pacX + deltaX] = 'C'; // Tecnicamente quem escreve o C é a renderGrid, mas eu tô com medo de tirar 😅

            // Atualizando as coordenadas do jogador para as novas
            pacman->posX += deltaX;
            pacman->posY += deltaY;
            break;
        }
    }
}

void checkwin()
{
    // TODO
}