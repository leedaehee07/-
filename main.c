/* Week 01: Game screen and basic auto-running (standard C). */
#include <stdio.h>

#define ROWS 7
#define COLS 56

void showGame(int distance)
{
    char screen[ROWS][COLS + 1];
    int x, y;

    for (y = 0; y < ROWS; y++)
    {
        for (x = 0; x < COLS; x++)
            screen[y][x] = ' ';
        screen[y][COLS] = '\0';
    }

    /* The ground pattern changes as the running distance grows. */
    for (x = 0; x < COLS; x++)
    {
        if ((x + distance) % 7 == 0)
            screen[6][x] = '=';
        else
            screen[6][x] = '_';
    }

    /* Player stands on the left side of the screen. */
    screen[2][5] = 'O';
    screen[3][4] = '/';
    screen[3][5] = '|';
    screen[3][6] = '\\';
    screen[4][4] = '/';
    screen[4][6] = '\\';

    printf("\n================ RUNNING GAME ================\n");
    printf(" WEEK 01    DISTANCE: %d\n", distance);
    for (y = 0; y < ROWS; y++)
        printf("|%s|\n", screen[y]);
    printf("==============================================\n");
}

int main(void)
{
    int distance = 0;
    int step;

    printf("Week 01: A basic auto-running demonstration.\n");
    for (step = 0; step < 5; step++)
    {
        showGame(distance);
        distance += 5;
    }
    printf("\nDemo complete. Total distance: %d\n", distance);
    return 0;
}
