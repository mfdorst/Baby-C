%{
	#include "ast.hpp"
  #include "parse_node.hpp"
  #include <iostream>

	extern int yylex();
	extern int yyerror(const char *);

  #define YYERROR_VERBOSE
  #define YYDEBUG 1
  
%}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

// Terminals
%token <string> IDENT
%token <num> NUM

// Non-terminals
%type <node> DeclarationList
%type <node> Statement
%type <node> StatementList
%type <node> Assignment
%type <node> AssignmentLHS
%type <node> Expr
%type <node> Term
%type <node> Factor

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'
{
  g_ast_root = $6;
};

DeclarationList: /* Empty */ {} | Declaration DeclarationList {};

Declaration:
"int" IDENT ';'
{
  add_declaration($2);
};

StatementList: /* Empty */
{
  $$ = NULL;
} 
| Statement StatementList
{
  $$ = make_statement_list($1, $2);
};

Statement: Assignment
{
  $$ = $1;
};

Assignment: AssignmentLHS '=' Expr ';'
{
  $$ = make_assign($1, $3);
};

AssignmentLHS: IDENT
{
  $$ = make_ident($1, true);
};

Expr: Expr '+' Term
{
  $$ = make_op(OP_ADD, $1, $3);
}
| Expr '-' Term
{
  $$ = make_op(OP_SUB, $1, $3);
}
| Term
{
  $$ = $1;
};

Term: Term '*' Factor
{
  $$ = make_op(OP_MULT, $1, $3);
}
| Term '/' Factor
{
  $$ = make_op(OP_DIV, $1, $3);
}
| Factor
{
  $$ = $1;
};

Factor: IDENT
{
  $$ = make_ident($1, false);
}
| NUM
{
  $$ = make_num($1);
}
| '('Expr')'
{
  std::cout << "Creating Expression node in parentheses\n";
  $$ = $2;
};

%%
