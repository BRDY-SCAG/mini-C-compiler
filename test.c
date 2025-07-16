# MIPS CODE GENERATE by Compilers class

.data

_L0: .asciiz	 "hello\n"
.align 2
x: .space 4 # global variable
A: .space 400 # global variable
.text


.globl main


main:				# function definition
	move $a1, $sp		# Activation Record carve out copy SP
	subi $a1 $a1 24		# Activation Record carve out copy size of function
	sw $ra , ($a1)		# Store Return address 
	sw $sp 4($a1)		# Store the old Stack pointer
	move $sp, $a1		# Make SP the current activation record




	li $a0, 0		# expression is a constant
	sw $a0 8($sp)		# Assign store RHS temporarily
	la $a0, x		# EMIT Var global variable
	lw $a1 8($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
_L1:			# # WHILE TOP target
	la $a0, x		# EMIT Var global variable
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 12($sp)		# expression store LHS temporarily
	li $a0, 2		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 12($sp)		# expression restore LHS from memory
	slt $a0, $a0, $a1		# #EXPR Lessthan
	beq $a0 $0 _L2		# #WHILE branch out
	la $a0, _L0		# The string address
	li $v0, 4		# About to print a string
	syscall			# call write string


	la $a0, x		# EMIT Var global variable
	lw $a0, ($a0)		# Expression is a VAR
	sw $a0, 16($sp)		# expression store LHS temporarily
	li $a0, 1		# expression is a constant
	move $a1, $a0		# #right hand side needs to be a1
	lw $a0, 16($sp)		# expression restore LHS from memory
	add $a0, $a0, $a1		# #EXPR ADD
	sw $a0 20($sp)		# Assign store RHS temporarily
	la $a0, x		# EMIT Var global variable
	lw $a1 20($sp)		# Assign get RHS temporarily
	sw $a1 ($a0)		# Assign place RHS into memory
	j _L1		# #WHILE Jump back
_L2:			# # End of WHILE 
	li $a0, 0		# RETURN has no specified value set to 0
	lw $ra ($sp)		# restore old environment RA
	lw $sp 4($sp)		# Return from function store SP

	li $v0, 10		# Exit from Main we are done
	syscall			# EXIT everything

			# END OF FUNCTION
