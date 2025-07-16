// emit.c 
//
// program that generates MIPS code 

// Brady Scaggari 
// Spring 2024 Lab 9
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "emit.h"

#ifndef AST
#define AST
#include "ast.h"
#endif

void EMIT_AST(ASTnode *p, FILE *fp);

int GLABEL = 0;

//PRE pointer to AST, and pointer to file
//POST prints out mips code to pointer file
void EMIT(ASTnode *p, FILE *fp) {

    if(p == NULL) return;
    if(fp == NULL) return;

    fprintf(fp, "#MIPS CODE GENERATED HEADER CS370\n\n");
    fprintf(fp, ".data\n\n");

    EMIT_STRING(p, fp);
    fprintf(fp, ".align 2");
    EMIT_GLOBALS(p, fp);
    fprintf(fp, "\n.text\n");
    fprintf(fp, ".globl main\n\n");
    EMIT_AST(p, fp);

}



//PRE possible label, command, comment
//POST formatted output to the file
void emit(FILE *fp, char * label, char * command, char * comment)   {

        fprintf(fp, "%s\t%s\t#%s\n", label, command, comment);

}

//PRE pointer to a VAR node
//POST $a0 has exact memory location for the value of VAR
void emit_var(ASTnode *p, FILE *fp) {

    char s[100];
    printf("entered emit var\n");
    printf("%d\n", p->value);
    if(p->s1 != NULL) {
        switch (p->s1->type)
        {
        case A_NUM:
            sprintf(s, "li $a0, %d", p->s1->value);
            emit(fp, "", s, "VAR is a number");
            emit(fp, "", "move $a1, $a0", "make a copy of the index");
            emit(fp, "", "move $a1, $a0", "VAR copy index array in a1");
            sprintf(s, "sll $a1 $a1 %d", LOG_WSIZE);
            emit(fp, "", s, "mult the index by the wordsize");
            break;
        
        case A_EXPR: 
            emit_expr(p->s1, fp);
            sprintf(s, "lw $a0 %d($sp)", p->symbol->offset * WSIZE);
            emit(fp, "", "move $a1, $a0", "var copy index array in a1");
            sprintf(s,"sll $a1, $a1, %d", LOG_WSIZE);
            emit(fp, "", s, "multiply index by 4");
            break;
        
        case A_VAR:
            emit_var(p->s1,fp);
            emit(fp, "", "lw $a0 ($a0)", "get value from identifier");
            emit(fp, "", "move $a1, $a0", "var copy index array in a1");
            sprintf(s,"sll $a1, $a1, %d", LOG_WSIZE);
            emit(fp, "", s, "multiply index by 4");
            break;

        default:
            printf("we should never be here");
            exit(1);
            break;
        }
    }

    if(p->symbol->level == 0) {
        sprintf(s, "la $a0, %s", p->symbol->name);
        emit(fp,"", s, "load global variables from data segment");   
    }
    else {
        emit(fp, "", "move $a0 $sp", "take a copy of the stack pointer");
        sprintf(s, "addi $a0, $a0, %d", p->symbol->offset * WSIZE);
        emit(fp, "", s, "load from code segment");
    }
        if(p->s1 != NULL) {
            emit(fp,"", "add $a0, $a0, $a1", "add on a1 to the array reference");
        }

}

//PRE pointer to A_WRITE NODE
//POST MIPS CODE to generate write string or write and expression compute
void emit_write(ASTnode *p, FILE *fp) {

    char s[100];

    if(p->name != NULL) {
        sprintf(s, "la $a0, %s", p->label);
        emit(fp, "", s, "The string address");
        emit(fp, "", "li $v0, 4", "About to print a string");
        emit(fp, "", "syscall", "call write to string");
        fprintf(fp, "\n\n");

    }
    else {
        //expression
        emit_expr(p->s1, fp);
        emit(fp, "", "li $v0, 1", "About to print a number");
        emit(fp, "", "syscall", "call to write a number");
        fprintf(fp, "\n\n");
        
    }
} // of emit write

//Pre pointer to A_READ node
// Post MIPS code that generates Reading(storing) a variable;
void emit_read(ASTnode *p, FILE *fp) {

	emit_var(p->s1, fp);
	emit(fp, "", "li $v0, 5", "about to read in value");
	emit(fp, "", "syscall", "read in value");
	emit(fp, "", "sw $v0, ($a0)","store the read in value");
	fprintf(fp,"\n\n");

} // of emit read

