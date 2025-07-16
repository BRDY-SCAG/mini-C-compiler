/* emit.h 
*   header file for emit.c
*   Spring 2024 CS370 LAB 9
*
*   INTERFACE file for emit.c 
*   connects to MIPS generating MIPS code routines
*/ 

#ifndef EMIT_H
#define EMIT_H
#include "ast.h"
#define WSIZE 4
#define LOG_WSIZE 2

void EMIT(ASTnode *p, FILE *fp);
void EMIT_GLOBALS(ASTnode *p, FILE *fp);
void EMIT_STRING(ASTnode *p, FILE *fp);
char *generateLabel();
void EMIT_AST(ASTnode *p, FILE *fp);
void emit_expr(ASTnode *p, FILE *fp);
void emit_call(ASTnode *p, FILE *fp);

#endif