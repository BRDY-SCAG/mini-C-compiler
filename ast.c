/*   Abstract syntax tree code

     This code is used to define an AST node, 
    routine for printing out the AST
    defining an enumerated type so we can figure out what we need to
    do with this.  The ENUM is basically going to be every non-terminal
    and terminal in our language.

    Brady Scaggari February 27, 2024 LAB 6

    This program is designed to create Nodes of enumerated types, to be more specific types of Nodes that will be used in a program grammar.
      for example Var nodes, expressions, numbers, statements, etc.
    each node created is given a pointer p, and the pointer node p contains pointers to an s1, s2 and next node. 
    each node has a value. and a type. The type for each node is a struct that contains its type of node and other values like an operator or name or value. see ast.h for more.

    implemented Pt(howmany) , helps prints how many spaces required for syntax.

    AST type to String , converts enum AST_MY_DATA_TYPE my type A_INTTYPE or A_VOIDTYPE

    ASTprint , given the SDSA from yacc structure a format to print out or Abstract syntax tree. 
    uses recursive logic to print s1s, s2s, names, values and next nodes in which out AST is structured.

    this source code prints output correctly for both input test cases. test.c and test2.c

*/

#include<stdio.h>
#include<malloc.h>
#include "ast.h" 


/* uses malloc to create an ASTnode and passes back the heap address of the newley created node */
//  PRE:  Ast Node Type
//  POST:   PTR To heap memory and ASTnode set and all other pointers set to NULL
ASTnode *ASTCreateNode(enum ASTtype mytype)

{
    ASTnode *p;
    if (myDebug) fprintf(stderr,"Creating AST Node \n");
    p=(ASTnode *)malloc(sizeof(ASTnode));
    p->type=mytype;
    p->s1=NULL;
    p->s2=NULL;
    p->next=NULL;
    p->symbol = NULL;
    p->value=0;
    return(p);
}

/*  Helper function to print tabbing */
//PRE:  Number of spaces desired
//POST:  Number of spaces printed on standard output

void PT(int howmany)
{
	 if(howmany >= 1){
    for(int i =0; i < howmany; i++){
      printf(" ");
    }
   }
}

//  PRE:  A declaration type
//  POST:  A character string that is the name of the type
//          Typically used in formatted printing
char * ASTtypeToString(enum AST_MY_DATA_TYPE mytype)
{
   switch (mytype)
   {
   case A_INTTYPE:
    return "int";
    break;
   case A_VOIDTYPE:
    return "void";
    break;
   
   default:
    break;
   } 

}



/*  Print out the abstract syntax tree */
// PRE:   PRT to an ASTtree
// POST:  indented output using AST order printing with indentation

