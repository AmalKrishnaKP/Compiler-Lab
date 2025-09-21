%{
        #include<stdio.h>
        #include<stdlib.h>
        int yylex();
        int yyerror(char *s);
        int result=0;
%}

%token NUM

%left '+' '-'
%left '*' '/'
%left UMINUS

%%
S:E             {result=$1;}
E:E '-' E       {$$ = $1 - $3;}
 |E '+' E       {$$ = $1 + $3;}
 |E '*' E       {$$ = $1 * $3;}
 |E '/' E       {
                        if($3==0)
                        {
                                printf("Error:dividing by Zero");
                                $$=0;
                        }
                        else{
                                $$=$1/$3;
                        }
                }
 |'-' E %prec UMINUS {$$ = -$2;}
 |'(' E ')'     {$$ = $2;}
 |NUM           {$$ = $1;}
 ;

%%
int main()
{
        printf("enter the expression\n");
        yyparse();
        printf("%d\n",result);
        return 0;
}

int yyerror(char *s)
{
        printf("Error:%s",s);
        return 0;
}
