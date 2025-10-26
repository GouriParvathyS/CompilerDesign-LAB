#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// List of keywords
char keywords[10][10] = {"int", "float", "if", "else", "for", "while", "return", "void", "char", "double"};

// Function to check if a word is a keyword
int isKeyword(char buffer[]) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(buffer, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char c, buffer[MAX];
    int i = 0;

    fp = fopen("input.c", "r"); // Input file
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 0;
    }

    while ((c = fgetc(fp)) != EOF) {
        // Ignore spaces, tabs, and newlines
        if (c == ' ' || c == '\t' || c == '\n')
            continue;

        // If alphanumeric, build the token
        if (isalpha(c)) {
            buffer[i++] = c;
            while (isalnum(c = fgetc(fp)))
                buffer[i++] = c;
            buffer[i] = '\0';
            i = 0;
            if (isKeyword(buffer))
                printf("<%s> : Keyword\n", buffer);
            else
                printf("<%s> : Identifier\n", buffer);
            if (c == EOF)
                break;
        }
        // If digit, read number
        else if (isdigit(c)) {
            buffer[i++] = c;
            while (isdigit(c = fgetc(fp)))
                buffer[i++] = c;
            buffer[i] = '\0';
            i = 0;
            printf("<%s> : Number\n", buffer);
            if (c == EOF)
                break;
        }
        // Operators and delimiters
        else {
            switch (c) {
                case '+': case '-': case '*': case '/': case '=':
                    printf("<%c> : Operator\n", c);
                    break;
                case '>': case '<':
                    printf("<%s> : Relational Operator\n");
                    break;
                case ';': case ',': case '(': case ')': case '{': case '}':
                    printf("<%c> : Delimiter\n", c);
                    break;
                default:
                    printf("<%c> : Unknown\n", c);
            }
        }
    }

    fclose(fp);
    return 0;
}
