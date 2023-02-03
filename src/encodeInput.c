/*
* FILE: encodeInput.c
* PROJECT: A-02 EncodeInput Utility
* FIRST VERSION: 02/01/2023
* PROGRAMMER(s): Ethan Major, Cosmin Matei
* DESCRIPTION: This file contains all function prototypes and constant definitions for the cryptoMagic utility
*/
#include "../inc/encode.h"

const int kArrSize = 255;

int main(int argc, char* argv[])
{
	int helpSwitch = 0;
	int outputFileSwitch = 0;
	int inputFileSwitch = 0;
	int srecSwitch = 0;
	char infilename[kArrSize];
	char outfilename[kArrSize];
	FILE* infile = NULL;
	FILE* outfile = NULL;

	// Loop through all of the command line arguments
	for(int i = 1; i < argc; i++)
	{
		// Read the first 2 characters of each command line argument
		char c1 = argv[i][0];
		char c2 = argv[i][1];

		// Check if the help switch was entered
		if(strcmp(argv[i], "-h") == 0)
		{
			// Update flag indicating the switch entered
			helpSwitch = 1;

			// Exit the loop
			break;
		}
		// Check if the first character is a -
		else if(c1 == '-')
		{
			// Check for the srec switch
			if(strcmp(argv[i], "-srec") == 0)
			{
				srecSwitch = 1;
			}
			// Check for the outputfile switch
			else if(c2 == 'o')
			{
				outputFileSwitch = 1;

				// Copy the output argument after the first 2 characters to get the filename
				strcpy(outfilename, argv[i] + 2);
			}
			// Check for the input file switch
			else if(c2 == 'i')
			{
				inputFileSwitch = 1;
				strcpy(infilename, argv[i] + 2);
			}
		}
		// Invalid switch entered
		else
		{
			helpSwitch = 1;
			break;
		}
	}

	// If the help switch was entered or an invalid switch was entered, output usage statement and exit
	if(helpSwitch)
	{
		printf("Usage: encodeInput -h -iINPUTFILENAME -oOUTPUTFILENAME -srec\n\n \
			-h: Displays usage information for the encodeInput filter\n\n \
			-iINPUTFILENAME: Name of the input file. If not present program obtains data from standard input\n\n \
			-oOUTPUTFILENAME: Name of the output file. If not present all output will be sent to standard output.\n\n \
			-srec: Specifies the output to be in S-record format. If not present, output will be put into an assembly file\n\n");
	}
	else
	{
		// Check if the inputfile switch is not present
		if(inputFileSwitch == 0) 
		{
			// Set input to standard input (command line)
			infile = stdin;

			// Check if the output file switch was entered, if it was not, set the output to standard output (command line), if it was open a file pointer
			outfile = (outputFileSwitch == 0) ? stdout : fopen(outfilename, "w");
		}
		// Input file switch is present
		else 
		{
			infile = fopen(infilename, "rb");
			if(infile == NULL) 
			{
				printf("Error: There was an error opening the file\n");
				exit(-1);
			}

			// Check if the output file switch was entered, if it was not, open a file pointer using the inputfile name with the appropriately appended extension.
			// if it is present open a file pointer using the supplied name
			outfile = (outputFileSwitch == 0) ? fopen(strcat(infilename, (srecSwitch == 0) ? ".asm" : ".srec"), "w") : fopen(outfilename, "w");
		}
		
		if(outfile == NULL) 
		{
			printf("Error: There was an error opening/creating the file\n");
			exit(-1);
		}

		// If the srec switch is present, encode the output as srec. If not, encode the output as ASM
		(srecSwitch == 0) ? asmEncode(infile, outfile) : srecEncode(infile, outfile);
	}
	return 0;
}