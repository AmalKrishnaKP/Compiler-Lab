%{
        #include "y.tab.h"
        #include <string.h>

%}

%%
[A-Za-z][A-Za-z0-9]*    {
                                yylval.ident=strdup(yytext);
                                return IDENTIFIER;
                        }
[\n]                    {
                                return '\n';
                        }
.                       {
                                return yytext[0];
                        }

%%

int yywrap(){return 1;}
