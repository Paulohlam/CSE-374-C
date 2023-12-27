// Paul Lam
// 05/01/2023
// Wordcount is the C version of Unix command wc. Wordcount takes in
// one or multiple input files and reports the number of lines, words, and
// characters of each indiviual file. For files that can't be oppened, an
// error will be displayed and the file is skipped over. Wordcount can handel
// inputlines up to 500 characters

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 500

typedef struct {
    int lines;
    int words;
    int characters;
} Counts;

/**
 * Processes a single input file and updates the counts for lines,
 * words, and characters.
 *
 * @param file is a pointer to the input file.
 * @param counts is a pointer to the counts struct.
 */
void processFile(FILE *file, Counts *counts) {
    char c;
    bool checker = false;

    while ((c = fgetc(file)) != EOF) {
        (counts->characters)++;

        if (c == '\n') {
            (counts->lines)++;
        }

        if (c == ' ' || c == '\t' || c == '\n') {
            checker = false;
        } else if (!checker) {
            checker = true;
            (counts->words)++;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        exit(1);
    }

    bool countLines = false;
    bool countWords = false;
    bool countChars = false;

    int filesStart = 1;

     while (argv[filesStart] && argv[filesStart][0] == '-') {
        for (int j = 1; j < strlen(argv[filesStart]); j++) {
            switch (argv[filesStart][j]) {
                case 'l':
                    countLines = true;
                    break;
                case 'w':
                    countWords = true;
                    break;
                case 'c':
                    countChars = true;
                    break;
                default:
                    break;
            }
        }
        filesStart++;
    }

    if (argc == filesStart) {
            fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
            exit(1);
        }

    if (!countLines && !countWords && !countChars) {
        countLines = countWords = countChars = true;
    }

    Counts totalCounts = {0, 0, 0};

    for (int i = filesStart; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "%s will not open. Skipping.\n", argv[i]);
            continue;
        }

        Counts counts = {0, 0, 0};
        processFile(file, &counts);

        if (countLines) {
            printf("%4d ", counts.lines);
            totalCounts.lines += counts.lines;
        }
        if (countWords) {
            printf("%4d ", counts.words);
            totalCounts.words += counts.words;
        }
        if (countChars) {
            printf("%4d ", counts.characters);
            totalCounts.characters += counts.characters;
        }

        printf("%s\n", argv[i]);
        fclose(file);
    }

    if (argc - filesStart > 1) {
        if (countLines) {
            printf("Total Lines = %d\n", totalCounts.lines);
        }
        if (countWords) {
            printf("Total Words = %d\n", totalCounts.words);
        }
        if (countChars) {
            printf("Total Characters = %d\n", totalCounts.characters);
        }
        printf("\n");
    }
    return 0;
}
