#include <stdio.h>
#include <conio.h>   // Para receber as setas como entrada do usuário
#include <stdlib.h>
#include <time.h>    // Para gerar seed da função rand()

#define ROWS 6
#define COLS 6




// Mapa do Jueguitos ------------------------------

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

// Muda a direção para a qual o fantasma está andando
int changeDirection(Fantasma* fan, char mapa[ROWS][COLS])
{
    srand(time(NULL));

    int n = rand() % 3;

    if (n == 0) // Fantasma anda pra direção oposta
    {
        fan->Xvel *= -1;
        fan->Yvel *= -1;
    }
    else
    {
        // Fantasma andará perpendicularmente para um lado...
        int aux = fan->Xvel;

        fan->Xvel = fan->Yvel;
        fan->Yvel = aux;

        if (n == 2) // ... ou para o outro
        {
            fan->Xvel *= -1;
            fan->Yvel *= -1;

            if(mapa[fan->posY + fan->Yvel][fan->posX + fan->Xvel] == '#')
            {
                fan->Xvel *= -1;
                fan->Yvel *= -1;
            }
        }
    }
}

void moverFantasma(Fantasma *fan, int rows, int cols, char mapa[ROWS][COLS])
{
    int posX = fan->posX; int posY = fan->posY;
    int velX = fan->Xvel; int velY = fan->Yvel;
    
    char futurePos = mapa[posY + velY][posX + velX];

    if (futurePos == '#')
    {
        changeDirection(fan, mapa);
    }
    else // TODO: fantasma gasta um turno pra mudar de direção. Imagino que seja por conta desse else, mas tentei movê-lo pra fora e não deu muito certo. Resolver!
    {
        mapa[posY][posX] = fan->objAbaixo;
        mapa[posY + velY][posX + velX] = fan->skin;
    
        fan->posX = posX + velX;
        fan->posY = posY + velY;
    }
}



// MAIN do códiguinho ---------------------------

char* main(void) {
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

int pontos = 0; // -Cayo: Uma pontuação 

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
        else if (mapa[pacY + deltaY][pacX + deltaX] == 'F')
        {
            printf("Game Over!!\n");
            exit(0);
        }
        
        else
        {
            // -Cayo: caso ele comer uma bolinha, a gente soma um ponto
            if (mapa[pacY + deltaY][pacX + deltaX] == '.') {
                pontos++;
            }

            // Esvaziando o local atual do jogador e movendo-o para o próximo
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