// A9 Main Function: main.c
// yacc -d parse.y
// lex scan.l
// cc -g -m32 y.tab.c lex.yy.c main.c syntax.c print.c
#include <stdio.h> 
#include <stdlib.h> 
#include "type.h" 
extern int syntax_err; 
extern A_NODE *root; 
extern FILE *yyin; 

void initialize();
void print_ast();

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
    printf("\nstart syntax analysis\n");
    initialize();
    yyparse();
    if (syntax_err)
        exit(1); 
    print_ast(root);
    semantic_analysis(root);
    print_sem_ast(root); 
    exit(0);
}