//PRE PTR to top of AST and file pointer to print to 
//POST prints MIPS global variables in correct location of fp
void EMIT_GLOBALS(ASTnode *p, FILE *fp) {

    if(p == NULL) {
        return;
    }
    if(fp == NULL) return;

    if((p->type == A_VARDEC) && (p->symbol->level == 0)) {
        fprintf(fp, "\n%s: .space %d", p->symbol->name, p->symbol->mysize * WSIZE);
    }
    EMIT_GLOBALS(p->s1, fp);
    EMIT_GLOBALS(p->next, fp);
    
}

//PRE pointer to top of ASTm and file Pointer to print
//POST Adds a label into the ast for use in write statement
// POST prints MIPS code based string into the file 
void EMIT_STRING(ASTnode *p, FILE *fp) {

    if(p == NULL) {return;}

    if((p->type == A_WRITE) && (p->name != NULL)){
        // printf("here\n");
        // printf("%s\n", p->label);
        // printf("%s\n", p->name);
        fprintf(fp,"%s: .asciiz %s \n", p->label, p->name);

    }
    EMIT_STRING(p->s1, fp);
    EMIT_STRING(p->s2, fp);
    EMIT_STRING(p->next, fp);
}

//pre: yacc calls from p->label to generate a label
//post: generates MIPS code in .data section the label of p->name(name of string).
char *generateLabel() {

    char hold[100];
    char *s;
    sprintf(hold, "_L%d", GLABEL++);
    s = strdup(hold);
    return s;
}

//Pre pointer to expression node
//POST MIPS code that sets the answer of expression to $a0
void emit_expr(ASTnode *p, FILE *fp) {

    char s[100];

    // printf("entered emit expression\n");
    // printf("%d\n", p->value);

    switch (p->type)
    {
    case A_NUM:
        sprintf(s, "li $a0, %d", p->value); 
        emit(fp, "", s, "expression is a constant int");
        // printf("HHEre\n");
        return;
        break;
    
    case A_EXPR:
        emit_expr(p->s1, fp);
        sprintf(s, "sw $a0, %d($sp)", p->symbol->offset * WSIZE);
        emit(fp, "", s, "lhs is an expression");
        if(p->s2 != NULL) emit_expr(p->s2, fp); 
// logic for unary minus. THis is because its the only expression not s2 connected. 
        emit(fp, "","move $a1, $a0", "rhs of an expression");
        sprintf(s, "lw $a0, %d($sp)", p->symbol->offset * WSIZE);
        emit(fp, "", s, "lhs from memory stack pointer");
        break;

    case A_CALL: 
        emit_call(p, fp);
        // emit(fp, "", "lw $a0 $v0 0", "copy return function value to a0");
        printf("inside call from expr\n");
        break;

    case A_VAR:
        emit_var(p,fp); // a0 is location in memory
        emit(fp,"", "lw $a0, ($a0)", "Expression is a var");
        // printf("hEEre\n");
        return;
        break;

        break;
    default:
        printf("should never be here\n");
        // printf("here\n");
        exit(1);
        break;
    }// of switch for lhs

    // emit(fp, "", emit_stack("sw $a0", p->symbol->offset), "store the lhs into memory");
   

    switch (p->operator)
    {
    case A_PLUS:
        emit(fp, "", "add $a0 $a0, $a1", "add and expression");
        return;
        break;

    case A_SUB:
        emit(fp, "", "sub $a0 $a0, $a1", "subtract an expression");
        return;
        break;

    case A_TIMES:
        emit(fp, "", "mult $a0 $a1","multiply left and right");
        emit(fp, "", "mflo $a0", "multiply expression");
        return;
        break;

    case A_DIV:
        emit(fp, "", "div $a0, $a1","divide the expression");
        emit(fp, "", "mflo $a0", "dividion expression");
        return;
        break;

    case A_LE:
        emit(fp, "", "add $a1, $a1, 1","Less than EQUAL EXPRESSION");
        emit(fp, "", "slt $a0, $a1, $a0", "LESS THAN EXPRESSION");
        return;
        break;

    case A_GT:
        emit(fp, "", "slt $a0, $a0, $a1", "greater than expression");
        return;
        break;

    case A_GE:
        emit(fp, "", "add $a1, $a1, 1","GREATER than EQUAL EXPRESSION");
        emit(fp, "", "slt $a0, $a1, $a0", "greater than equal expression");
        return;
        break;
    
    case A_EQ:
        emit(fp, "", "slt $t2, $a0, $a1", "equal expression");
        emit(fp, "", "slt $t3, $a1, $a0", "equal expression");
        emit(fp, "", "nor $a0, $t2, $t3", "equal expression");
        emit(fp, "", "andi $a0, 1", "EQUAL EXPRESSION");
        return;
        break;

    case A_NE:
        emit(fp, "", "slt $t2, $a0, $a1", "not equal expression");
        emit(fp, "", "slt $t3, $a1, $a0", "not equal expression");
        emit(fp, "", "or $a0, $t2, $t3", "not equal expression");
        return;
        break;

    case A_LT:
        emit(fp, "", "slt $a0, $a0, $a1", "less than expression");            
        return;
        break;
    case A_UMINUS:
        emit(fp, "", "li $t0, 0", "loading unary minus holder");
        emit(fp, "" ,"sub $a0, $t0, $a0", "UNARY MINUS IMPLEMENTATION");   
        return;
        break;
    default:
        printf("error inside of expression operator\n");
        exit(1);
        break;
    }

} // of emit expression

