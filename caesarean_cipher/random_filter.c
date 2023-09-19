#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int ch;

    srand(time(NULL));

    while ((ch = getchar()) != EOF) {
        switch (rand() % 2) {
        case 0:
            putchar(toupper(ch));
            break;
        case 1:
            putchar(tolower(ch));
        }
    }

    return 0;
}
