#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char prod[MAX][20];
int n;

// Add a symbol to a result string (avoid duplicates)
void add(char *res, char c) {
    if (!strchr(res, c)) {
        int len = strlen(res);
        res[len] = c;
        res[len + 1] = '\0';
    }
}

// Recursive function to find FIRST
void findFirst(char c, char *res) {
    // If terminal, FIRST = itself
    if (!isupper(c)) {
        add(res, c);
        return;
    }

    // For each production with c on LHS
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            char next = prod[i][2];

            // Skip invalid or empty production
            if (next == '\0')
                continue;

            if (!isupper(next))
                add(res, next);
            else if (next != c) // avoid self-recursion like E -> E+T
                findFirst(next, res);
        }
    }
}

// Recursive function to find FOLLOW
void findFollow(char c, char *res) {
    // Add $ to start symbol
    if (prod[0][0] == c)
        add(res, '$');

    // Check all productions for symbol c
    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    char next = prod[i][j + 1];
                    if (!isupper(next))
                        add(res, next);
                    else {
                        char temp[MAX] = "";
                        findFirst(next, temp);
                        for (int k = 0; temp[k] != '\0'; k++)
                            add(res, temp[k]);
                    }
                } else if (prod[i][0] != c)
                    findFollow(prod[i][0], res);
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); // remove newline left by scanf

    printf("Enter productions (like E=E+T):\n");
    for (int i = 0; i < n; i++) {
        fgets(prod[i], sizeof(prod[i]), stdin);
        prod[i][strcspn(prod[i], "\n")] = 0; // remove newline
    }

    for (int i = 0; i < n; i++) {
        char nt = prod[i][0];
        char first[MAX] = "", follow[MAX] = "";

        findFirst(nt, first);
        findFollow(nt, follow);

        printf("\nFIRST(%c) = { ", nt);
        for (int j = 0; j < strlen(first); j++)
            printf("%c ", first[j]);
        printf("}");

        printf("\nFOLLOW(%c) = { ", nt);
        for (int j = 0; j < strlen(follow); j++)
            printf("%c ", follow[j]);
        printf("}\n");
    }

    return 0;
}
