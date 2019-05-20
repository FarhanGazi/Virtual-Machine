#include "vm.h"

/* METHOD used to print all the loaded instructions */
int print()
{
	int currentIP, regA, regB, number, position;
	IP = 0;
	while (IP < (unsigned int) IN)
	{
		switch (FETCH)
		{
		case HALT:
			currentIP = IP;
			printf("[%3d] HALT\n", currentIP);
			IP++;
			break;

		case DISPLAY:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			printf("[%3d] DISPLAY\t R%d\n", currentIP, regA);
			IP++;
			break;

		case PRINT_STACK:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			number = FETCH;
			printf("[%3d] PRINT_STACK\t R%d\n", currentIP, number);
			IP++;
			break;

		case PUSH:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			printf("[%3d] PUSH\t R%d\n", currentIP, regA);
			IP++;
			break;

		case POP:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			printf("[%3d] POP\t R%d\n", currentIP, regA);
			IP++;
			break;

		case MOV:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			number = FETCH;
			printf("[%3d] MOV\t R%d\t %d\n", currentIP, regA, number);
			IP++;
			break;

		case CALL:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			printf("[%3d] CALL\t %d\n", currentIP, position);
			IP++;
			break;

		case RET:
			currentIP = IP;
			printf("[%3d] RET\n", currentIP);
			IP++;
			break;

		case JMP:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			printf("[%3d] JMP\t %d\n", currentIP, position);
			IP++;
			break;

		case JZ:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			printf("[%3d] JZ\t %d\n", currentIP, position);
			IP++;
			break;

		case JPOS:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			printf("[%3d] JPOS\t %d\n", currentIP, position);
			IP++;
			break;

		case JNEG:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			printf("[%3d] JNEG\t %d\n", currentIP, position);
			IP++;
			break;

		case ADD:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			printf("[%3d] ADD\t R%d\t R%d\n", currentIP, regA, regB);
			IP++;
			break;

		case SUB:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			printf("[%3d] SUB\t R%d\t R%d\n", currentIP, regA, regB);
			IP++;
			break;

		case MUL:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			printf("[%3d] MUL\t R%d\t R%d\n", currentIP, regA, regB);
			IP++;
			break;

		case DIV:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			printf("[%3d] DIV\t R%d\t R%d\n", currentIP, regA, regB);
			IP++;
			break;

		default:
			return 7;
			break;
		}
	}
	return 0;
}

/* METHOD used to execute all the instructions loaded */
int execute()
{
	int currentIP, regA, regB, number, position, index;
	IP = 0;
	SP = 0;
	while (IP < (unsigned int) IN)
	{
		switch (FETCH)
		{
		case HALT:
			return 0;
			break;

		case DISPLAY:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE))
				return 8;
			printf("[%3d] $R%d =>>\t {%3d}\n", currentIP, regA, REGISTER[regA]);
			IP++;
			break;

		case PRINT_STACK:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			number = FETCH;
			if (SP < (unsigned int) number)
				return 8;
			for (index = 1; index <= number; index++)
				printf("[%3d] #SP[%d] =>>\t {%3d}\n", currentIP, SP - index, STACK[SP - index]);
			IP++;
			break;

		case PUSH:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE))
				return 8;

			if(SP >= STACK_SIZE)
				return 5;
			
			STACK[SP] = REGISTER[regA];

			SP++;
			IP++;
			break;

		case POP:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE))
				return 8;

			SP--;

			REGISTER[regA] = STACK[SP];

			IP++;
			break;

		case MOV:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			number = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE))
				return 8;
			
			REGISTER[regA] = number;

			IP++;
			break;

		case CALL:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			if (!(position >= 0) || !(position < IN))
				return 8;
			IP++;
			
			STACK[SP] = IP;

			SP++;
			IP = position;
			break;

		case RET:
			currentIP = IP;

			SP--;

			IP = STACK[SP];
			break;

		case JMP:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			if (!(position >= 0) || !(position < IN))
				return 8;

			IP = position;
			break;

		case JZ:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			if (!(position >= 0) || !(position < IN))
				return 8;
			if ((SP > 0) && (STACK[--SP] != 0)){	
				IP = position;
			} 
			else
			{
				IP++;
			}
			break;

		case JPOS:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			if (!(position >= 0) || !(position < IN))
				return 8;
			if ((SP > 0) && (STACK[--SP] > 0)){	
				IP = position;
			} 
			else
			{
				IP++;
			}
			break;

		case JNEG:
			if ((IP + 1) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			position = FETCH;
			if (!(position >= 0) || !(position < IN))
				return 8;
			if ((SP > 0) && (STACK[--SP] < 0)){	
				IP = position;
			} 
			else
			{
				IP++;
			}
			break;

		case ADD:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE) || !(regB >= 0) || !(regB < REGISTER_SIZE))
				return 8;
			
			if(SP >= STACK_SIZE)
				return 5;

			STACK[SP] = REGISTER[regA] + REGISTER[regB];

			SP++;
			IP++;
			break;

		case SUB:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE) || !(regB >= 0) || !(regB < REGISTER_SIZE))
				return 8;
			
			if(SP >= STACK_SIZE)
				return 5;

			STACK[SP] = REGISTER[regA] - REGISTER[regB];

			SP++;
			IP++;
			break;

		case MUL:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE) || !(regB >= 0) || !(regB < REGISTER_SIZE))
				return 8;
			
			if(SP >= STACK_SIZE)
				return 5;

			STACK[SP] = REGISTER[regA] * REGISTER[regB];

			SP++;
			IP++;
			break;

		case DIV:
			if ((IP + 2) == (unsigned int) IN)
				return 6;
			currentIP = IP;
			IP++;
			regA = FETCH;
			IP++;
			regB = FETCH;
			if (!(regA >= 0) || !(regA < REGISTER_SIZE) || !(regB >= 0) || !(regB < REGISTER_SIZE))
				return 8;
			
			if(SP >= STACK_SIZE)
				return 5;

			STACK[SP] = REGISTER[regA] / REGISTER[regB];

			SP++;
			IP++;
			break;

		default:
			return 7;
			break;
		}
	}
	return 0;
}

int bootstrap(char *option, char *filename)
{
	int digit, index, outcome = 0;
	FILE *inputFile;

	if ((strcmp(option, "esegui") != 0) && (strcmp(option, "stampa") != 0))
	{
		return 3;
	}

	inputFile = fopen(filename, "r");

	if (!inputFile)
	{
		return 4;
	}

	fscanf(inputFile, "%*[^0-9]%d%*[^\n]", &IN);
	INSTRUCTIONS = malloc(sizeof(int) * IN);
	index = 0;

	if (!INSTRUCTIONS)
	{
		return 8;
	}
	
	while (fscanf(inputFile, "%*[^0-9]%d%*[^\n]", &digit) && !feof(inputFile))
	{
		INSTRUCTIONS[index] = digit;
		index++;
	}

	if (strcmp(option, "esegui") == 0)
	{
		outcome = execute();
	}
	else if (strcmp(option, "stampa") == 0)
	{
		outcome = print();
	}
	

	fclose(inputFile);
	free(INSTRUCTIONS);

	return outcome;
}