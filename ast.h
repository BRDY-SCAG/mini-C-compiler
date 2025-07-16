/*   Abstract syntax tree code


 Header file   
   Brady Scaggari 2024 March 27. LAB 6. 

   This header file contains the methods from ast.c as well as the enumerations for types of nodes and types of operators for nodes.
      see ast.c for pre and post conditions for all of the methods. 

   When we create an operator using SDSA or a NODE WE NEED THE HEADER TO define these so that in our c code we can print out the structure of our code.
   
   This file is included with the yacc file so yacc knows where to call methods. Most importantly createNode so that we can assemble our AST with SDSA.



 You must add appropriate header code that describes what this does

*/

#include<stdio.h>
#include<malloc.h>

#include"symtable.h"

#ifndef AST_H
#define AST_H
int myDebug;

/* define the enumerated types for the AST.  THis is used to tell us what 
sort of production rule we came across */

enum ASTtype {
   A_FUNCTIONDEC,
   A_VARDEC,
   A_COMPOUND, 
   A_WRITE,
   A_NUM,
   A_EXPR,
   A_VAR,
   A_READ,
   A_IF,
   A_ARG,
   A_CALL,
   AIF_BODY,
   A_ASSIGN,
   A_ITERATE,
   AWHILE_BODY,
   A_RETURN,
   A_PARAM,
   A_EXPRSTMT
	   //missing
};

// Math Operators

enum AST_OPERATORS {
   A_PLUS,
   A_SUB,
   A_TIMES,
   A_MOD,
   A_DIV,
   A_LT,
   A_GT,
   A_GE,
   A_LE,
   A_EQ,
   A_NE,
   A_UMINUS
	   //missing
};

enum AST_MY_DATA_TYPE {
   A_INTTYPE,
   A_VOIDTYPE

};

/* define a type AST node which will hold pointers to AST structs that will
   allow us to represent the parsed code 
*/

typedef struct ASTnodetype
{
     enum ASTtype type;
     enum AST_OPERATORS operator;
     char * name;
     int value;
     char * label;
     enum AST_MY_DATA_TYPE my_data_type;
     struct SymbTab *symbol;
     struct ASTnodetype *s1,*s2, *next ; /* used for holding IF and WHILE components -- not very descriptive */
} ASTnode;


/* uses malloc to create an ASTnode and passes back the heap address of the newley created node */
ASTnode *ASTCreateNode(enum ASTtype mytype);

void PT(int howmany);


/*  Print out the abstract syntax tree */
int check_params(ASTnode *a, ASTnode *f);
void ASTprint(int level,ASTnode *p);

#endif // of AST_H
