#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char prod[MAX][MAX];
int n;

char first[MAX][MAX];
char follow[MAX][MAX];

void findFirst(char *res, char c);
void findFollow(char *res, char c);
void add(char *res, char c);

int main() {
    int i;
    char c, res[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (like E->E+T):\n");
    for (i = 0; i < n; i++)
        scanf("%s", prod[i]);

    printf("\n----- FIRST sets -----\n");
    for (i = 0; i < n; i++) {
        c = prod[i][0];
        strcpy(res, "");
        findFirst(res, c);
        printf("FIRST(%c) = { %s }\n", c, res);
        strcpy(first[i], res);
    }

    printf("\n----- FOLLOW sets -----\n");
    for (i = 0; i < n; i++) {
        c = prod[i][0];
        strcpy(res, "");
        findFollow(res, c);
        printf("FOLLOW(%c) = { %s }\n", c, res);
        strcpy(follow[i], res);
    }

    return 0;
}

void add(char *res, char c) {
    if (strchr(res, c) == 0)
        strncat(res, &c, 1);
}

void findFirst(char *res, char c) {
    if (!isupper(c)) {  // terminal
        add(res, c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == c) {
            char rhs = prod[i][3];
            if (rhs == '#')
                add(res, '#');
            else if (!isupper(rhs))
                add(res, rhs);
            else
                findFirst(res, rhs);
        }
    }
}

void findFollow(char *res, char c) {
    if (prod[0][0] == c)
        add(res, '$');  // start symbol

    for (int i = 0; i < n; i++) {
        for (int j = 3; j < strlen(prod[i]); j++) {
            if (prod[i][j] == c) {
                if (prod[i][j + 1] != '\0') {
                    char next = prod[i][j + 1];
                    if (!isupper(next))
                        add(res, next);
                    else {
                        char temp[MAX] = "";
                        findFirst(temp, next);
                        for (int k = 0; k < strlen(temp); k++) {
                            if (temp[k] != '#')
                                add(res, temp[k]);
                            else if (prod[i][0] != c)
                                findFollow(res, prod[i][0]);
                        }
                    }
                } else if (prod[i][0] != c)
                    findFollow(res, prod[i][0]);
            }
        }
    }
}
