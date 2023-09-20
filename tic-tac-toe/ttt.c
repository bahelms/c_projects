#include <stdio.h>

void show_grid(int *grid) {
    const char bfwb[] = "\x1b[32;47m";
    const char bf[] = "\x1b[32m";
    const char xfwb[] = "\x1b[31;47m";
    const char xf[] = "\x1b[31m";
    const char ofwb[] = "\x1b[34;47m";
    const char of[] = "\x1b[34m";
    const char reset[] = "\x1b[0m";

    for (int x = 0; x < 9; x++) {
        switch (*(grid + x)) {
        case -1:
            if (x % 2)
                printf("%s O %s", ofwb, reset);
            else
                printf("%s O %s", of, reset);
            break;
        case 1:
            if (x % 2)
                printf("%s X %s", xfwb, reset);
            else
                printf("%s X %s", xf, reset);
            break;
        default:
            if (x % 2)
                printf("%s %d %s", bfwb, x + 1, reset);
            else
                printf("%s %d %s", bf, x + 1, reset);
        }

        if ((x + 1) % 3 == 0)
            putchar('\n');
    }
    putchar('\n');
}

int prompt(int ply, int *grid) {
    int square;
    printf("%c's turn: Pick a square, 0 to quit: ", ply % 2 ? 'O' : 'X');
    scanf("%d", &square);
    if (square < 0 || square > 9) {
        puts("Value out of range");
        return -1;
    }

    if (square == 0)
        return (square);

    if (*(grid + square - 1) != 0) {
        printf("Square %d is occupied, try again!\n", square);
        return -1;
    }
    return square;
}

int winner(int *grid) {
    int slice[8];

    slice[0] = *(grid + 0) + *(grid + 3) + *(grid + 6);
    slice[1] = *(grid + 1) + *(grid + 4) + *(grid + 7);
    slice[2] = *(grid + 2) + *(grid + 5) + *(grid + 8);
    slice[3] = *(grid + 0) + *(grid + 1) + *(grid + 2);
    slice[4] = *(grid + 3) + *(grid + 4) + *(grid + 5);
    slice[5] = *(grid + 6) + *(grid + 7) + *(grid + 8);
    slice[6] = *(grid + 0) + *(grid + 4) + *(grid + 8);
    slice[7] = *(grid + 2) + *(grid + 4) + *(grid + 6);

    for (int i = 0; i < 8; i++) {
        if (slice[i] == -3) {
            show_grid(grid);
            puts(">>> O wins!");
            return 1;
        }
        if (slice[i] == 3) {
            show_grid(grid);
            puts(">>> X wins!");
            return 1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int grid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ply = 0, input;

    puts("Tic-Tac-Toe");

    while (ply < 9) {
        show_grid(grid);
        while ((input = prompt(ply, grid)) == -1)
            ;
        if (input == 0)
            break;

        grid[input - 1] = ply % 2 ? -1 : 1;

        if (winner(grid))
            break;
        ply++;
    }

    if (ply == 9) {
        show_grid(grid);
        puts("Cat's game!");
    }

    return 0;
}
