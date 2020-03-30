%{
	#include <stdio.h>
	#include "ast.hpp"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;

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

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> DeclarationList
%type <node> Statement
%type <node> StatementList
%type <node> Expr
%type <node> Term
%type <node> Factor
// Add the rest of the types for the grammar's symbols

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'	{gASTRoot=$6;} // Store the AST root node in gASTRoot
;

DeclarationList: /* Empty */{}
| Declaration DeclarationList {}

Declaration:
"int" IDENT ';'
{
  AddDeclaration($2);
  printf("Processing declaration of %s\n", $2);
};

StatementList: /* Empty */
{
  $$ = NULL;
} 
| Statement StatementList
{
  $$ = CreateStatementListNode($1,$2);
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
  $$ = CreateIdentNode($1);
  printf("Creating IDENT node for %s\n", $1);
}
| NUM
{
  $$ = CreateNumNode($1);
  printf("Creating NUM node for %d\n", $1);
}
| '('Expr')'
{
  $$ = $2;
};

%%
