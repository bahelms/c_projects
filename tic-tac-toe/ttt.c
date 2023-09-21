#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TL *(grid + 0)
#define TC *(grid + 1)
#define TR *(grid + 2)
#define ML *(grid + 3)
#define MC *(grid + 4)
#define MR *(grid + 5)
#define BL *(grid + 6)
#define BC *(grid + 7)
#define BR *(grid + 8)

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

void slice_grid(int *grid, int *slice) {
    slice[0] = *(grid + 0) + *(grid + 3) + *(grid + 6);
    slice[1] = *(grid + 1) + *(grid + 4) + *(grid + 7);
    slice[2] = *(grid + 2) + *(grid + 5) + *(grid + 8);
    slice[3] = *(grid + 0) + *(grid + 1) + *(grid + 2);
    slice[4] = *(grid + 3) + *(grid + 4) + *(grid + 5);
    slice[5] = *(grid + 6) + *(grid + 7) + *(grid + 8);
    slice[6] = *(grid + 0) + *(grid + 4) + *(grid + 8);
    slice[7] = *(grid + 2) + *(grid + 4) + *(grid + 6);
}

int winner(int *grid) {
    int slice[8];
    slice_grid(grid, slice);

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

int choose_square(int *grid, int token) {
    if (TL + ML + BL == token * 2) {
        if (TL == 0)
            return 0;
        if (ML == 0)
            return 3;
        if (BL == 0)
            return 6;
    }
    if (TC + MC + BC == token * 2) {
        if (TC == 0)
            return 1;
        if (MC == 0)
            return 4;
        if (BC == 0)
            return 7;
    }
    if (TR + MR + BR == token * 2) {
        if (TR == 0)
            return 2;
        if (MR == 0)
            return 5;
        if (BR == 0)
            return 8;
    }
    if (TL + TC + TR == token * 2) {
        if (TL == 0)
            return 0;
        if (TC == 0)
            return 1;
        if (TR == 0)
            return 2;
    }
    if (ML + MC + MR == token * 2) {
        if (ML == 0)
            return 3;
        if (MC == 0)
            return 4;
        if (MR == 0)
            return 5;
    }
    if (BL + BC + BR == token * 2) {
        if (BL == 0)
            return 6;
        if (BC == 0)
            return 7;
        if (BR == 0)
            return 8;
    }
    if (TL + MC + BR == token * 2) {
        if (TL == 0)
            return 0;
        if (MC == 0)
            return 4;
        if (BR == 0)
            return 8;
    }
    if (TR + MC + BL == token * 2) {
        if (TR == 0)
            return 2;
        if (MC == 0)
            return 4;
        if (BL == 0)
            return 6;
    }
    return -1;
}

int computer(int ply, int *grid) {
    // grab center ASAP
    if (ply == 0 || (ply == 1 && MC == 0)) {
        puts("Computer snags the center!");
        return 5;
    }

    // take the corner when center is taken
    if (ply == 1 && TL == 0) {
        puts("Computer moves to square 1");
        return 1;
    }

    int square;
    if (ply % 2)
        square = choose_square(grid, -1);
    else
        square = choose_square(grid, 1);

    if (square == -1) {
        if (ply % 2)
            square = choose_square(grid, 1);
        else
            square = choose_square(grid, -1);
    }

    if (square == -1) {
        do {
            square = rand() % 9;
        } while (*(grid + square) != 0);
    }
    square++;
    printf("The computer moves to square %d\n", square);
    return square;
}

int main(int argc, char *argv[]) {
    int grid[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int ply = 0, square, players;

    srand((unsigned)time(NULL));

    puts("Tic-Tac-Toe");
    printf("Number of players (0, 1, 2): ");
    scanf("%d", &players);
    if (players < 0 || players > 2)
        return 1;

    int active = rand() % 2;
    if (active) {
        puts("Computer goes first!");
    } else {
        puts("You go first!");
    }

    while (ply < 9) {
        show_grid(grid);

        if (players == 0) {
            square = computer(ply, grid);
        } else if (players == 1) {
            if (active) {
                square = computer(ply, grid);
                active = 0;
            } else {
                while ((square = prompt(ply, grid)) == -1)
                    ;
                active = 1;
            }
        } else {
            while ((square = prompt(ply, grid)) == -1)
                ;
        }

        if (square == 0)
            break;
        grid[square - 1] = ply % 2 ? -1 : 1;
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
