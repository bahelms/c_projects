#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BSIZE 256

void pithy_saying() {
    const char filename[] = "pithy.txt";
    char buffer[BSIZE];
    char *r, *entry;
    int items = 0;
    char **entries;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        exit(1);
    }

    entries = (char **)malloc(sizeof(char *) * 100);
    if (entries == NULL) {
        fprintf(stderr, "Unable to allocate memory for entries\n");
        exit(1);
    }

    while (!feof(fp)) {
        r = fgets(buffer, BSIZE, fp);
        if (r == NULL)
            break;

        entry = (char *)malloc(sizeof(char) * strlen(buffer) + 1);
        if (entry == NULL) {
            fprintf(stderr, "Unable to allocate memory for entry\n");
            exit(1);
        }
        strcpy(entry, buffer);
        *(entries + items) = entry;
        items++;

        // expand entries list if full
        if (items % 100 == 0) {
            entries = (char **)realloc(entries, sizeof(char *) * (items + 100));
            if (entries == NULL) {
                fprintf(stderr, "Unable to reallocate memory for entries\n");
                exit(1);
            }
        }
    }

    fclose(fp);

    srand((unsigned)time(NULL));
    int saying = rand() % (items - 1);
    printf("%s", *(entries + saying));
}

int main(int argc, char *argv[]) {
    pithy_saying();
    return 0;
}