//PRE pointer to an ASTnode function dec
//Post mips code into file
void emit_function(ASTnode *p, FILE *fp) {

    char s[100];
    ASTnode *f;
    f = p->s1;
    int i = 0;
    emit(fp, strcat(p->name, ":"), "", "function declaration");
    
    //carve out the activation record for the given function
    emit(fp, "", "move $a1, $sp", "ACtivation record carve out copy sp");
    sprintf(s, "subi $a1, $a1, %d", p->symbol->offset * WSIZE);
    emit(fp, "", s, "Activation carve out size of function");
    emit(fp, "", "sw $ra, ($a1)", "Store return address");
    sprintf(s, "sw $sp %d($a1)", WSIZE);
    emit(fp, "",s , "Store the old stack pointer");
    emit(fp, "","move $sp, $a1" , "make sp the current activation record");
    fprintf(fp, "\n\n");

    while(f != NULL) {
        sprintf(s, "sw $t%d %d($sp)", i, f->symbol->offset * WSIZE);
        emit(fp, "", s, "parameter store start of function");
        i = i + 1;
        f = f->next;
    }

    EMIT_AST(p->s2, fp);// call to compound statment. 

    //implicit return depending on function
    emit(fp, "", "lw $ra ($sp)", "restore old env RA");
    sprintf(s, "lw $sp %d($sp)", WSIZE);
    emit(fp, "", s, "return from function restore sp");
    fprintf(fp,"\n");

    if(strcmp(p->name, "main:") == 0) {
        //EXIT SYSTEM@ END OF MAIN
        emit(fp, "", "li $v0, 10", "exit from main done");
        emit(fp, "", "syscall", "EXIT PROGRAM");
    }
    else {
        emit(fp, "", "jr $ra", "jump to the other function");
        emit(fp, "", "li $v0, 10", "exit from main done");
        emit(fp, "", "syscall", "EXIT PROGRAM");
    } 

}// of emit function

//PRE pointer to ITERATE NODE
//POST MIPS CODE COMPLETE FOR WHILE LOOP

void emit_while(ASTnode *p, FILE *fp) {
    char *L1, *L2;
    ASTnode *f;
    char s[100];

    L1 = generateLabel();
    L2 = generateLabel();

    sprintf(s, "%s:", L1);
    emit(fp, s, "", "WHILE TOP LABEL");
    emit_expr(p->s1, fp);
    sprintf(s, "beq $a0, $0 %s", L2);
    emit(fp, "", s, "BRANCH EQ GET OUT");

    EMIT_AST(p->s2->s1, fp);

    sprintf(s, "j %s", L1);
    emit(fp, "", s, "jump back till BRANCH EQ");

    emit(fp, strcat(L2, ":"), "", "END OF WHILE");

}// of emit while 

