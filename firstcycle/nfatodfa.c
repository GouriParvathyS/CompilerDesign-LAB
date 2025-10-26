#include <stdio.h>

int main() {
    int n, m, nfa[10][10][10], count[10][10];
    int i, j, k, s, dfa[20][10][10], dfa_count[20][10], total_dfa = 0;
    int dfa_states[20][10], dfa_states_count[20], newset[10], newcount;
    int found;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);
    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    // --- NFA input ---
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("From q%d on %c -> (enter states, -1 to end): ", i, 'a' + j);
            count[i][j] = 0;
            while (1) {
                scanf("%d", &s);
                if (s == -1) break;
                nfa[i][j][count[i][j]++] = s;
            }
        }
    }

    // --- Start DFA with {q0} ---
    dfa_states[0][0] = 0;
    dfa_states_count[0] = 1;
    total_dfa = 1;

    for (i = 0; i < total_dfa; i++) {
        for (j = 0; j < m; j++) {
            newcount = 0;
            // Combine transitions for each NFA state in current DFA state
            for (k = 0; k < dfa_states_count[i]; k++) {
                s = dfa_states[i][k];
                for (int t = 0; t < count[s][j]; t++) {
                    int x = nfa[s][j][t];
                    int repeat = 0;
                    for (int y = 0; y < newcount; y++)
                        if (newset[y] == x) repeat = 1;
                    if (!repeat) newset[newcount++] = x;
                }
            }

            // Save DFA transition
            dfa_count[i][j] = newcount;
            for (k = 0; k < newcount; k++)
                dfa[i][j][k] = newset[k];

            // Check if new DFA state already exists
            found = 0;
            for (k = 0; k < total_dfa; k++) {
                if (dfa_states_count[k] == newcount) {
                    int same = 1;
                    for (int y = 0; y < newcount; y++)
                        if (dfa_states[k][y] != newset[y]) same = 0;
                    if (same) found = 1;
                }
            }

            // Add new DFA state if not found
            if (!found && newcount > 0) {
                for (k = 0; k < newcount; k++)
                    dfa_states[total_dfa][k] = newset[k];
                dfa_states_count[total_dfa++] = newcount;
            }
        }
    }

    // --- Output ---
    printf("\nEquivalent DFA:\n");
    for (i = 0; i < total_dfa; i++) {
        printf("DFA%d = { ", i);
        for (j = 0; j < dfa_states_count[i]; j++)
            printf("q%d ", dfa_states[i][j]);
        printf("}\n");
        for (j = 0; j < m; j++) {
            printf("  On %c -> { ", 'a' + j);
            for (k = 0; k < dfa_count[i][j]; k++)
                printf("q%d ", dfa[i][j][k]);
            printf("}\n");
        }
    }
}
