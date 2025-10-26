%{
#include <stdio.h>
%}

%%

.*Gour.*      { printf("Contains first four characters as substring\n"); }
.*\n?         { printf("Accepted\n"); }

%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
