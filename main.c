/* Week 02: Player can jump (W) and slide (S); no obstacles yet. */
#include <stdio.h>

#define ROWS 7
#define COLS 56
#define INPUT_SIZE 64

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

void showGame(int distance, char pose)
{
    char screen[ROWS][COLS + 1];
    int x, y;

    for (y = 0; y < ROWS; y++)
    {
        for (x = 0; x < COLS; x++)
            screen[y][x] = ' ';
        screen[y][COLS] = '\0';
    }
    for (x = 0; x < COLS; x++)
        screen[6][x] = ((x + distance) % 7 == 0) ? '=' : '_';

    if (pose == 'W')
    {
        /* Jump: draw the runner higher than usual. */
        screen[0][5] = 'O';
        screen[1][4] = '/';
        screen[1][5] = '|';
        screen[1][6] = '\\';
        screen[2][4] = '/';
        screen[2][6] = '\\';
    }
    else if (pose == 'S')
    {
        /* Slide: draw the runner in a low posture. */
        screen[5][3] = '[';
        screen[5][4] = 'O';
        screen[5][5] = '=';
        screen[5][6] = ']';
    }
    else
    {
        screen[2][5] = 'O';
        screen[3][4] = '/';
        screen[3][5] = '|';
        screen[3][6] = '\\';
        screen[4][4] = '/';
        screen[4][6] = '\\';
    }

    printf("\n================ RUNNING GAME ================\n");
    printf(" WEEK 02    DISTANCE: %d    MOVE: %c\n", distance, pose);
    for (y = 0; y < ROWS; y++)
        printf("|%s|\n", screen[y]);
    printf("==============================================\n");
}

int main(void)
{
    char input[INPUT_SIZE];
    char move = 'N';
    int distance = 0;

    printf("Week 02: Practice W (jump), S (slide), N (run), Q (quit).\n");
    while (1)
    {
        showGame(distance, move);
        printf(" Move (W/S/N/Q) + Enter > ");
        if (!readLine(input, INPUT_SIZE))
            break;
        if (input[1] != '\0')
        {
            printf("Enter only one letter.\n");
            continue;
        }
        move = upperLetter(input[0]);
        if (move == 'Q')
            break;
        if (move != 'W' && move != 'S' && move != 'N')
        {
            printf("Invalid move.\n");
            move = 'N';
            continue;
        }
        distance += 5;
    }
    printf("Training complete. Distance: %d\n", distance);
    return 0;
}
