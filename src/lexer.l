%{
#include "../src/ast.h"
#include "../gen/parser.tab.h"
#include <stdio.h>
#include <string.h>

void yyerror (const char *s) 
{
   printf("ERROR on line %d: %s.\n", yylineno, s);
   exit(1);
}

%}

%option yylineno

/* Don't generate functions we aren't using */
%option nounput
%option noinput
%option noyywrap

%%
"," return ',';
";" return ';';
"+" return '+';
"-" return '-';
"*" return '*';
"/" return '/';
"<" return '<';
">" return '>';
"=" return '=';
"(" return '(';
")" return ')';
"{" return '{';
"}" return '}';

"||" return OR;
"&&" return AND; 
"==" return EQ;
"!=" return NE;
"<=" return LE;
">=" return GE;

"int" return INT;
"main" return MAIN;
"if"  return IF;
"else" return ELSE;
"while" return WHILE;

[a-zA-Z][a-zA-Z0-9]* {
  yylval.string = strdup(yytext);
  return IDENT;
}
0|[1-9][0-9]* {
  yylval.num = atoi(yytext);
  return NUM;
}
[ \t\n]+ // Ignore whitespace
. {
  printf( "ERROR on Line %d: Unrecognized token \n", yylineno );
  exit(1);
}
