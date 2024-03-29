// A9 Main Function: main.c
// yacc -d parse.y
// lex scan.l
// cc -g -m32 y.tab.c lex.yy.c main.c syntax.c print.c
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "type.h" 
extern int syntax_err; 
extern A_NODE *root; 
extern FILE *yyin; 
FILE *fout;

void initialize();
void print_ast();
void yyparse();
void semantic_analysis(A_NODE *);
void print_sem_ast(A_NODE *);
void code_generation(A_NODE *);


void main(int argc, char *argv[]) 
{
    if (argc < 2) {
        printf("source file not given\n");
        exit(1);
    }
    if ( (argc == 2) && (yyin = fopen(argv[argc-1],"r")) == NULL ) {
        printf("can not open input file: %s\n",argv[argc-1]);
        exit(1);
    } 

    char name[255];
    strcpy(name, "./interpreter/testprogram/");
    strcat(name, argv[1]);

    fout = fopen(name, "w+");

    printf("\nstart syntax analysis\n");
    initialize();
    yyparse();
    if (syntax_err)
        exit(1); 
    print_ast(root);
    semantic_analysis(root);
    print_sem_ast(root); 
    code_generation(root);
    exit(0);
}
