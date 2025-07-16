%{
/*	
	Brady Scaggari Feb 27. 2024	LAB 6
	Implemented next connected for Param list local decls, statement list, 
	declaration list, and arg list.

	added node typings for the nonTerminals on lines 51,52,53 all of these nonterminals either create a node or have a reference to a created node. 

	Yacc has tokens from lex. These include things like operators, conditional operators. Relational operators etc. +,-,/,*,%,==, <=... etc.

	Type specifier is given a d_type from ast.h enum AST_MY_DATA_TYPE this is either VOID or INT type. 

	This program takes the token generated grammar from lex and uses NonTerminals to create a Abstract Syntax Tree. This is used for giving direction to an unambiguous language or grammar
	This program is LR(1) grammar for it has left recursion. The program is top down, but parses from the most bottom nonterminal upwards. The start of every language will always have declarations 
	these two declarations are called variable declarations and function declarations. Within each function/statement there is a compound statement. Compound statements have local declarations 
	these local declarations are designed to give a local scope within our AST. This is why compound statements are not next connected but, local declarations are next connected. 

	A statement list is also next connected. this ensures that our expression,compute are given a scope within each statmenet. we next connect the statment list so we can have multiple
	statments within a function or program, any expressions within each statmenet are either s1 connected and or s2 connected with if statement being unique for the conditon of there
	being an else statement, in case of this we s2->s1 connect the else statement.   

*/


/*begin specs*/
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "ast.h"
#include "emit.h"
#include "symtable.h"

ASTnode *PROGRAM;

int yylex();
extern int myDebug;
extern int lineCount;

int LEVEL = 0; // global var for levels
int OFFSET = 0; // global var for accumulating runtime spaces
int GOFFSET = 0; // glbal variable for accumulation of global offset
int maxoffset = 0; // largest off set needed for print

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("YACC PARSE ERROR: %s on line %d\n", s, lineCount);
}

%}

%start Program

%union{
	int value; 
	char * string;
    ASTnode *node;
	enum AST_MY_DATA_TYPE d_type;
	enum AST_OPERATORS operator;
}

%token <value>T_NUM
%token <string>T_ID T_STRING
%token T_INT 
%token T_VOID
%token T_READ T_RETURN T_WRITE T_WHILE T_IF T_ELSE
%token T_LT T_GT T_EQ T_LE T_GE T_NE T_DIV T_MULT T_ADD T_SUB T_MOD

%type <node> Declaration_List Declaration Var_Declaration Var_List Fun_Declaration Params Compound_Statement Local_Declarations Statement_List
%type <node> Statement Write_Statement Read_Statement Expression Simple_Expression  Additive_Expression Expression_Statement Param Param_List
%type <node> Term Factor Var Call Arg_List Args Selection_Statement Return_Statement Iteration_Statement Assignment_Statement 
%type <d_type> Type_Specifier
%type <operator> Addop Multop Relop

%%	/* end specs, begin rules */
	
Program	:	Declaration_List    {PROGRAM = $1; }
		;


Declaration_List : Declaration 
					{	
						$$ = $1;
					}
				|	Declaration	Declaration_List
                    {
                        $$ = $1;
                        $$ ->next = $2; // next connect declarations 
                    }
				;

Declaration :	Var_Declaration 
				{   
					$$=$1;  
				}

			|
				Fun_Declaration 
				{
					$$=$1;
                }
			;

Var_Declaration : Type_Specifier Var_List	';'
                    { /*update all elements to the list to the type*/
						
						/*populate s1 connected list with defined type @$1*/
						ASTnode *p = $2;
						while(p != NULL){
							p->my_data_type = $1;
							//check each variable to see if already defined @ given level
							if(Search(p->name, LEVEL,0) != NULL)
							{	//Symbol defined BARF
								yyerror(p->name);
								yyerror("Symbol already defined");
								exit(1);
							}
							if(p->value == 0){
								p->symbol = Insert(p->name, p->my_data_type, SYM_SCALAR,LEVEL,1,OFFSET);
								OFFSET = OFFSET + 1;
							}
							else {
								p->symbol = Insert(p->name, p->my_data_type, SYM_ARRAY,LEVEL,p->value,OFFSET);
								OFFSET = OFFSET + p->value;
							}
							p = p->s1;
						}
                        $$ = $2;/*dollar dollar = dolar two*/
                    }
				;
/* ASTnode *ASTCreateNode(enum ASTtype mytype) */

