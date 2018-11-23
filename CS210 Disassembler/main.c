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
CPU cpu;
Word main_memory[4096]; 



/*
* Prototypes
*/

// Returns n'th bit from the input given to it
int getNthBit(int input, int desired_bit); 
Word* getMainMemory(); //Access as a pointer so we can use it as a massive long 'word' 
int opCodeFunctions(Instruction exInstruct); // x will be the decimal version of the instruction, passed in to be added to MAR
int fetchExecute();

int main(int argc, char *argv[]) {
	clear_mem(getMainMemory(0));

	
	if (strcmp(argv[1], "-d") == 0){
		load_default();
		fetchExecute();
	}

	if (strcmp(argv[1], "-f") == 0){
		load_file(argv[2]);
		fetchExecute();
	}


	print_assembly();
	display_mem();
	return 0;
}



/*
* Functions/Methods
*/

int getNthBit(int input, int desired_bit) {
	return (input >> desired_bit) & 1;
}

Word* getMainMemory(int location) {
	return &main_memory[location];
}

int opCodeFunctions (Instruction exInstruct) {
	printf("Opcode: %d\n", exInstruct.opcode);

	switch(exInstruct.opcode) {
		case 0: return -1;
			
		case 1:
			cpu.mbr = cpu.mar;
			cpu.ac = getMainMemory(cpu.mbr)->contents;
		break;
		
		case 2: 
			cpu.mbr = cpu.mar;
			getMainMemory(cpu.mbr)->contents = cpu.ac;
		break;
		
		case 3: 
			cpu.mbr = cpu.mar;
			cpu.ac -= getMainMemory(cpu.mbr)->contents;
		break;
		
		case 4: 
			cpu.mbr = cpu.mar;
			cpu.ac += getMainMemory(cpu.mbr)->contents;
		break;
		
		case 5: 
			printf("Please enter the value you would like to input into the Accumulator \n");
			int temp;
			scanf("%d", &temp);
			cpu.ac = temp;
			cpu.input_register = cpu.ac;
		break;
		
		case 6:
			cpu.output_register = cpu.ac;
			printf("The value currently stored in the Accumulator is %d", cpu.ac);
		break;
		
		case 7: 
			if (cpu.mbr != 1024) {
				cpu.pc+=1;
			}
		break;

		
		case -8: 
			cpu.mbr = cpu.mar;
			cpu.pc = cpu.mbr;
		break;
		
		case -7: 
			cpu.mbr = cpu.mar;
			cpu.ac = cpu.ac * cpu.mbr;
		break;
		
		case -6: 
			cpu.mbr = cpu.mar;
			cpu.mbr = cpu.mbr << 2;
		break;
		
		case -5: 
			cpu.mbr = cpu.mar;
			cpu.mbr = cpu.mbr >> 2;
		break;
		
		default:
			printf("This instruction does not exist: Opcode: %d, Operand: %d",exInstruct.opcode, exInstruct.operand);
			return -1;
		
		
	}
	return 0;
}

int fetchExecute(){
	cpu.pc = 0;
	int running = 1;
	while(running){
		cpu.mar = cpu.pc;
		cpu.ir = getMainMemory(cpu.mar)->contents;
		cpu.pc++;
		Instruction instruction = decodeInstruction(cpu.ir);
		cpu.mar = instruction.operand;
		if (opCodeFunctions(instruction) == -1 || cpu.pc > 2046){
			running = 0;
		}
	}
	return 0;
}
