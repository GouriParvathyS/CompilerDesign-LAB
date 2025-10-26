#include <stdio.h>
#include <string.h>

int main() {
    int n, m, i, j, k;
    int trans[10][10];      // Transition table
    int final[10];          // Final states (1 = final, 0 = not final)
    int mark[10][10] = {0}; // Marked pairs (distinguishable)

 
    int changed;

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("\nEnter transition table (next state numbers):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("From q%d on symbol %d -> ", i, j);
            scanf("%d", &trans[i][j]);
        }
    }

    printf("\nEnter final states (1 = final, 0 = not final):\n");
    for (i = 0; i < n; i++)
        scanf("%d", &final[i]);

    // Step 1: Mark pairs (p, q) where one is final and the other is not
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (final[i] != final[j])
                mark[i][j] = 1;
        }
    }

    // Step 2: Iteratively mark distinguishable pairs
    do {
        changed = 0;
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (!mark[i][j]) {
                    for (k = 0; k < m; k++) {
                        int p = trans[i][k];
                        int q = trans[j][k];
                        if (p != q) {
                            int a = (p < q) ? p : q;
                            int b = (p > q) ? p : q;
                            if (mark[a][b]) {
                                mark[i][j] = 1;
                                changed = 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    } while (changed);

    // Step 3: Print equivalent states
    printf("\nEquivalent States (can be merged):\n");
    int none = 1;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (!mark[i][j]) {
                printf("{ q%d , q%d }\n", i, j);
                none = 0;
            }
        }
    }
    if (none) printf("No equivalent states found.\n");

    return 0;
}