//PRE pointer to ITERATION STATEMENT NODE
//POST MIPS CODE THAT LOGICALLY COMPUTES EXPRESSIOn
void emit_if(ASTnode *p, FILE *fp) {

    char * L1, *L2;
    ASTnode * ptr;
    char s[100];

    L1 = generateLabel();
    L2 = generateLabel();

    emit_expr(p->s1, fp);
    sprintf(s, "beq $a0, $0 %s", L1);
    emit(fp, "", s, "if branch to else");
    EMIT_AST(p->s2->s1, fp);
    sprintf(s, "j %s", L2);
    emit(fp, "", s, "goto L2");
    emit(fp, strcat(L1, ":"), "", "LABEL 1");
    EMIT_AST(p->s2->s2, fp);
    emit(fp, strcat(L2, ":"), "", "LABEL 2");

} // of emit if

//PRE pointer to return STATEMENT NODE
//POST mips code that returns the value computed from the end of function $a0
// if there are no parameters or return is void. $a0 will be 0. 
void emit_return(ASTnode *p, FILE *fp) {

    char s[100];

    if(p->s1 == NULL) {
        emit(fp, "", "li $a0, 0 ", "return zero");
    }
    else {
        emit_expr(p->s1, fp);
    }
}   // of emit return 

//PRE pointer to an AST call node. 
// mips generated code handling the call functionality 
void emit_call(ASTnode *p, FILE *fp) {
    char s[100];
    int i = 0;
    ASTnode *fparms, *args;

    fparms = p->symbol->fparms;
    args = p->s1;

    while (args != NULL)
    {
        emit_expr(args->s1, fp);
        sprintf(s, "sw $a0, %d($sp)\n", args->symbol->offset * WSIZE);
        emit(fp, "", s, "store call arg temporarily");
        args = args->next;
    }
    args = p->s1;
    while(args != NULL)
    {       
        sprintf(s, "lw $a0, %d($sp)", args->symbol->offset * WSIZE);
        emit(fp, "",s , "pull out stored Arg");
        sprintf(s, "move $t%d, $a0", i);
        emit(fp, "", s, "move arg in temp\n");
        i = i + 1;
        args = args->next;
    }
    sprintf(s, "jal %s\n\n", p->name);
    emit(fp, "", s, "call the function");
    
}

//PRE; pointer to an assignment statement box
//POST mips code that assigns variable to express
void emit_assign(ASTnode *p, FILE *fp) {

    char s[100];

    emit_expr(p->s2, fp);

    sprintf(s, "sw $a0 %d($sp)", p->symbol->offset * WSIZE);
    emit(fp, "", s, "");
    emit_var(p->s1, fp);
    sprintf(s, "lw $a1 %d($sp)", p->symbol->offset * WSIZE);
    emit(fp, "", s, "load the expression");
    emit(fp, "", "sw $a1 ($a0)", "assign into memory of var");

}

//Pre pointer to ast node 
//post MIps code into the file for ast
void EMIT_AST(ASTnode *p, FILE *fp) {

    char hold[100];
    int i;

    if(p == NULL) return;

    switch (p->type)
    {
    case A_VARDEC:
        EMIT_AST(p->next, fp);  
        break;
    
    case A_FUNCTIONDEC:
        emit_function(p, fp);  
        EMIT_AST(p->next, fp);
        break;
    
    case A_WRITE:
        emit_write(p, fp);
        EMIT_AST(p->next, fp);  
        break;

    case A_COMPOUND:
        EMIT_AST(p->next, fp);
        EMIT_AST(p->s2, fp);
        break; 
    
    case A_READ:
        emit_read(p,fp);
        EMIT_AST(p->next, fp);
        break;

    case A_ASSIGN:
        emit_assign(p, fp);
        EMIT_AST(p->next, fp);
        break;
    
    case A_ITERATE:
        emit_while(p, fp);
        EMIT_AST(p->next, fp);
        break;
    
    case AWHILE_BODY:
        printf("this does nothing shouldn't");
        break;

    case AIF_BODY:
        printf("this does nothing \n");
        break;

    case A_IF:
        emit_if(p, fp);
        EMIT_AST(p->next, fp);
        break;
    
    case A_RETURN:
        emit_return(p,fp);
        EMIT_AST(p->next, fp);
        break;

    case A_CALL:
        emit_call(p, fp);
        break;
    
    case A_EXPRSTMT:
        emit_expr(p->s1, fp);
        break;

    default:
        printf("emit ast case %d not implemented\n", p->type);
        printf("we should never be here\n");
        exit(1);
        break;
    } // of switch

} // of EMIT AST