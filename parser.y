%{
	#include "ast.hpp"
  #include "symbol_table.hpp"
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
%type <node> WhileLoop
%type <node> If
%type <node> Condition
%type <node> Compare
%type <node> ComparePr
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <comp_op> CompOp

%%

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'
{
  g_ast_root = $6;
};

DeclarationList: /* Empty */ {} | Declaration DeclarationList {};

Declaration:
"int" IDENT ';'
{
  if (symbol_declared($2)) {
    yyerror(("Multiple declarations of '" + $2 + "'").c_str());
  }
  add_declaration($2);
};

StatementList: /* Empty */ {} 
| Statement StatementList
{
  $$ = make_statement_list($1, $2);
};

Statement: Assignment
{
  $$ = $1;
}
| WhileLoop
{
  $$ = $1;
}
| If
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

WhileLoop: WHILE '(' Condition ')' '{' StatementList '}'
{
  $$ = make_while($3, $6);
};

If: IF '(' Condition ')' '{' StatementList '}'
{
  $$ = make_if($3, $6);
}
| IF '(' Condition ')' '{' StatementList '}' ELSE '{' StatementList '}'
{
  $$ = make_if($3, $6, $10);
};

Condition: Compare
{
  $$ = $1;
}
| Compare OR Compare
{
  $$ = make_logical_op(OP_OR, $1, $3);
};

Compare: ComparePr
{
  $$ = $1;
}
| ComparePr AND ComparePr
{
  $$ = make_logical_op(OP_AND, $1, $3);
};

ComparePr: Expr CompOp Expr
{
  $$ = make_comparison($2, $1, $3);
};

CompOp:
  '<' { $$ = OP_LT; }
| '>' { $$ = OP_GT; }
| LE { $$ = OP_LE; }
| GE { $$ = OP_GE; }
| EQ { $$ = OP_EQ; }
| NE { $$ = OP_NE; };

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
  if (!symbol_declared($1)) {
    yyerror("Ident not declared");
  }
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
