#include "pacman_functions.h"
#include <stdio.h>
#include <conio.h> // Para receber as setas como entrada do usuário
#include <stdlib.h>
#include <time.h> // Para gerar seed da função rand()

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

void gerarFantasmapa(char s[ROWS][COLS], char d[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            d[i][j] = s[i][j] == '#' ? '#' : ' ';
        }
    }
}

void renderGrid(char m[ROWS][COLS], char fm[ROWS][COLS], Player player, Fantasma f1, int *pontos)
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
                if (m[i][j] == 'C')
                {
                    printf("\033[1;33m%c\033[0m", m[i][j]); // Pac-Man amarelo
                }
                else
                {
                    printf("%c", m[i][j]);
                }
            }
            else
            {
                if (fm[i][j] == 'F')
                {
                    printf("\033[1;31m%c\033[0m", fm[i][j]); // Fantasma vermelho
                    if (m[i][j] == 'C')
                    {
                        system("cls");
                        printf("\nGame Over!!\n");
                        printf("Sua pontuacao: %d\n", (*pontos));
                        exit(0);
                    }
                }
                else
                {
                    printf("%c", fm[i][j]);
                }
            }
        }
        printf("|");                   // DEBUG 02
        for (int k = 0; k < COLS; k++) // DEBUG 02
        {                              // DEBUG 02
            printf("%c", fm[i][k]);    // DEBUG 02
        } // DEBUG 02
        printf("\n");
    }

    int xAhead = f1.xPos + f1.xVel;
    int yAhead = f1.yPos + f1.yVel;                                                                                            // DEBUG 01
    printf("yAhead: %i, xAhead: %i\n", yAhead, xAhead);                                                                        // DEBUG 01
    printf("fan: xPos: %i, yPos: %i, xVel: %i, yVel: %i, sees: %c\n", f1.xPos, f1.yPos, f1.xVel, f1.yVel, fm[yAhead][xAhead]); // DEBUG 01
}

// TODO: contabilizar pontos quando o pacman se move para uma casa onde havia uma bolinha
void moverJogador(Player *pacman, int rows, int cols, char mapa[ROWS][COLS], int *pontos)
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
            if (mapa[pacY + deltaY][pacX + deltaX] == '.')
            {
                (*pontos)++;
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

void moverFantasma(Fantasma *fan, char fm[ROWS][COLS])
{
    // Renderiza o fantasma em sua próxima posição
    fm[fan->yPos][fan->xPos] = ' ';
    fm[fan->yPos + fan->yVel][fan->xPos + fan->xVel] = fan->skin;

    // Muda de fato a coordenada do fantasma
    fan->xPos += fan->xVel;
    fan->yPos += fan->yVel;

    int xAhead = fan->xPos + fan->xVel;
    int yAhead = fan->yPos + fan->yVel;

    if (fm[yAhead][xAhead] != ' ')
    {
        mudarDirecao(fan, fm);
    }
}

// Muda a direção para a qual o fantasma está andando
// kris: Eu prevejo que essa função não vai funcionar adequadamente caso um fantasma entre num beco sem saída.
// kris: Por enquanto, deixemos assim, MAS... se der merda, é só adicionar uma condição que conta quantos # tem em volta do fantasma, se for 3, ele vira pra trás
int mudarDirecao(Fantasma *fan, char fm[ROWS][COLS])
{
    srand(time(NULL));

    int n = rand() % 3;

    if (n == 0) // Fantasma vira para a direção oposta
    {
        fan->xVel *= -1;
        fan->yVel *= -1;
    }
    else
    {
        // Fantasma vira perpendicularmente para um lado...
        int aux = fan->xVel;

        fan->xVel = fan->yVel;
        fan->yVel = aux;

        if (n == 2) // ... ou para o outro
        {
            fan->xVel *= -1;
            fan->yVel *= -1;
        }

        // Verifica se a próxima posição é valida ou não. Se não for, inverte
        if (fm[fan->yPos + fan->yVel][fan->xPos + fan->xVel] != ' ')
        {
            fan->xVel *= -1;
            fan->yVel *= -1;
        }
    }
}