/* Week 03: Add low/high obstacles and collision detection (standard C). */
#include <stdio.h>

#define ROWS 7
#define COLS 56
#define INPUT_SIZE 64
#define OBSTACLE_X 28

typedef struct
{
    int type;  /* 0 = floor block, 1 = overhead bar */
    int x;
} Obstacle;

char upperLetter(char c)
{
    if (c >= 'a' && c <= 'z')
        return (char)(c - 'a' + 'A');
    return c;
}

int readLine(char text[], int size)
{
    int i = 0;
    int ch;
    if (fgets(text, size, stdin) == NULL)
        return 0;
    while (text[i] != '\0' && text[i] != '\n')
        i++;
    if (text[i] == '\n')
        text[i] = '\0';
    else
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }
    return 1;
}

void putSymbol(char screen[ROWS][COLS + 1], int y, int x, char symbol)
{
    if (y >= 0 && y < ROWS && x >= 0 && x < COLS)
        screen[y][x] = symbol;
}

void showGame(int distance, Obstacle obstacle)
{
    char screen[ROWS][COLS + 1];
    int x, y, d;

    for (y = 0; y < ROWS; y++)
    {
        for (x = 0; x < COLS; x++)
            screen[y][x] = ' ';
        screen[y][COLS] = '\0';
    }
    for (x = 0; x < COLS; x++)
        screen[6][x] = ((x + distance) % 7 == 0) ? '=' : '_';

    putSymbol(screen, 2, 5, 'O');
    putSymbol(screen, 3, 4, '/');
    putSymbol(screen, 3, 5, '|');
    putSymbol(screen, 3, 6, '\\');
    putSymbol(screen, 4, 4, '/');
    putSymbol(screen, 4, 6, '\\');

    if (obstacle.type == 0)
    {
        for (y = 4; y <= 5; y++)
            for (d = -2; d <= 2; d++)
                putSymbol(screen, y, obstacle.x + d, '#');
    }
    else
    {
        for (y = 1; y <= 2; y++)
            for (d = -2; d <= 2; d++)
                putSymbol(screen, y, obstacle.x + d, '=');
    }

    printf("\n================ RUNNING GAME ================\n");
    printf(" WEEK 03    DISTANCE: %d\n", distance);
    for (y = 0; y < ROWS; y++)
        printf("|%s|\n", screen[y]);
    printf("==============================================\n");
    printf(" Floor ##### = W jump   |   Top ===== = S slide\n");
}

int main(void)
{
    char input[INPUT_SIZE];
    char move;
    int distance = 0;
    int round = 1;
    int gameOver = 0;
    Obstacle obstacle;

    printf("Week 03: Dodge obstacles until you collide.\n");
    while (gameOver == 0)
    {
        obstacle.x = OBSTACLE_X;
        obstacle.type = (round - 1) % 2;
        distance += 10;
        showGame(distance, obstacle);

        while (1)
        {
            printf(" Move (W/S/N/Q) + Enter > ");
            if (!readLine(input, INPUT_SIZE))
                return 0;
            if (input[1] != '\0')
            {
                printf("Enter just one letter.\n");
                continue;
            }
            move = upperLetter(input[0]);
            if (move == 'Q')
            {
                printf("Game ended by player.\n");
                return 0;
            }
            if (move == 'W' || move == 'S' || move == 'N')
                break;
            printf("Invalid move.\n");
        }

        if ((obstacle.type == 0 && move == 'W') ||
            (obstacle.type == 1 && move == 'S'))
        {
            printf("[OK] Obstacle avoided!\n");
            round++;
            distance += 2;
        }
        else
        {
            printf("[CRASH] You hit the obstacle!\n");
            gameOver = 1;
        }
    }
    printf("GAME OVER. Final distance: %d\n", distance);
    return 0;
}
