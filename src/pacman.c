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
char fantasmapa[ROWS][COLS]; // Mapa dos fantasmas





// STRUCTS ------------------------------

typedef struct Player // Talvez seria interessante fazer uma estrutura "Entidade" que possa ser o Pacman e o fantasma?
{
    int xPos, yPos;
} Player;

typedef struct Fantasma
{
    char skin;
    int xPos, yPos;
    int xVel, yVel;
} Fantasma;






// PROTÓTIPOS ---------------------------

char getInput();
void renderGrid(char[ROWS][COLS], char[ROWS][COLS], Player, Fantasma);
void moverJogador(Player*, int rows, int cols, char mapa[rows][cols]);
// void checkWin();

void gerarFantasmapa(char s[ROWS][COLS], char d[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            d[i][j] = s[i][j] == '#' ? '#' : ' ' ;
        }
    }
}

// Muda a direção para a qual o fantasma está andando
int mudarDirecao(Fantasma* fan, char mapa[ROWS][COLS])
{
    srand(time(NULL));

    int n = rand() % 3;

    if (n == 0) // Fantasma anda pra direção oposta
    {
        fan->xVel *= -1;
        fan->yVel *= -1;
    }
    else
    {
        // Fantasma andará perpendicularmente para um lado...
        int aux = fan->xVel;

        fan->xVel = fan->yVel;
        fan->yVel = aux;

        if (n == 2) // ... ou para o outro
        {
            fan->xVel *= -1;
            fan->yVel *= -1;

            if(mapa[fan->yPos + fan->yVel][fan->xPos + fan->xVel] == '#')
            {
                fan->xVel *= -1;
                fan->yVel *= -1;
            }
        }
    }
}

void moverFantasma(Fantasma *fan, int rows, int cols, char fm[ROWS][COLS])
{
    int xPos = fan->xPos; int yPos = fan->yPos;
    int xVel = fan->xVel; int yVel = fan->yVel;
    
    char futurePos = fm[yPos + yVel][xPos + xVel];

    if (futurePos == '#')
    {
        mudarDirecao(fan, fm);
    }
    else // TODO: fantasma gasta um turno pra mudar de direção. Imagino que seja por conta desse else, mas tentei movê-lo pra fora e não deu muito certo. Resolver!
    {
        // Move-se para a próxima posição
        fm[yPos][xPos] = ' ';
        fm[yPos + yVel][xPos + xVel] = fan->skin;

    
        fan->xPos = xPos + xVel;
        fan->yPos = yPos + yVel;
    }
}



// MAIN do códiguinho ---------------------------

char* main(void) {
    // Inicializando player e fantasmas
    gerarFantasmapa(mapa, fantasmapa);

    Player p1 = {1, 1};
    Fantasma f1 = {'F', 1, 3, 1, 0, '.'};

    renderGrid(mapa, fantasmapa, p1, f1);

    // Loop principal do jogo
    while (1)
    {
        moverJogador(&p1, ROWS, COLS, mapa);
        moverFantasma(&f1, ROWS, COLS, fantasmapa); // Mudará para moverFantasmas() assim que completarmos a função
        renderGrid(mapa, fantasmapa, p1, f1);
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

void renderGrid(char m[COLS][ROWS], char fm[COLS][ROWS], Player player, Fantasma f1)
{
    system("cls");

    // Posicionando o jogador e os fantasmas
    m[player.yPos][player.xPos] = 'C';
    fm[f1.yPos][f1.xPos] = f1.skin;

    // Printa na tela o valor de cada coordenada do mapa, priorizando os valores da camada dos fantasmas
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (fm[i][j] == ' ')
            {
                printf("%c", m[i][j]);
            }
            else
            {
                printf("%c", fm[i][j]);
            }
        }
        printf("\n");
    }

    printf("fan: xPos: %i, yPos: %i, xVel: %i, yVel: %i\n", f1.xPos, f1.yPos, f1.xVel, f1.yVel);
}

int pontos = 0; // -Cayo: Uma pontuação 

// TODO: contabilizar pontos quando o pacman se move para uma casa onde havia uma bolinha
void moverJogador(Player *pacman, int rows, int cols, char mapa[rows][cols])
{
    char proxMov;
    int pacX = pacman->xPos;
    int pacY = pacman->yPos;

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
            pacman->xPos += deltaX;
            pacman->yPos += deltaY;
            break;
        }
    }
}

void checkwin()
{
    // TODO
}