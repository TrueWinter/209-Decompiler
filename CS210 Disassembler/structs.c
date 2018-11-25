/**************************************************************************
 * Assessment Title: ACE3 Computer
 *
 *
 * Number of Submitted C Files: 3
 *
 * 
 * Date: 25/11/18
 *
 * 
 * Authors: 
 *	1. FRASER BELL, Reg no: 201718540
 *	2. IAN HENDERSON, Reg no: 201707694
 *	3. ROSS WILLIAMSON, Reg no: 201707864
 *	4. MONIKA KORNAZEWSKA, Reg no: 201707759
 * 	5. LAUREN CRONIN, Reg no: 201707491
 * 
 *
 *	Statement: We confirm that this submission is all our own work.
 *
 *      (Signed)FRASER BELL
 *	
 * 	(Signed)IAN HENDERSON
 *	
 *	(Signed)MONIKA KORNAZEWSKA
 *	
 *	(Signed)LAUREN CRONIN
 *
 **************************************************************************/
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