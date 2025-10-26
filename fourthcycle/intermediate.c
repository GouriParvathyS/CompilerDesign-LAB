#include <stdio.h>
#include <string.h>

// Generate code for a specific operator
void gen_code_for_operator(char *inp, char operator, char *reg) {
    int i = 0, j = 0;
    char temp[100];
    while (inp[i] != '\0') {
        if (inp[i] == operator) {
            printf("%c\t%c\t%c\t%c\n", operator, *reg, inp[i - 1], inp[i + 1]);
            temp[j - 1] = *reg;  // replace left operand with temporary
            i += 2;               // skip operator and right operand
            (*reg)--;             // move to next temporary
            continue;
        }
        temp[j] = inp[i];
        i++;
        j++;
    }
    temp[j] = '\0';
    strcpy(inp, temp);  // update expression
}

// Generate intermediate code for the whole expression
void gen_code(char *inp) {
    char reg = 'Z';  // start temporary from Z
    gen_code_for_operator(inp, '/', &reg);
    gen_code_for_operator(inp, '*', &reg);
    gen_code_for_operator(inp, '+', &reg);
    gen_code_for_operator(inp, '-', &reg);
    gen_code_for_operator(inp, '=', &reg);
}

int main() {
    char inp[100];
    printf("Enter expression:\n");
    scanf("%s", inp);

    printf("Op\tDestn\tArg1\tArg2\n");
    gen_code(inp);

    return 0;
}
