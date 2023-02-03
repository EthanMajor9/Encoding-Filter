/*
* FILE: asm.c
* PROJECT: A-02 EncodeInput Utility
* FIRST VERSION: 02/01/2023
* PROGRAMMER(s): Ethan Major, Cosmin Matei
* DESCRIPTION: This file contains all function prototypes and constant definitions for the cryptoMagic utility
*/
#include "../inc/encode.h"

// FUNCTION: 	void asmEncode(FILE* infile, FILE* outfile)
// DESCRIPTION: This function takes the input file pointer and output file pointer, reads the input contents and outputs as dc.b assembly instructions to the output
// PARAMETERS:  FILE* infile: File pointer to the input stream
//				FILE* outfile: File pointer to the output stream
// RETURNS: 	None
void asmEncode(FILE* infile, FILE* outfile)
{
	const int kBufferSize = 1;
	char buffer[kBufferSize];
	int i = 0;

	// Loop until the end of file is reached
	while(!feof(infile))
	{
		// Read in a byte at a time
		fread(buffer, kBufferSize, 1, infile);
		
		// Check if the first byte is being read
		if(i == 0)
		{
			// Print out the dc.b instruction to the output
			fprintf(outfile, "dc.b\t");
		}

		// Print the byte read as hex to the output with $ infront of it
		fprintf(outfile, "$%02X", (unsigned char) buffer[0]);

		// Increment i
  		i++;

		// Check if the end of the file or the end of the line has been reached
		if (i == 16 || feof(infile)) 
		{
			// Print a newline character to the output
    		fprintf(outfile, "\n");

			// Reset i counter
    		i = 0;
  		}
		else 
		{
			// Print the comma separating instructions
    		fprintf(outfile, ", ");
  		}
	}
}