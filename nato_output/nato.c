#include <ctype.h>
#include <stdio.h>

#define BUFFER_LENGTH 64

int main(int argc, char *argv[]) {
    const char *nato[] = {"Alfa",    "Bravo",  "Charlie", "Delta",    "Echo",
                          "Foxtrot", "Golf",   "Hotel",   "India",    "Juliett",
                          "Kilo",    "Lima",   "Mike",    "November", "Oscar",
                          "Papa",    "Quebec", "Romeo",   "Sierra",   "Tango",
                          "Uniform", "Victor", "Whiskey", "Xray",     "Yankee",
                          "Zulu"};
    char buffer[BUFFER_LENGTH];
    char ch;
    int i = 0;

    printf("Enter a word or phrase: ");
    fgets(buffer, BUFFER_LENGTH, stdin);

    // terminates at null char
    while (buffer[i]) {
        ch = toupper(buffer[i]);
        if (isalpha(ch))
            printf("%s ", nato[ch - 'A']);
        i++;
        if (i == BUFFER_LENGTH)
            break;
    }
    putchar('\n');

    return 0;
}
