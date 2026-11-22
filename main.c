/*
 * RUNNING GAME - Standard C (C11)
 *
 * W = jump over a block on the ground
 * S = slide under an overhead bar
 * N = keep running (hits the obstacle)
 * Q = quit
 *
 * Type the letters and press Enter. No Windows-only functions are used.
 */
#include <stdio.h>

#define ROWS 7
#define COLS 56
#define MAX_OBSTACLES 3
#define INPUT_SIZE 64

/* An obstacle is either on the floor (0) or overhead (1). */
typedef struct
{
    int type;
    int x;
} Obstacle;

typedef struct
{
    int distance;
    int score;
    int passed;
    int level;
    int round;
    int gameOver;
} Game;

/* Read one whole line so leftover characters cannot affect the next turn. */
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
            /* Discard excess input. */
        }
    }
    return 1;
}

char upperLetter(char c)
{
    if (c >= 'a' && c <= 'z')
        return (char)(c - 'a' + 'A');
    return c;
}

void resetGame(Game *game)
{
    game->distance = 0;
    game->score = 0;
    game->passed = 0;
    game->level = 1;
    game->round = 1;
    game->gameOver = 0;
}

/* The difficulty grows without real-time timers. */
int countObstacles(int level)
{
    if (level >= 5)
        return 3;
    if (level >= 3)
        return 2;
    return 1;
}

void createObstacles(const Game *game, Obstacle obstacles[], int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        /* Spread obstacle symbols evenly across the display. */
        obstacles[i].x = COLS * (i + 1) / (count + 1);

        /* In level 1, practice jumping. Later levels mix both types. */
        if (game->level == 1)
            obstacles[i].type = 0;
        else
            obstacles[i].type = (game->round + i + game->passed / 2) % 2;
    }
}

void putSymbol(char screen[ROWS][COLS + 1], int y, int x, char symbol)
{
    if (y >= 0 && y < ROWS && x >= 0 && x < COLS)
        screen[y][x] = symbol;
}

/* A readable side-view screen made only with text characters. */
void showGame(const Game *game, const Obstacle obstacles[], int count)
{
    char screen[ROWS][COLS + 1];
    int x, y, i, d;

    for (y = 0; y < ROWS; y++)
    {
        for (x = 0; x < COLS; x++)
            screen[y][x] = ' ';
        screen[y][COLS] = '\0';
    }

    /* Ground */
    for (x = 0; x < COLS; x++)
        screen[6][x] = ((x + game->distance) % 7 == 0) ? '=' : '_';

    /* Runner on the left: head, arms, and legs */
    putSymbol(screen, 2, 5, 'O');
    putSymbol(screen, 3, 4, '/');
    putSymbol(screen, 3, 5, '|');
    putSymbol(screen, 3, 6, '\\');
    putSymbol(screen, 4, 4, '/');
    putSymbol(screen, 4, 6, '\\');

    for (i = 0; i < count; i++)
    {
        x = obstacles[i].x;
        /* Label each obstacle so W/S letters can be typed left-to-right. */
        putSymbol(screen, 0, x, (char)('1' + i));

        if (obstacles[i].type == 0)
        {
            /* FLOOR block: W jumps over it. */
            for (y = 4; y <= 5; y++)
                for (d = -2; d <= 2; d++)
                    putSymbol(screen, y, x + d, '#');
        }
        else
        {
            /* OVERHEAD bar: S slides underneath it. */
            for (y = 1; y <= 2; y++)
                for (d = -2; d <= 2; d++)
                    putSymbol(screen, y, x + d, '=');
        }
    }

    printf("\n============================================================\n");
    printf(" RUNNING GAME    SCORE: %d    DIST: %d    LEVEL: %d / 5\n",
           game->score, game->distance, game->level);
    printf(" ROUND: %d        PASSED: %d\n", game->round, game->passed);
    printf("============================================================\n");
    for (y = 0; y < ROWS; y++)
        printf("|%s|\n", screen[y]);
    printf("============================================================\n");
    printf(" FLOOR BLOCK [#####] -> W (JUMP)\n");
    printf(" TOP BAR     [=====] -> S (SLIDE)\n");
    printf(" N = run without action (CRASH)       Q = quit\n");
    printf(" Obstacles this round: %d. Enter moves left to right.\n", count);

    if (count == 1)
        printf(" Example input: W  or  S, then Enter\n");
    else if (count == 2)
        printf(" Example input: WS or SW, then Enter\n");
    else
        printf(" Example input: WSW or SWS, then Enter\n");
}

/* Remove spaces, check valid characters, and check the move count. */
int parseMoves(const char input[], char moves[], int count)
{
    int i, found = 0;
    char c;

    for (i = 0; input[i] != '\0'; i++)
    {
        c = upperLetter(input[i]);
        if (c == ' ' || c == '\t' || c == '\r')
            continue;
        if (c != 'W' && c != 'S' && c != 'N')
            return 0;
        if (found >= count)
            return 0;
        moves[found] = c;
        found++;
    }
    return found == count;
}

/* Return 1 after a collision, 0 when the player quits or closes input. */
int playGame(void)
{
    Game game;
    Obstacle obstacles[MAX_OBSTACLES];
    char input[INPUT_SIZE];
    char moves[MAX_OBSTACLES];
    int count, i, gap, correctType;

    resetGame(&game);
    printf("\nWelcome to RUNNING GAME!\n");
    printf("This is a turn-based game written in standard C.\n");

    while (game.gameOver == 0)
    {
        count = countObstacles(game.level);
        createObstacles(&game, obstacles, count);

        /* The player runs automatically to the next obstacle group. */
        gap = 12 - game.level;
        game.distance += gap;
        game.score += gap;
        showGame(&game, obstacles, count);

        while (1)
        {
            printf("\n Your move > ");
            if (!readLine(input, INPUT_SIZE))
                return 0;

            if ((input[0] == 'q' || input[0] == 'Q') && input[1] == '\0')
                return 0;

            if (parseMoves(input, moves, count))
                break;

            printf(" Invalid input. Enter exactly %d letter(s) using W, S or N.\n", count);
        }

        for (i = 0; i < count; i++)
        {
            correctType = (obstacles[i].type == 0 && moves[i] == 'W') ||
                          (obstacles[i].type == 1 && moves[i] == 'S');

            game.distance += 2;
            if (correctType)
            {
                game.passed++;
                game.score += 10;
                printf(" [OK] Obstacle %d: %s! +10 points\n", i + 1,
                       moves[i] == 'W' ? "JUMP" : "SLIDE");
            }
            else
            {
                printf(" [CRASH] Obstacle %d! Incorrect action.\n", i + 1);
                game.gameOver = 1;
                break;
            }
        }

        game.level = 1 + game.passed / 3;
        if (game.level > 5)
            game.level = 5;

        if (!game.gameOver)
        {
            printf(" [CLEAR] Round complete! Total score: %d\n", game.score);
            game.round++;
        }
    }

    printf("\n**************** GAME OVER ****************\n");
    printf(" FINAL SCORE: %d   DISTANCE: %d\n", game.score, game.distance);
    printf(" PASSED: %d       LEVEL: %d\n", game.passed, game.level);
    printf("*******************************************\n");
    return 1;
}

int main(void)
{
    char input[INPUT_SIZE];

    while (1)
    {
        if (!playGame())
            break;

        printf("\n Play again? (Y/N) > ");
        if (!readLine(input, INPUT_SIZE))
            break;
        if (upperLetter(input[0]) != 'Y' || input[1] != '\0')
            break;
    }
    printf("\nThank you for playing!\n");
    return 0;
}