void ASTprint(int level,ASTnode *p)
{
   int i;
   if (p == NULL ) return;
   else
     { 
       switch (p->type) {
        case A_VARDEC :
                    if(p->value > 0){
                      PT(level); printf("Variable %s %s [%d] level: %d offset: %d", ASTtypeToString(p->my_data_type), p->name, p->value,
                      p->symbol->level, p->symbol->offset);
                      printf("\n");
                      ASTprint(level, p->s1);
                      ASTprint(level, p->next);
                    }
                    else { 
                      PT(level); printf("Variable %s %s level: %d offset: %d",ASTtypeToString(p->my_data_type), p->name,
                      p->symbol->level, p->symbol->offset);
                      printf("\n");
                      ASTprint(level, p->s1);
                      ASTprint(level, p->next);
                    }
                    break;
        case A_FUNCTIONDEC :  
                            PT(level); printf("Function %s %s level: %d offset: %d",ASTtypeToString(p->my_data_type), p->name,
                            p->symbol->level, p->symbol->offset);
                            printf("\n");
                            ASTprint(level + 1, p->s1); //params
                            ASTprint(level + 1, p->s2); // compound
                            ASTprint(level, p->next);
                          break;
        case A_COMPOUND:
                        PT(level); printf("Compound Statement \n");
                        ASTprint(level + 1, p->s1); //local decls
                        ASTprint(level + 1, p->s2); // statement list
                        ASTprint(level, p->next);
                      break;

        case A_WRITE:
                        PT(level);
                          if(p->name != NULL){ //string
                            PT(level); printf("Write String %s\n", p->name);
                          }
                          else{ // expression
                            printf("Write Expression\n");
                            ASTprint(level+1, p->s1);

                          }
                        ASTprint(level, p->next);
                        break;
        case A_NUM:     
                        PT(level);
                        printf("Num value %d \n",p->value );
                        break;
        case A_EXPR:     
                        PT(level);
                        printf("Expression operator ");
                        switch(p->operator){
                          case A_PLUS:
                            printf("+\n");
                            break;
                          case A_SUB:
                            printf("-\n");
                            break;
                          case A_TIMES:
                            printf("*\n");
                            break;
                          case A_DIV:
                            printf("/\n");
                            break;
                          case A_MOD:
                            printf("%\n");
                            break;
                          case A_EQ:
                            printf("==\n");
                            break;
                          case A_LE:
                            printf("<= \n");
                            break;
                          case A_GE:
                            printf(">=\n");
                            break;
                          case A_GT:
                            printf(">\n");
                            break;
                          case A_LT:
                            printf("<\n");
                            break;
                          case A_NE:
                            printf("!=\n");
                            break; 
                          case A_UMINUS:
                            printf("UMINUS\n");
                            break;  
                          default:
                            printf("unknown operator \n");
                        }//of switch
                        ASTprint(level +1, p->s1); //additive expression
                        ASTprint(level +1, p->s2); //term
                        break;
        case A_VAR:
                        PT(level);
                        if(p->s1 != NULL && p->value > 0){
                          printf("Variable %s level: %d offest: %d \n",p->name, p->symbol->level, p->symbol->offset);
                          PT(level+1);
                          printf("[\n");
                          ASTprint(level+2,p->s1);
                          PT(level + 1);
                          printf("]\n");
                        }
                        else if(p->s1 != NULL){
                          printf("Variable %s level: %d offest: %d \n",p->name, p->symbol->level, p->symbol->offset);
                          ASTprint(level+1, p->s1);
                        }
                        else{
                          printf("Variable %s level: %d offest: %d \n",p->name, p->symbol->level, p->symbol->offset);
                        }
                        // ASTprint(level, p->next);                   
                        break;
        case A_READ:
                      PT(level);
                          printf("Read Var\n");
                          ASTprint(level+1, p->s1);
                        break;
        case A_IF:    
                      PT(level); printf("IF STATEMENT\n");
                      PT(level+1); printf("IF EXPRESSION\n");
                      ASTprint(level + 1, p->s1);
                      ASTprint(level + 1, p->s2);
                      
                      printf("\n");
                      ASTprint(level, p->next);
                      break;
        case AIF_BODY:
                      PT(level);
                      printf("IF BODY\n");
                      ASTprint(level+1, p->s1);
                    if(p->s2 != NULL){
                      PT(level);
                      printf("else statment\n");
                      ASTprint(level+1, p->s2);
                    }
                    printf("\n");
                    break;
        case A_ASSIGN:
                      PT(level); printf("assignment statement\n");
                      ASTprint(level,p->s1);
                      PT(level); printf("= \n");
                      ASTprint(level, p->s2);
                      printf("\n");
                      break;
        case A_ITERATE:
                      PT(level); printf("WHILE STATEMENT\n");
                      PT(level+1); printf("WHILE Expression\n");
                      ASTprint(level+1, p->s1);
                      ASTprint(level+1, p->s2);
                      ASTprint(level,p->next);
                      printf("\n");
                      break;
        case AWHILE_BODY:
                      PT(level); printf("while body\n");
                      ASTprint(level+1, p->s1);
                      printf("\n");
                      break;
        case A_RETURN:
                      PT(level); printf("RETURN STATEMENT\n");
                      ASTprint(level+1,p->s1);
                      ASTprint(level, p->next);
                      break;    
        case A_PARAM:
                      printf("PARAMETER ");
                        if(p->value > 0){
                          PT(level);printf("Parameter %s %s [] ", ASTtypeToString(p->my_data_type), p->name);
                          printf("\n");
                          ASTprint(level, p->next);
                        }
                        else{
                          PT(level);printf("Paramater %s %s ", ASTtypeToString(p->my_data_type), p->name);
                          printf("\n");
                          ASTprint(level, p->next);
                        }
                        break;
        case A_ARG: 
                      PT(level); printf("Call ARG\n ");
                      if(p->s1 != NULL){
                        ASTprint(level+1, p->s1);
                      }
                      
                      ASTprint(level, p->next);
                      break;
        case A_CALL: 
                      PT(level); printf("Call function %s(\n", p->name);
                      if(p->s1 != NULL){
                        ASTprint(level+1, p->s1);
                      }
                      if(p->s1 == NULL){
                        PT(level +1);
                        printf("NULL\n");
                      }
                      PT(level + 1);
                      printf(")\n");
                      break;
        case A_EXPRSTMT: 
                      PT(level); printf("expression statment\n");
                      ASTprint(level+1, p->s1);
                      ASTprint(level, p->next);
                      break;
        default: printf("unknown AST Node type %d in ASTprint\n", p->type);


       } // of switch
     }

} // of ast print

//PRE pointers to actuals and formals
//POST 0 if not the same type or length.
int check_params(ASTnode *a, ASTnode *f) {
  
  if(a == NULL  &&  f ==  NULL) 
  {
    return 1;
  }
  
  if(a == NULL || f == NULL) {
    return 0;
  }

  if(a->s1->my_data_type != f->my_data_type)  {
    return 0;
  }

  if(a->my_data_type != f->my_data_type) {
    return 0;
  }

  return 1 * check_params(a->next,f->next);

}

/* dummy main program so I can compile for syntax error independently   
main()
{
}
/* */