Var_List	:	T_ID    {   $$=ASTCreateNode(A_VARDEC); 
                            $$->name = $1;
                        }
			|	T_ID	'['	T_NUM	']'
						{
							$$=ASTCreateNode(A_VARDEC);
							$$->name = $1;
							$$->value = $3; //size of array
						}
			|	T_ID	','	Var_List    
						{
							$$=ASTCreateNode(A_VARDEC);
							$$->name = $1;
							$$->s1 = $3; // s1 connect var list
						}
			|	T_ID	'['	T_NUM	']'	','	Var_List    
						{
							$$=ASTCreateNode(A_VARDEC);
							$$->name = $1;
							$$->value = $3; // size of array
							$$->s1 = $6; // s1 connect var list
						}
			;

Type_Specifier	:	T_INT	{	$$ = A_INTTYPE;}
				|	T_VOID	{	$$ = A_VOIDTYPE;}
				;

Fun_Declaration	:	Type_Specifier T_ID
					{//check if function is defined
						if(Search($2,LEVEL,0) != NULL) {
							//id already used for func
							yyerror($2);
							yyerror("function name already in use");
							exit(1);
						}	
						//put into symbol table 
						Insert($2,  $1,  SYM_FUNCTION,	LEVEL,	0,	0);

						GOFFSET = OFFSET;
						OFFSET = 2;
						maxoffset = OFFSET;
					}
					'(' Params ')'	
					{
						Search($2, LEVEL, 0)->fparms = $5;
					}
					Compound_Statement 
					{		
						$$ = ASTCreateNode(A_FUNCTIONDEC);
						$$->name = $2;
						$$->my_data_type = $1; // INT OR VOID
						$$->s1 = $5; // PARAMS LIST
						$$->s2 = $8; // S2 connect compound statement
						$$->symbol = Search($2,LEVEL,0);
						$$->symbol->offset = maxoffset;
						OFFSET -= Delete(1);
						LEVEL = 0;
						OFFSET = GOFFSET; // resets offset for global vars
					}
				;

Params	:	T_VOID 
			{
				$$ = NULL;
			}
		|	Param_List 
			{
			$$ = $1;// fixme
			}
		;

Param_List	:	Param
				{
					$$ = $1; // param
				}
			|	Param	','	Param_List
				{
					$1->next = $3; //next connect param list
					$$ = $1; 
				}
			;

Param	:	Type_Specifier	T_ID
			{
				if(Search($2, LEVEL+1,0) != NULL ) {
					yyerror($2);
					yyerror("parameter already used");
					exit(1);
				}
				
				$$ = ASTCreateNode(A_PARAM);
				$$->my_data_type = $1; // INT OR VOID
				$$->name = $2; // ID
				$$->symbol = Insert($$->name, $$->my_data_type, SYM_SCALAR, LEVEL + 1, 1,OFFSET);
				OFFSET = OFFSET + 1;
			}
		|	Type_Specifier	T_ID	'[' ']'
			{	
				if(Search($2, LEVEL+1,0) != NULL ) {
					yyerror($2);
					yyerror("parameter already used");
					exit(1);
				}
				$$= ASTCreateNode(A_PARAM);
				$$->my_data_type = $1; // INT OR VOID 
				$$->name = $2; // ID
				$$->value = 777; //specify passing array
				$$->symbol = Insert($$->name, $$->my_data_type, SYM_ARRAY, LEVEL + 1, 1,OFFSET);
				OFFSET = OFFSET + 1;
			}
		;

Compound_Statement	:	'{'	{ LEVEL++; } Local_Declarations	Statement_List	'}'
						{
							
							$$ = ASTCreateNode(A_COMPOUND);
							$$->s1 = $3;
							$$->s2 = $4;
							if(myDebug) 	Display();
							if(OFFSET > maxoffset) maxoffset = OFFSET;
							OFFSET -= Delete(LEVEL);
							LEVEL--;
						}
					;

Local_Declarations	:		Var_Declaration Local_Declarations
					{
						$$ = $1;
						$$->next = $2; // next connect local declarations/var decls
					}

					| /*empty*/ 
					{
						$$ = NULL; 
					}
					;

Statement_List	:	/*empty*/
					{
						$$ = NULL;
					}
				|	Statement Statement_List
					{
						$$ = $1;
						$$->next = $2;
					}
				;

Statement	:	Read_Statement {	$$ = $1;}
			|	Write_Statement {	$$ = $1; }
			|	Compound_Statement {	$$ = $1; }
			|	Expression_Statement {	$$ = $1; }
			|	Selection_Statement {	$$ = $1; }
			|	Return_Statement {	$$ = $1; }
			|	Assignment_Statement {	$$ = $1; }
			|	Iteration_Statement {	$$ = $1; }
			;

Expression_Statement	:	Expression ';'
							{
								$$ = ASTCreateNode(A_EXPRSTMT);
								$$->s1 = $1; //expression
							}

						|	';'
							{
								$$ = ASTCreateNode(A_EXPRSTMT);
							}
						;

