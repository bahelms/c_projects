#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Caesarean cipher
int main(int argc, char *argv[]) {
    int shift = 3, ch;

    if (argc > 1) {
        shift = atoi(argv[1]);
    }

    while ((ch = getchar()) != EOF) {
        if (isupper(ch)) {
            ch += shift;
            if (ch > 'Z')
                ch -= 26;
            if (ch < 'A')
                ch += 26;
            putchar(ch);
        } else if (islower(ch)) {
            ch += shift;
            if (ch > 'z')
                ch -= 26;
            if (ch < 'a')
                ch += 26;
            putchar(ch);
        } else {
            putchar(ch);
        }
    }

    return 0;
}
