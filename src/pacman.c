#include <stdio.h>
#include <conio.h> // Biblioteca para receber as setas como entrada do usuário

// PROTÓTIPOS ----------------------------

char move();
void renderGrid(int rows, int cols, char[rows][cols]);
// void makeMove();
// void checkWin();

char mapa[4][4] = {{'#', '#', '#', '#'}, {'#', '.', '.', '#',}, {'#', '.', '.', '#',}, {'#', '#', '#', '#'}};

struct Pacman
{
    // TODO
};

struct Fantasma
{
    // TODO
};

char *main(void) {
    renderGrid(4, 4, mapa);

    // Loop principal do jogo. É interessante manter o menor número possível de funções nesse loop, mas dá pra mudar
    while (1)
    {
        // makeMove();
        // renderGrid();
        // checkWin();
    }

    return "🥴";
}

// FUNÇÕES ----------------------------

// Retorna um char representando a seta que o jogador apertou no formato 'u' (up), 'd' (down), 'l' (left), 'r' (right)
// Não retorna nada caso o usuário entre com qualquer tecla que não seja uma setinha
char move()
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
    }

    return output;
}

void renderGrid(int rows, int cols, char map[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}


// void makeMove()
// {
//     // TODO
// }

// void checkwin()
// {
//     // TODO
// }