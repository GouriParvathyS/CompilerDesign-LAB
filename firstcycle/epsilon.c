/*#include<stdio.h>
#include<string.h>

char result[20][20], copy[20], states[20][20];

void add_state(char a[20], int i){ 
    strcpy(result[i], a); 
}

void display(int n){ 
    int k=0; 
    printf("\nEpsilon closure of %s = { ", copy); 
    while(k < n){ 
        printf(" %s", result[k]); 
        if(k < n-1) printf(",");  
        k++; 
    } 
    printf(" }\n"); 
}

int main(){ 
    FILE* ipfile; 
    ipfile = fopen("input.txt", "r"); 
    if(ipfile == NULL){
        printf("Error: could not open input.txt\n");
        return 1;
    }

    char state[20], state1[20], state2[20], input[20]; 
    int end, i=0, n, k=0;   

    printf("\nEnter the number of states: "); 
    scanf("%d",&n); 

    printf("\nEnter the states: "); 
    for(k=0; k<n; k++)   // ✅ fixed loop
        scanf("%s", states[k]);   

    for(k=0; k<n; k++){ 
        i=0; 
        strcpy(state, states[k]); 
        strcpy(copy, state); 
        add_state(state, i++);   

        while(1){ 
            end = fscanf(ipfile,"%s%s%s", state1, input, state2); 
            if(end == EOF) 
                break;       

            if(strcmp(state, state1) == 0 && strcmp(input,"e") == 0){ 
                add_state(state2, i++); 
                strcpy(state, state2); 
            } 
        } 

        display(i); 
        rewind(ipfile); 
    } 

    fclose(ipfile);   
    return 0; 
}*/
#include <stdio.h>
#include <string.h>

#define MAX 20

char states[MAX][MAX];
char from[MAX][MAX], input[MAX][MAX], to[MAX][MAX];
int n, t;
int visited[MAX];

// find index of a state
int find_index(char s[]) {
    for (int i = 0; i < n; i++)
        if (strcmp(states[i], s) == 0)
            return i;
    return -1;
}

// recursive epsilon closure
void find_closure(char s[]) {
    int idx = find_index(s);
    if (visited[idx]) return;       // already added
    visited[idx] = 1;               // mark as visited

    for (int i = 0; i < t; i++) {   // check all transitions
        if (strcmp(from[i], s) == 0 && strcmp(input[i], "e") == 0)
            find_closure(to[i]);    // follow epsilon transitions
    }
}

int main() {
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter the states: ");
    for (int i = 0; i < n; i++)
        scanf("%s", states[i]);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (from input to):\nExample: q0 e q1\n");
    for (int i = 0; i < t; i++)
        scanf("%s %s %s", from[i], input[i], to[i]);

    for (int i = 0; i < n; i++) {
        memset(visited, 0, sizeof(visited)); // reset visited array
        find_closure(states[i]);

        printf("\nEpsilon closure of %s = { ", states[i]);
        int first = 1;
        for (int j = 0; j < n; j++) {
            if (visited[j]) {
                if (!first) printf(", ");
                printf("%s", states[j]);
                first = 0;
            }
        }
        printf(" }");
    }

    printf("\n");
    return 0;

}

