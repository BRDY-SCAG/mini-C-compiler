#MIPS CODE GENERATED HEADER CS370

.data

_L0: .asciiz "hello" 
_L1: .asciiz "\n" 
.align 2
A: .space 400
.text
.globl main

main:		#function declaration
	move $a1, $sp	#ACtivation record carve out copy sp
	subi $a1, $a1, 20	#Activation carve out size of function
	sw $ra, ($a1)	#Store return address
	sw $sp 4($a1)	#Store the old stack pointer
	move $sp, $a1	#make sp the current activation record


	la $a0, _L0	#The string address
	li $v0, 4	#About to print a string
	syscall	#call write to string


	la $a0, _L1	#The string address
	li $v0, 4	#About to print a string
	syscall	#call write to string


	li $a0, 10	#expression is a constant int
	sw $a0 12($sp)	#
	move $a0 $sp	#take a copy of the stack pointer
	addi $a0, $a0, 8	#load from code segment
	lw $a1 12($sp)	#load the expression
	sw $a1 ($a0)	#assign into memory of var
	move $a0 $sp	#take a copy of the stack pointer
	addi $a0, $a0, 8	#load from code segment
	lw $a0, ($a0)	#Expression is a var
	sw $a0, 16($sp)	#lhs is an expression
	li $a0, 1	#expression is a constant int
	move $a1, $a0	#rhs of an expression
	lw $a0, 16($sp)	#lhs from memory stack pointer
	sub $a0 $a0, $a1	#subtract an expression
	li $v0, 1	#About to print a number
	syscall	#call to write a number


	lw $ra ($sp)	#restore old env RA
	lw $sp 4($sp)	#return from function restore sp

	li $v0, 10	#exit from main done
	syscall	#EXIT PROGRAM
