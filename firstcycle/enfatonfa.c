#include <stdio.h>
#include <string.h>

#define MAX 20

int n, m;
char symbol[MAX];
int trans[MAX][MAX][MAX]; // [state][symbol][next_state]
int eclose[MAX][MAX];

void computeEclose() {
    for (int i = 0; i < n; i++) {
        eclose[i][i] = 1;
        for (int j = 0; j < n; j++)
            if (trans[i][m][j]) // last symbol = epsilon
                eclose[i][j] = 1;
    }

    // transitive closure
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (eclose[i][k] && eclose[k][j])
                    eclose[i][j] = 1;
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols (excluding ε): ");
    scanf("%d", &m);

    printf("Enter symbols (e.g. a b ...): ");
    for (int i = 0; i < m; i++) scanf(" %c", &symbol[i]);
    symbol[m] = 'e'; // epsilon

    memset(trans, 0, sizeof(trans));
    memset(eclose, 0, sizeof(eclose));

    printf("\n--- Define transitions ---\n");
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= m; k++) {
            int count;
            printf("How many transitions from q%d on '%c'? ", i, symbol[k]);
            scanf("%d", &count);
            for (int c = 0; c < count; c++) {
                int j;
                printf("  To state q: ");
                scanf("%d", &j);
                trans[i][k][j] = 1;
            }
        }
    }

    computeEclose();

    printf("\nEpsilon-closures:\n");
    for (int i = 0; i < n; i++) {
        printf("E(q%d) = { ", i);
        for (int j = 0; j < n; j++)
            if (eclose[i][j]) 
                printf("q%d ", j);
        printf("}\n");
    }

    printf("\nNFA without ε-transitions:\n");
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            int reachable[MAX] = {0};
            for (int p = 0; p < n; p++)
                if (eclose[i][p])
                    for (int q = 0; q < n; q++)
                        if (trans[p][k][q])
                            for (int r = 0; r < n; r++)
                            
                                if (eclose[q][r])
                                    reachable[r] = 1;

            printf("From q%d on '%c' -> { ", i, symbol[k]);
            for (int r = 0; r < n; r++)
                if (reachable[r])
                    printf("q%d ", r);
            printf("}\n");
        }
    }

    return 0;
}
