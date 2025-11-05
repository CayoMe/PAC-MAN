#include <stdio.h>

#define R 4
#define C 4

char matriz[R][C] = {{'#', '#', '#', '#'},
                     {'#', '.', '.', '#'},
                     {'#', '.', '.', '#'},
                     {'#', '#', '#', '#'}};

char copia[R][C];

void copiar_matriz(char s[R][C], char d[R][C])
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            d[i][j] = s[i][j] == '#' ? '#' : ' ';
        }
    }
}

int main(void)
{
    copiar_matriz(matriz, copia);

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%c", matriz[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%c", copia[i][j]);
        }
        printf("\n");
    }
}