Selection_Statement	:	T_IF '(' Expression	')'	Statement
						{
							$$ = ASTCreateNode(A_IF);
							$$->s1 = $3; // if expression
							$$->s2 = ASTCreateNode(AIF_BODY);
							$$->s2->s1 = $5; // if statment
						}

					|	T_IF '(' Expression ')'Statement T_ELSE	Statement
						{
							$$ = ASTCreateNode(A_IF);
							$$->s1 = $3; // if expression
							$$->s2 = ASTCreateNode(AIF_BODY);
							$$->s2->s1 = $5; // if statement
							$$->s2->s2 = $7; // else statment

						}
					;

Iteration_Statement	:	T_WHILE	'(' Expression ')'	Statement
						{
							$$ = ASTCreateNode(A_ITERATE);
							$$->s1 = $3; // while expression
							$$->s2 = ASTCreateNode(AWHILE_BODY);
							$$->s2->s1 = $5; // while statement
						}
					;
Return_Statement	:	T_RETURN	Expression ';'
						{
							$$ = ASTCreateNode(A_RETURN);
							$$->s1 = $2; //expression
						}

					|	T_RETURN	';'
						{
							$$ = ASTCreateNode(A_RETURN);
						}
					;
Read_Statement	:	T_READ	Var	';'
					{
						$$ = ASTCreateNode(A_READ);
						$$->s1 = $2; //s1 connect var to read
					}
				;

Write_Statement	:	T_WRITE Expression ';' 
				{
					$$ = ASTCreateNode(A_WRITE);
					$$->s1 = $2; // s1 expression
				}
				
				| T_WRITE	T_STRING ';'    
				{
					$$ = ASTCreateNode(A_WRITE);
					$$->label = generateLabel();
					$$->name = $2; //give string name for Write node
				}
				;

Assignment_Statement	:	Var '='	Simple_Expression	';'
							{
								if($1->my_data_type != $3->my_data_type) {
									yyerror("TyP3 mismatch");
									exit(1);
								}

								$$ = ASTCreateNode(A_ASSIGN);
								$$->s1 = $1; // s1 var to be assigned
								$$->operator = A_EQ; // give assign node =
								$$->s2 = $3; // s2 expression to assign
								$$->name = CreateTemp();
								$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
								OFFSET = OFFSET + 1;
							}
						;

Var	:	T_ID	
		{
			struct SymbTab *p;
			p = Search($1,LEVEL, 1);
			if(p == NULL){
				//not in symbol table
				yyerror($1);
				yyerror("Symbol used but not defined");
				exit(1);
			}

			if(p->SubType != SYM_SCALAR){
				//not a scalar type
				yyerror($1);
				yyerror("SYMBOL IS NOT A SCALAR");
				exit(1);
			}

			$$ = ASTCreateNode(A_VAR);
			$$->name = $1;
			$$->symbol = p;
			$$->my_data_type = p->Declared_Type;
		}

	|	T_ID	'['Expression']' 
		{
			struct SymbTab *p;
			p = Search($1, LEVEL, 1);
			if(p == NULL){
				yyerror($1);
				yyerror("Symbol Used But Not Defined for Array");
				exit(1);
			}
			if(p->SubType != SYM_ARRAY){
				yyerror($1);
				yyerror("Symbol is not an ARRAY");
				exit(1);
			}
			$$ = ASTCreateNode(A_VAR);
			$$->name = $1;
			$$->s1 = $3;
			$$->value = 77; //specifiy that var is array. 
			$$->symbol = p;
		}
	;

Expression	:	Simple_Expression {  $$ = $1; }
			;

Simple_Expression	:	Additive_Expression {$$ = $1;}
					|	Additive_Expression	Relop	Additive_Expression{
									if($1->my_data_type != $3->my_data_type) {
										yyerror("type MISMATCHED");
										exit(1);
									}
									$$ = ASTCreateNode(A_EXPR);
									$$->s1 = $1; //s1 connect left most expression
									$$->s2 = $3; // s2 connect right most expresstion
									$$->operator = $2; // operator to assign
									$$->name = CreateTemp();
									$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
									OFFSET = OFFSET + 1;
									$$->my_data_type = $1->my_data_type;
								}
					;

Relop	:	T_GE { $$ = A_GE; }
		|	T_LT { $$ = A_LT; }
		|	T_GT { $$ = A_GT; }
		|	T_LE { $$ = A_LE; }
		|	T_EQ { $$ = A_EQ; }
		|	T_NE { $$ = A_NE; }
		;

Additive_Expression	:	Term 
						{		
							$$ = $1;
						}	
					|	Additive_Expression Addop Term
						{
							if($1->my_data_type != $3->my_data_type)	{
								yyerror("type is mismatched");
								exit(1);
							}	
							$$ = ASTCreateNode(A_EXPR);
							$$->s1 = $1; //additive expression
							$$->operator = $2;
							$$->s2 = $3; //term
							$$->name = CreateTemp();
							$$->my_data_type = $1->my_data_type;
							$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
							OFFSET = OFFSET + 1;
						}
					;

