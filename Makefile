all: lab9

lab9:   ast.c ast.h emit.c emit.h symtable.c symtable.h lab9.l lab9.y 
		lex lab9.l 
		yacc -d lab9.y
		gcc ast.c symtable.c emit.c y.tab.c lex.yy.c -o lab9

clean: 	lab9
		rm -f lab9

