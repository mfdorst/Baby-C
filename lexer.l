%{
#include <stdio.h>
#include <string.h>
#include <memory>
#include <stdexcept>
#include "ast.hpp"
#include "lexer.hpp"
#include "parse_node.hpp"
#include "parser.tab.hpp"

void yyerror (const char *s) 
{
   printf("ERROR on line %d: %s.\n", yylineno, s);
   exit(1);
}

#define YY_INPUT(buf, bytes_read, max_bytes_to_read) \
  bytes_read = 0; \
  if (!g_lexer_input) { \
    throw std::runtime_error{"g_lexer_input is not initialized"}; \
  } \
  while (true) { \
    char c = g_lexer_input->get(); \
    if (g_lexer_input->eof()) { \
      break; \
    } \
    buf[bytes_read++] = c; \
    if (bytes_read == max_bytes_to_read) { \
      break; \
    } \
  } \

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

[a-zA-Z][a-zA-Z0-9]* {
  yylval.string = yytext;
  return IDENT;
}

0|[1-9][0-9]* {
  yylval.num = std::stoi(yytext);
  return NUM;
}

[ \t\n]+ ; // Ignore whitespace

. {
  yyerror("Unrecognized token");
}
