#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Word* getMainMemory();
int getNthBit(int input, int desired_bit);

void clear_mem(struct Word *);
int btod(char *);
char* dtob(int);
void display_mem();
void load_file(char *);
void user_code();
void print_assembly();
void print_instruction(struct Instruction);

const int mem_size = 4096;
const int word_size = 16;

/*
 * Clears the memory by filling it with 0s
 */

void clear_mem(struct Word *main_memory){
	memset (main_memory, 0, mem_size);
}

/* 
* Converts a binary string into a decimal value
*/

int btod(char *binP){
	int dec = 0;
	int counter = 0;
	for(int i = strlen(binP)-1; i >= 0; i--){
		if(binP[i] == '1'){
			dec += pow(2, counter);
		} else if ((binP[i] != '0') && (strcmp(binP, "stop")!=0)){
			printf("Error: not a binary number\n");
			return -1;
		}
    counter++;
	}
	return dec;
}

/*
 * Returns a string represtenting a binary number
 */

char* dtob(int dec) {
	static char bin[16];
	bin[0] = '\0';
	int i;
	for (i=word_size-1;i>=0;i--){
		int k = dec >> i;
		if (k & 1){
			strcat(bin, "1");
		} else {
			strcat(bin, "0");
		}
	}
	return bin;
}

void display_mem(){
	int i;
	int temp;
	char bin[16];
	for (i=0;i<=mem_size-1;i++){
		printf("%d\t%s\n", i, dtob(getMainMemory(i)->contents));
	}
}

void user_code(){
	char input[16];
	char exit_string[] = "stop";
	int i = 0;
	while (strcmp(exit_string, input)!=0){
		printf("Please enter the next 16 bit instruction in binary\nEnter 'stop' to stop input: ");
		scanf("%s", input);
		while(((btod(input) == -1) || (strlen(input) > 16)) && (strcmp(exit_string, input)!=0)){
			printf("Enter it again: ");
			scanf("%s", input);
		}
		if (strcmp(exit_string, input)!=0){
			getMainMemory(i)->contents = btod(input);
		}
		i++;
	}
}

void load_file(char *file_name){
	FILE *fp;
	fp = fopen(file_name, "r");
	if(fp == NULL) {
		perror("Error opening file");
		return;
	}
	char temp[16];
	int i = 0;
	while (fgets(temp, 17, fp)!=NULL){
		getMainMemory(i)->contents = btod(temp);
		i++;
	}
	
	
	fclose(fp);
}

void print_assembly(){
	struct Instruction instruct;
	char opCode_s[4];
	char operand_s[12];
	instruct.opcode = -1;
	int i;
	int counter = 0;
	while (instruct.opcode != 0){
		strcpy(opCode_s, "");
		strcpy(operand_s, "");
		for (i=15;i>=12;i--){
			if (getNthBit(getMainMemory(counter)->contents, i) == 1){
				strcat(opCode_s, "1");
			} else{
				strcat(opCode_s, "0");
			}
		}
		instruct.opcode = btod(opCode_s);
		for (i=11;i>=0;i--){
			if (getNthBit(getMainMemory(counter)->contents, i) == 1){
				strcat(operand_s, "1");
			} else{
				strcat(operand_s, "0");
			}
		}
		instruct.operand = btod(operand_s);
		print_instruction(instruct);
		counter++;
	}
}

void print_instruction(struct Instruction instruct){
	if (instruct.opcode == 0){
		printf("Halt\n");
	} else if (instruct.opcode == 1){
		printf("Load %d\n", instruct.operand);
	} else if (instruct.opcode == 2){
		printf("Store %d\n", instruct.operand);
	} else if (instruct.opcode == 3){
		printf("Subt %d\n", instruct.operand);
	} else if (instruct.opcode == 4){
		printf("Add %d\n", instruct.operand);
	} else if (instruct.opcode == 5){
		printf("Input\n");
	} else if (instruct.opcode == 6){
		printf("Output\n");
	} else if (instruct.opcode == 7){
		printf("Skipcond\n");
	} else if (instruct.opcode == 8){
		printf("Jump %d\n", instruct.operand);
	}
}