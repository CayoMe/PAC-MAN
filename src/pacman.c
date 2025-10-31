#include <stdio.h>
#include <conio.h> // Biblioteca para receber as setas como entrada do usuário

// Retorna um char representando a seta que o jogador apertou no formato 'u' (up), 'd' (down), 'l' (left), 'r' (right)
// Não retorna nada caso o usuário entre com qualquer tecla que não seja uma setinha
// TODO: criar mais teclas de controle, como [r]einiciar, [s]air, etc.
char move();
// void renderGrid();
// void makeMove();
// void checkWin();

char *main(void) {
    // renderGrid();

    // Loop principal do jogo. É interessante manter o menor número possível de funções nesse loop, mas dá pra mudar
    while (1)
    {
        char test = move();
        if (test == 'u')
        {
            printf("Up!\n");
        }
        else if (test == 'd')
        {
            printf("Down!\n");
        }
        else if (test == 'l')
        {
            printf("Left!\n");
        }
        else
        {
            printf("Right!\n");
        }
        
        // makeMove();
        // renderGrid();
        // checkWin();
    }
}

char move()
{
    char output;

    while (!output)
    {
        int input = getch(); // É uma função estranha que recebe uma tecla sem escrever na tela
    
        if (input == 224)
        {
            input = getch(); // Ela tem que ser chamada duas vezes pra alguns tipos de teclas, como as setinhas

            switch (input)
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

// void renderGrid()
// {
//     // TODO
// }

// void makeMove()
// {
//     // TODO
// }

// void checkwin()
// {
//     // TODO
// }