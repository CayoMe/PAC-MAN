#include <stdio.h>
#include <conio.h> // Biblioteca para receber as setas como entrada do usuário
#include <stdlib.h>

#define ROWS 6
#define COLS 6

char mapa[ROWS][COLS] = {{'#', '#', '#', '#', '#', '#'}, // Infelizmente por enquanto o tamanho dos mapas vai ter que ser declarado em toda variável
                         {'#', '.', '.', '.', '.', '#'}, // É BEM complicado mexer com matrizes em C, e eu tô meio atolado...
                         {'#', '.', '.', '.', '.', '#'},
                         {'#', '.', '.', '.', '.', '#'},
                         {'#', '#', '#', '#', '#', '#'}};


// STRUCTS ------------------------------

typedef struct Player // Talvez seria interessante fazer uma estrutura "Entidade" que possa ser o Pacman e o fantasma?
{
    int posX, posY;
} Player;

typedef struct Fantasma
{
    char skin;
    int posX, posY;
    int Xvel, Yvel;
    char objAbaixo; // Esta variável serve para guardar o que estava presente na célula que o fantasma se mover, pra que ele não apague as bolinhas ou itens
} Fantasma;


// PROTÓTIPOS ---------------------------

char getInput();
void renderGrid(int rows, int cols, char[rows][cols], Player, Fantasma);
void makeMove(Player*, int rows, int cols, char mapa[rows][cols]);
// void checkWin();

void moverFantasma(Fantasma *fan, int rows, int cols, char[rows][cols])
{
    int posX = fan->posX; int posY = fan->posY;
    int velX = fan->Xvel; int velY = fan->Yvel;
    
    char futurePos = mapa[posY + velY][posX + velX];
    
    mapa[posY][posX] = fan->objAbaixo;
    mapa[posY + velY][posX + velX] = fan->skin;

    fan->posX = posX + velX;
    fan->posY = posY + velY;
}

char *main(void) {
    // Inicializando player e fantasmas
    Player p1 = {1, 1};
    Fantasma f1 = {'F', 1, 3, 1, 0, '.'};

    renderGrid(ROWS, COLS, mapa, p1, f1);

    // Loop principal do jogo
    while (1)
    {
        makeMove(&p1, ROWS, COLS, mapa);
        moverFantasma(&f1, ROWS, COLS, mapa);
        renderGrid(ROWS, COLS, mapa, p1, f1);
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

void renderGrid(int rows, int cols, char map[rows][cols], Player player, Fantasma f1)
{
    system("cls");

    // Posicionando o jogador e os fantasmas
    map[player.posY][player.posX] = 'C';
    map[f1.posY][f1.posX] = f1.skin;

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

        // Verificando a validade do movimento (parede => nada acontece; fantasma => jogo encerra)
        if (mapa[pacY + deltaY][pacX + deltaX] == '#')
        {
            printf("vc acertaria uma parede\n");
        }
        else if (mapa[pacY + deltaY][pacX + deltaX] == 'F') // TODO: printar uma mensagem de game over
        {
            exit(0);
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