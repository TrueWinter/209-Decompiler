#include <stdio.h>
#include "structs.c"
#include "auxiliary_f.c"

/*
* Summary
* A disassembler is a computer program that translates machine language into assembly language.
*/


/*
* Globals
*/

//Declare main CPU. Check 'structs.c' for details.
struct CPU cpu;
struct Word main_memory[4096]; 



/*
* Prototypes
*/

// Returns n'th bit from the input given to it
int getNthBit(int input, int desired_bit); 
struct Word* getMainMemory(); //Access as a pointer so we can use it as a massive long 'word' 
void opCodeFunctions(struct Instruction exInstruct, struct CPU comp, int x); // x will be the decimal version of the instruction, passed in to be added to MAR


int main() {
	clear_mem(getMainMemory(0));
	display_mem();
	return 0;
}



/*
* Functions/Methods
*/

int getNthBit(int input, int desired_bit) {
	return (input >> desired_bit) & 1;
}

struct Word* getMainMemory(int location) {
	return &main_memory[location];
}

void opCodeFunctions (struct Instruction exInstruct, struct CPU comp, int x) {
	for (comp.pc == 0; comp.pc < 1000; comp.pc++) {
		
		comp.ir = main_memory[comp.pc];
		comp.mar = x; 
		comp.mbr = main_memory[comp.mar];
		
		switch(exInstruct.opcode) {
			case 0: break;
			
			case 1: comp.ac = comp.mbr;
			break;
			
			case 2: main_memory[comp.mbr] = comp.ac;
			break;
			
			case 3: comp.ac -= comp.mbr;
			break;
			
			case 4: comp.ac += comp.mbr;
			break;
			
			case 5: 
				printf("Please enter the value you would like to input into the Accumulator \n");
				scanf("%d", &comp.ac);
				comp.input_register = comp.ac;
			break;
			
			case 6:
				comp.output_register = comp.ac;
				printf("The value currently stored in the Accumulator is %d", comp.ac);
			break;
			
			case 7: 
				if (comp.mbr != 1024) {
					comp.pc+=1;
				}
			break;
			
			case -1: comp.pc = comp.mbr;
			default:
				printf("This instruction does not exist: Opcode: %d, Operand: %s",exInstruct.opcode, exInstruct.operand);
				break;
			
			
		}
	}
}