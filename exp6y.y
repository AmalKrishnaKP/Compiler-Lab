%{
        #include<stdio.h>
        #include<stdlib.h>
        int yylex();
        int yyparse();
        int yyerror(char *s);
%}

%union{
        char *ident;
}

%token <ident> IDENTIFIER

%%

program :
        |program line
        ;
line    :
        IDENTIFIER '\n' {printf("\t \n %s :is a valied identifier\n",$1); free($1)}
        |'\n'                   {}
        |error '\n'             {yyerror("invalied identifier or syntax")}
        ;


%%
int main(){
        printf("enter the identifier one at a line\n");
        yyparse();
        return 0;
}
int yyerror(char *s)
{
        printf("error:%s\n",s);
        return 0;
}
