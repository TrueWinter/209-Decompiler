#include <stdio.h>
#include "structs.c"
#include "auxiliary_f.c"


/*
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



int main() {
	clear_mem(getMainMemory(0));
	display_mem();
	return 0;
}



/*
* Functions
*/

int getNthBit(int input, int desired_bit) {
	return (input >> desired_bit) & 1;
}

/*
* Returns a pointer to the specified memory location
*/
struct Word* getMainMemory(int location) {
	return &main_memory[location];
}
