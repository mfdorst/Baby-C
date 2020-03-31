%{
#include <stdio.h>
#include <string.h>
#include "ast.hpp"
#include "lexer.hpp"
#include "parser.tab.hpp"

void yyerror (const char *s) 
{
   printf("ERROR on line %d: %s.\n", yylineno, s);
   exit(1);
}

#define YY_INPUT(buf, result, max_size) lex_input(buf, result, max_size)

%}


%option yylineno

/* Prevent unused warnings */
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

[a-zA-Z_][a-zA-Z0-9_]* yylval.string = strdup(yytext); return IDENT;
[0-9]+ yylval.num = atoi(yytext); return NUM;

[ \t\n]+		//Whitespace is ignored
.           printf( "ERROR on Line %d: Unrecognized token \n", yylineno ); exit(1); //No match. Fatal error.
