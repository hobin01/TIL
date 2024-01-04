%{
#include "hw.tab.h"
%}

%%
"//".*	{ /* ignore comments */ }
"("	{ return OP; }
")"	{ return CP; }
"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"|"	{ return ABS; }
[-+]?[0-9]+  { yylval.double_val = atof(yytext); return NUMBER; }
[-+]?([0-9]*\.?[0-9]+|[0-9]+\.[0-9]*)	{ yylval.double_val = atof(yytext); return NUMBER; }
\n	{ return EOL; }
[ \t]	{ /* ignore white space */ }
.	{ printf("Mystery character %c\n", *yytext); }
%%

