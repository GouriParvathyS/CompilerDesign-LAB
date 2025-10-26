/*#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
char keywords[MAX][MAX]={"int","float","return","void","char","double","if","else","while","for"};
int iskeyword(char buffer[]){
    for(int i=0;i<10;i++){
        if(strcmp(buffer,keywords[i])==0){
            return 1;
        }
    }
    return 0;
}
int main(){
    FILE *fp;
    char buffer[MAX];
    int i=0;
    char c;
    fp=fopen("input.c","r");
    if (fp==NULL){
        printf("File not found");
        return 0;
    }
    while((c=fgetc(fp))!=EOF){
        if(c==' '|| c=='\t' || c=='\n'){
            continue;
        }
        if (isalpha(c)){
            buffer[i++]=c;
            while(isalnum(c=fgetc(fp))){
                buffer[i++]=c;
            }
            buffer[i]='\0';
            i=0;
            if(iskeyword(buffer)){
                printf("<%s> is keyword\n",buffer);
            }
            else{
                printf("<%s> is identifier\n",buffer);
            }
            if(c==EOF){
                break;
            }
        }
        else if(isdigit(c)){
            buffer[i++]=c;
            while(isdigit(c=fgetc(fp))){
                buffer[i++]=c;
            }
            buffer[i]='\0';
            i=0;
            printf("<%s> is Number\n",buffer);
            if(c==EOF){
                break;
            }
        }
        else{
            switch (c)
            {
            case '+': case '-': case '*': case '/': case '=':
                    printf("<%c> : Operator\n", c);
                    break;
                case '>': case '<':
                    printf("<%s> : Relational Operator\n");
                    break;
                case ';': case ',': case '(': case ')': case '{': case '}':
                    printf("<%c> : Delimiter\n", c);
                    break;
                default:
                    printf("<%c> : Unknown\n", c);
            }
        }
    }
    fclose(fp);
    return 0;
}
#include <stdio.h>
#include <string.h>
#define MAX 20
char states[MAX][MAX];
char from[MAX][MAX],input[MAX][MAX],to[MAX][MAX];
int visited[MAX];
int n,t;
int findindex(char s[]){
    for(int i=0;i<n;i++){
        if(strcmp(s,states[i])==0){
            return i;
        }
    }
    return -1;
}
void findclosure(char s[]){
    int idx=findindex(s);
    if (visited[idx]){
        return;
    }
    visited[idx]=1;
    for(int i=0;i<t;i++){
        if(strcmp(from[i],s)==0 && strcmp(input[i],"e")==0){
            findclosure(to[i]);
        }
    }
}
int main(){
    printf("Enter the no.of states:\n");
    scanf("%d",&n);

    printf("Enter the states:-\n");
    for(int i=0;i<n;i++){
        scanf("%s",states[i]);
    }

    printf("Enter the no.of transitions:\n");
    scanf("%d",&t);
    printf("Enter the transition:-\n");
    for(int i=0;i<t;i++){
        scanf("%s %s %s",from[i],input[i],to[i]);
    }
    for(int i=0;i<n;i++){
        memset(visited,0,sizeof(visited));
        findclosure(states[i]);
        printf("\nThe eclosure  of %s={",states[i]);
        int first=1;
        for(int j=0;j<n;j++){
            if (visited[j]){
                if(!first){
                    printf(",");
                }
                printf("%s",states[j]);
                first=0;
            }
        }
        printf("}");
    }
    printf("\n");
    return 0;
}*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
int n,m;
int trans[MAX][MAX][MAX];
int eclose[MAX][MAX];
char symbol[MAX];

void computeeclose(){
    for(int i=0;i<n;i++){
        eclose[i][i]=1;
        for(int j=0;j<n;j++){
             if(trans[i][m][j]){
                eclose[i][j]=1;
             }
        }
    }
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(eclose[i][k]&&eclose[k][j]){
                    eclose[i][j]=1;
                }
            }
        }
    }
}
int main(){
    printf("Enter the no.of state:\n");
    scanf("%d",&n);
    printf("Enter the no.of symbols:-");
    scanf("%d",&m);
    printf("Enter symbols (e.g. a b ...): ");
    for (int i = 0; i < m; i++) scanf(" %c", &symbol[i]);
    symbol[m] = 'e'; // epsilon
    memset(trans, 0, sizeof(trans));
    memset(eclose, 0, sizeof(eclose));
    for(int i=0;i<n;i++){
        for(int k=0;k<m;k++){
            int count;
            printf("enter th")
        }
    }
}