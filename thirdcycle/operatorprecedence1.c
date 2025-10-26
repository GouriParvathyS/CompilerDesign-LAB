#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[20], input[20];
int top = -1;
int i = 0;

// precedence function
int precedence(char c) {
    switch(c) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '(': return 0; // lowest
    }
    return -1;
}

// push to stack
void push(char c) {
    stack[++top] = c;
}

// pop from stack
char pop() {
    return stack[top--];
}

int main() {
    printf("Enter an expression: ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");
    printf("-----\t-----\t------\n");

    push('$'); // bottom marker
    char symbol = input[i];

    while(symbol != '\0' || top > 0) {  // loop until input and stack done
        stack[top + 1] = '\0';  // null-terminate stack for printing
        printf("%s\t%s\t", stack, input + i);

        if(isalnum(symbol)) {  // operand
            printf("Shift (operand)\n");
            symbol = input[++i];
        }
        else if(symbol == '(') {
            push(symbol);
            printf("Shift '('\n");
            symbol = input[++i];
        }
        else if(symbol == ')') {
            while(stack[top] != '(' && top >= 0) {
                pop();
                printf("Reduce till '('\n");
            }
            if(stack[top] == '(') pop(); // remove '('
            symbol = input[++i];
        }
        else if(symbol != '\0' && strchr("+-*/", symbol)) {  // operator
            while(precedence(stack[top]) >= precedence(symbol)) {
                pop();
                printf("Reduce by operator\n");
            }
            push(symbol);
            printf("\t\tShift operator '%c'\n", symbol) ;
            symbol = input[++i];
        }
        else if(symbol == '\0') {  // end of input
            while(top > 0) {
                pop();
                stack[top + 1] = '\0'; // null-terminate after pop
                printf("%s\t%sReduce remaining\n", stack, "");
                }

        }
        else {
            printf("Error: invalid character '%c'\n", symbol);
            break;
        }
    }

    printf("\nParsing complete. Expression accepted.\n");
    return 0;
}
