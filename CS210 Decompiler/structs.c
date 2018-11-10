/*
* Integer's can store 16 bits
* Using 'bit fields' to define how many bits are held in each variable eg, (int a : 12) for 12 bits.
* Word - 12 bits per address
*/

struct Instruction {
	int operand : 12;
	int opcode : 4;
};

struct CPU {
	int ac;
	int ir;
	int mbr;
	int pc : 12;
	int mar : 12;

	int output_register;
	int input_register;
};

struct Word {
	int contents : 16;
};