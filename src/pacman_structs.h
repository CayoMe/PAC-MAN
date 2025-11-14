#ifndef pacman_structs_h
#define pacman_structs_h

typedef struct Player
{
    int xPos, yPos;
} Player;

typedef struct Fantasma
{
    char skin;
    int xPos, yPos;
    int xVel, yVel;
} Fantasma;

#endif /* pacman_structs_h */