%{
	#include "ast.h"
	#include <stdio.h>

	extern int yylex();

	extern int yyerror(const char *);

    extern ASTNode* g_ast_root;

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

%union 
{
	ASTNode* node;
	int num;
	char* string;
}

%token <string> IDENT
%token <num> NUM

%type <node> DeclarationList
%type <node> Statement
%type <node> StatementList
%type <node> Expr
%type <node> Term
%type <node> Factor

%%

Goal:
"main" '(' ')' '{' DeclarationList StatementList '}'
{
  g_ast_root = $6;
};

DeclarationList:
/* Empty */ {}
| Declaration DeclarationList {}

Declaration:
"int" IDENT ';'
{
  add_declaration($2);
  printf("Processing declaration of %s\n", $2);
};

StatementList:
/* Empty */
{
  $$ = NULL;
} 
| Statement StatementList
{
  $$ = make_statement_list($1,$2);
  printf("Adding a statement to a statement list \n");
};

Statement: Expr ';'
{
  $$ = $1;
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
  $$ = make_ident($1);
  printf("Creating IDENT node for %s\n", $1);
}
| NUM
{
  $$ = make_num($1);
  printf("Creating NUM node for %d\n", $1);
}
| '('Expr')'
{
  $$ = $2;
};

%%
