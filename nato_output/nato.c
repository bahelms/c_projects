#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 64

char isterm(char *, const char *[]);
void natoToWord(const char *[]);
void wordToNato(const char *[]);
void checkFile(char *, const char *[]);

int main(int argc, char *argv[]) {
    const char *nato[] = {"Alfa",    "Bravo",  "Charlie", "Delta",    "Echo",
                          "Foxtrot", "Golf",   "Hotel",   "India",    "Juliett",
                          "Kilo",    "Lima",   "Mike",    "November", "Oscar",
                          "Papa",    "Quebec", "Romeo",   "Sierra",   "Tango",
                          "Uniform", "Victor", "Whiskey", "Xray",     "Yankee",
                          "Zulu"};

    if (argc > 1) {
        if (strcmp(argv[1], "--nato-to-word") == 0) {
            natoToWord(nato);
        } else if (strcmp(argv[1], "--file") == 0) {
            if (argc < 3) {
                fprintf(stderr, "Please supply a text file argument\n");
                exit(1);
            }
            checkFile(argv[2], nato);
        }
    } else {
        wordToNato(nato);
    }

    return 0;
}

void natoToWord(const char *nato[]) {
    char phrase[BUFFER_LENGTH];
    char *match;
    char ch;

    printf("NATO word or phrase: ");
    fgets(phrase, BUFFER_LENGTH, stdin);

    match = strtok(phrase, " ");
    while (match) {
        if ((ch = isterm(match, nato)) != '\0')
            putchar(ch);
        match = strtok(NULL, " "); // this hurts my soul
    }
    putchar('\n');
}

void wordToNato(const char *nato[]) {
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
}

void checkFile(char *filename, const char *nato[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open '%s'\n", filename);
        exit(1);
    }

    const int MAX_WORD_LENGTH = 64;
    char word[MAX_WORD_LENGTH];
    int ch;
    int offset = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            word[offset] = ch;
            offset++;
            if (offset >= MAX_WORD_LENGTH) {
                fprintf(stderr, "Buffer overflow\n");
                return;
            }
        } else if (offset > 0) {
            word[offset] = '\0';
            putchar(isterm(word, nato));
            offset = 0;
        }
    }
    putchar('\n');
    fclose(file);
}

char isterm(char *term, const char *nato[]) {
    const char *n;
    char *t;

    for (int i = 0; i < 26; i++) {
        n = nato[i];
        t = term;
        while (*n != '\0') {
            if ((*n | 0x20) != (*t | 0x20))
                break;
            n++;
            t++;
        }

        if (*n == '\0')
            return *nato[i];
    }

    return '\0';
}
