#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
int pos = 0;

// Function prototypes for grammar non-terminals
void E();  // Example: start symbol
void Eprime();
void T();
void Tprime();
void F();

// Error handling
void error() {
    printf("\nSyntax Error at position %d ('%c')\n", pos + 1, input[pos]);
    exit(1);
}

// Advance input pointer
void advance() { pos++; }

// Grammar functions (modify for your own grammar)
void F() {
    printf("F -> ");
    if (isalpha(input[pos])) { printf("id\n"); advance(); }
    else if (input[pos] == '(') { 
        printf("(E)\n"); advance(); E(); 
        if(input[pos]==')') advance(); else error(); 
    }
    else error();
}

void Tprime() {
    if (input[pos] == '*') {
        printf("T' -> * F T'\n"); advance(); F(); Tprime();
    } else printf("T' -> epsilon\n");
}

void T() {
    printf("T -> F T'\n"); F(); Tprime();
}

void Eprime() {
    if (input[pos] == '+') {
        printf("E' -> + T E'\n"); advance(); T(); Eprime();
    } else printf("E' -> epsilon\n");
}

void E() {
    printf("E -> T E'\n"); T(); Eprime();
}

// Main driver
int main() {
    printf("Enter expression: ");
    scanf("%s", input);

    E(); // Start symbol

    if(input[pos]=='\0') printf("\nParsing successful!\n");
    else error();

    return 0;
}