Addop	:	T_ADD
			{
				$$ = A_PLUS;
			}
		|	T_SUB
			{
				$$ = A_SUB;
			}
		;

Term	:	Factor 
			{
				$$ = $1;
			}
		|	Term	Multop	Factor 
			{
				if($1->my_data_type != $3->my_data_type) {
					yyerror("Type mismatch term");
					exit(1);
				}
				
				$$ = ASTCreateNode(A_EXPR);
				$$->s1 = $1; //term
				$$->operator = $2;
				$$->my_data_type = $1->my_data_type;
				$$->s2 = $3;  //factor
				$$->name = CreateTemp();
				$$->symbol = Insert($$->name, $$->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
				OFFSET = OFFSET + 1;
			}
		;

Multop	:	T_MULT
			{
				$$ = A_TIMES;
			}
		|	T_DIV
			{
				$$ = A_DIV;
			}
		|   T_MOD
			{
				$$ = A_MOD;
			}
		;

Factor	:	'(' Expression	')' 
				{
					$$ = $2; 	
				}
		|	T_NUM 
				{
					$$ = ASTCreateNode(A_NUM);
					$$->value = $1;	
					$$->my_data_type = A_INTTYPE;
				}
		|	Var 
		 		{	
					$$ = $1;
				}
		|	Call 	
				{
					$$ = $1;
				}
		|	T_SUB Factor
				{
					if($2->my_data_type != A_INTTYPE) {
						yyerror("Type mismatch unary minus");
						exit(1);
					}

					$$ = ASTCreateNode(A_EXPR);
					$$->operator = A_UMINUS;
					$$->s1 = $2; // factor
					$$->name = CreateTemp();
					$$->my_data_type = A_INTTYPE;
					$$->symbol = Insert($$->name, $2->my_data_type, 
					SYM_SCALAR, LEVEL, 1, OFFSET);

				}
		;

Call	:	T_ID	'('	Args	')' 
				{ 
					struct SymbTab *p;
					p = Search($1,0,0);
					if(p ==NULL)	{
						yyerror($1);
						yyerror("function call not known");
						exit(1);
					}

					if(p->SubType != SYM_FUNCTION)	{
						yyerror($1);
						yyerror("not defined as function");
						exit(1);
					}
					//check if formal and actual parameters are same
					if(check_params($3,	p->fparms) == 0)	{
						yyerror($1);
						yyerror("Actuals and Formals do not Match");
						exit(1);
					}
					$$ = ASTCreateNode(A_CALL);
					$$->name = $1;
					$$->s1 = $3; //args list   
					$$->symbol = p;
					$$->my_data_type = p->Declared_Type;
				}
		;

Args	:	Arg_List
			{
				$$ = $1;
			}
		|	/*empty*/
			{

			}
		;

Arg_List	:	Expression
				{
					
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1; // s1 connect expression for arg node
					$$->name = CreateTemp();
					$$->symbol = Insert($$->name, $1->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					$$->my_data_type = $1->my_data_type;
					OFFSET = OFFSET + 1;
					
				}
			|	Expression	','	Arg_List
				{
					if($1->my_data_type != $3->my_data_type)  {
						yyerror("TYPE mismatch");
						exit(1);
					}
					$$ = ASTCreateNode(A_ARG);
					$$->s1 = $1; //s1 connect expression for arg node
					$$->next = $3; // next connect other expressions. 
					$$->name = CreateTemp();
					$$->symbol = Insert($$->name, $3->my_data_type, SYM_SCALAR, LEVEL, 1, OFFSET);
					$$->my_data_type = $3->my_data_type;
					OFFSET = OFFSET + 1;
				}
			;

%%	/*end of rules*/

/*start of program*/
void main(int argc, char * argv[])
{	
	FILE *fp;
	int i;
	char s[100];
	//option for -d to turn on debug 
	//option for -o next arg is output file name
	for(i=0; i < argc; i++) {
		if(strcmp(argv[i], "-d") == 0) myDebug = 1;
		if(strcmp(argv[i], "-o") == 0) {
			// file input
			strcpy(s,argv[i + 1]);
			strcat(s,".asm");
			/* printf(" File name is %s \n", s); */
		}
	}

	fp = fopen(s, "w");
	if(fp == NULL) { 
		printf("cannot open file %s\n", s);
		exit(1);
	}



	yyparse();
    if(myDebug) printf("\nfinished parsing\n\n\n");
	if(myDebug) Display();
    if(myDebug) printf("\n\n\nASTprint\n\n\n");
	if(myDebug) ASTprint(0,PROGRAM);

	EMIT(PROGRAM, fp);
}
