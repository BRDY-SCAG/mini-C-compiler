/*
	Brady Scaggari Feb 27. 2024	LAB 6 from lab 5
	This is the lex file that deals with lexical analysis for out CMINUS+ language. 
	We have tokenized every operator that we need for CMINUS+ and added a couple regular expressions 
	for things like T_ID T_NUM and T_STRING. 
	added comment regular expression to allow comments to work properly and not return anything
	added a line count so that yacc can get the line a syntax error is on
	created T_String for write method so that we can tokenize the string for better context free ruling
*/



%{
int myDebug = 0;
int lineCount = 1;

#include "ast.h"
#include "y.tab.h"
%}

%%

"int"		{ return (T_INT);}
"void"		{ return (T_VOID);}
"read"		{ return (T_READ);}
"write"		{ return (T_WRITE);}
"else"		{ return (T_ELSE);}
"if"		{ return (T_IF);}
"while"		{ return (T_WHILE);}
"return"	{ return (T_RETURN);}
"<"			{return	(T_LT);	}
">"			{return	(T_GT);	}
"<="		{return	(T_LE);	}
">="		{return	(T_GE);	}
"=="		{return	(T_EQ);	}
"*"			{return (T_MULT);}
"/"			{return (T_DIV);}
"+"			{return (T_ADD);}
"-"			{return (T_SUB);}
"%"			{return (T_MOD);}
"!="		{return (T_NE); }



[;()=\-+*/%&|,\[\]{}""] 	{ if (myDebug) fprintf(stderr,"return a token %c\n",*yytext); 
                       return (*yytext);}


[a-zA-Z][a-zA-Z0-9_]*		{if (myDebug) fprintf(stderr,"T_ID found on line: %d\n", lineCount); 
                       yylval.string=strdup(yytext); 
					   return(T_ID);
					}

[0-9][0-9]*	{if (myDebug) fprintf(stderr,"T_NUM found\n"); 
                       yylval.value=atoi((const char *)yytext); 
					   return(T_NUM);
					}

\"[^\"]*\"		{if (myDebug) fprintf(stderr,"T_STRING found\n"); 
                       yylval.string=strdup(yytext); 
					   return(T_STRING);
					}

[ \t]		{if (myDebug) fprintf(stderr,"Whitespace found\n");}
					   
\n 		{ if (myDebug) fprintf(stderr,"cariage return %c\n",*yytext);
						lineCount++;}
				
\/\/[^\n]*		{	if (myDebug) fprintf(stderr,"in comment mode\n"); 
						}



%%

int yywrap(void)
{return 1;}
