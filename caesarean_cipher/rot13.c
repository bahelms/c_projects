#include <ctype.h>
#include <stdio.h>

// Caesarean cipher - 13 character rotation
int main(int argc, char *argv[]) {
    int ch;

    while ((ch = getchar()) != EOF) {
        if (isalpha(ch)) {
            if (toupper(ch) >= 'A' && toupper(ch) <= 'M') {
                ch += 13;
            } else {
                ch -= 13;
            }
        }
        putchar(ch);
    }

    return 0;
}
