/*
* Integer's can store 16 bits
* Using 'bit fields' to define how many bits are held in each variable eg, (int a : 12) for 12 bits.
* Word - 12 bits per address
*/

typedef struct {
	unsigned int operand : 12;
	unsigned int opcode : 4;
}Instruction;

typedef struct{
	int ac: 16;
	int ir: 16;
	int mbr: 16;
	unsigned int pc : 12;
	int mar : 12;

	int output_register;
	int input_register;
}CPU;

typedef struct {
	int contents : 16;
}Word;