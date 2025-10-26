#include <stdio.h>
#include <string.h>

char input[20], stack[20];
int top = -1, i = 0;

void check() {
    // Replace id with E
    if (stack[top] == 'i') {
        stack[top] = 'E';
        printf("$%.*s\t%s$\tREDUCE E -> id\n", top+1, stack, input + i);
    }

    // Replace (E) with E
    if (top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        top -= 2;
        stack[top] = 'E';
        printf("$%.*s\t%s$\tREDUCE E -> (E)\n", top+1, stack, input + i);
    }

    // Replace E+E or E*E with E
    if (top >= 2 && stack[top] == 'E' && (stack[top-1] == '+' || stack[top-1] == '*') && stack[top-2] == 'E') {
        top -= 2;
        stack[top] = 'E';
        printf("$%.*s\t%s$\tREDUCE E -> E%cE\n", top+1, stack, input + i, stack[top+1]);
    }
}

int main() {
    printf("Enter the input string (use i for id): ");
    scanf("%s", input);
    printf("\nStack\tInput\tAction\n");
    printf("-----\t-----\t------\n");

    while (i < strlen(input)) {
        // SHIFT: move symbol from input to stack
        stack[++top] = input[i];
        input[i] = ' '; // mark consumed
        printf("$%.*s\t%s$\tSHIFT '%c'\n", top+1, stack, input + i, stack[top]);
        i++;

        // try to REDUCE after every SHIFT
        check();
    }

    // After all input symbols are shifted, do final reductions
    check();

    // If only one E remains, ACCEPT
    if (top == 0 && stack[top] == 'E')
        printf("$E\t$\tACCEPT\n");
    else
        printf("REJECT\n");

    return 0;
}
