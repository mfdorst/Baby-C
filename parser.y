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
  ASTCompOp comp_op;
}

%token <string> IDENT
%token <num> NUM

%type <node> DeclarationList
%type <node> Statement
%type <node> StatementList
%type <node> Assignment
%type <node> LHS
%type <node> Condition
%type <node> Compare
%type <node> ComparePrime
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <comp_op> CompOp

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'
{
  g_ast_root = $6;
};

DeclarationList: /* Empty */ {}
| Declaration DeclarationList {}

Declaration: "int" IDENT ';'
{
  add_declaration($2);
  printf("Processing declaration of %s\n", $2);
};

StatementList: /* Empty */
{
  $$ = NULL;
} 
| Statement StatementList
{
  $$ = make_statement_list($1,$2);
  printf("Adding a Statement to a Statement list \n");
};

Statement: Assignment
{
  $$ = $1;
}
| "while" '(' Condition ')' '{' StatementList '}'
{
  printf("Creating while loop node\n");
  $$ = make_while_loop($3, $6);
}
| "if" '(' Condition ')' '{' StatementList '}'
{
  printf("Creating if Statement node\n");
  $$ = make_if($3, $6, NULL);
}
| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}'
{
  printf("Creating if-else Statement node\n");
  $$ = make_if($3, $6, $10);
};

Assignment: LHS '=' Expr ';'
{
  printf("Creating Assignment node\n");
  $$ = make_assignment($1, $3);
};

LHS: IDENT
{
  printf("Creating left-hand IDENT node for %s\n", $1);
  $$ = make_ident($1);
};

Condition: Compare
{
  $$ = $1;
}
| Compare OR Compare
{
  printf("Creating OR node\n");
  $$ = make_logic_op(OP_OR, $1, $3);
};

Compare: ComparePrime
{
  $$ = $1;
}
| ComparePrime AND ComparePrime
{
  printf("Creating AND node\n");
  $$ = make_logic_op(OP_AND, $1, $3);
};

ComparePrime: Expr CompOp Expr
{
  printf("Creating Compare node\n");
  $$ = make_comp_op($2, $1, $3);
};

CompOp:
  '<'  { $$ = OP_LT; }
| '>'  { $$ = OP_GT; }
| "<=" { $$ = OP_LE; }
| ">=" { $$ = OP_GE; }
| "==" { $$ = OP_EQ; }
| "!=" { $$ = OP_NE; };

Expr: Expr '+' Term
{
  printf("Creating Addition node\n");
  $$ = make_arith_op(OP_ADD, $1, $3);
}
| Expr '-' Term
{
  printf("Creating Subtraction node\n");
  $$ = make_arith_op(OP_SUB, $1, $3);
}
| Term
{
  $$ = $1;
};

Term: Term '*' Factor
{
  printf("Creating Multiplication node\n");
  $$ = make_arith_op(OP_MULT, $1, $3);
}
| Term '/' Factor
{
  printf("Creating Division node\n");
  $$ = make_arith_op(OP_DIV, $1, $3);
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
| '(' Expr ')'
{
  printf("Creating Expression node in parentheses\n");
  $$ = $2;
};

%%
