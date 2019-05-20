#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 16000
#define REGISTER_SIZE 32

/** Instructions **/
typedef enum
{
	HALT = 0,		 /* 0  -- halt			---	 		:: halts the program 								*/
	DISPLAY = 1,	 /* 1  -- display		reg	 		:: prints the value of the register		  			*/
	PRINT_STACK = 2, /* 2  -- print_stack	num	 		:: prints the indicated number of stack positions	*/
	PUSH = 10,		 /* 10 -- push			reg	 		:: pushes the reg value to stack 					*/
	POP = 11,		 /* 11 -- pop			reg	 		:: pops value from stack to reg			  			*/
	MOV = 12,		 /* 12 -- move         	reg val 	:: copies the second parameters value into reg 		*/
	CALL = 20,		 /* 20 -- call			pos	 		:: calls a subroutine, PUSH next IP & JMP to pos 	*/
	RET = 21,		 /* 21 -- return		---	 		:: returns from the subroutine call & POP in IP 	*/
	JMP = 22,		 /* 22 -- jump			pos	 		:: changes the value of IP with pos 				*/
	JZ = 23,		 /* 23 -- jz			pos	 		:: jumps if the last stack value is <> from 0 		*/
	JPOS = 24,		 /* 24 -- jpos			pos	 		:: jumps if the last stack value is >  then 0 		*/
	JNEG = 25,		 /* 25 -- jneg			pos	 		:: jumps if the last stack value is <  then 0 		*/
	ADD = 30,		 /* 30 -- add			reg reg		:: adds two registers in stack 						*/
	SUB = 31,		 /* 31 -- sub			reg reg 	:: subs two registers in stack 						*/
	MUL = 32,		 /* 32 -- mul			reg reg 	:: multiplicates two registers in stack 			*/
	DIV = 33		 /* 33 -- div			reg reg 	:: devides two registers in stack 					*/
} Instructions;

static const char *LOGS[] = 
{
	"[SUCCESS] Program successfully concluded!",
 	"[ERROR] No option indicated!",
 	"[ERROR] No input file indicated!",
 	"[ERROR] The indicated option is not valid!",
 	"[ERROR] Could not read the indicated file!",
 	"[ERROR] Stack overflow!",
 	"[ERROR] Syntax error!",
 	"[ERROR] Unknown instruction!",
 	"[ERROR] System error!"
};

int IN;
int *INSTRUCTIONS;
unsigned int IP;
unsigned int SP;
int STACK[STACK_SIZE];
int REGISTER[REGISTER_SIZE];

#define FETCH (INSTRUCTIONS[IP])

int bootstrap(char *option, char *filename);
