#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int helpSwitch = 0;
	int outputFileSwitch = 0;
	int inputFileSwitch = 0;
	int srecSwitch = 0;
	char* infilename = NULL;
	char* outfilename = NULL;
	FILE* infile = NULL;
	FILE* outfile = NULL;

	for(int i = 1; i < argc; i++)
	{
		char c1 = argv[i][0];
		char c2 = argv[i][1];

		if(strcmp(argv[i], "-h") == 0)
		{
			helpSwitch = 1;
			break;
		}
		else if(c1 == '-')
		{
			if(strcmp(argv[i], "-srec") == 0)
			{
				srecSwitch = 1;
			}
			else if(c2 == 'o')
			{
				outputFileSwitch = 1;
				outfilename = argv[i] + 2;
			}
			else if(c2 == 'i')
			{
				inputFileSwitch = 1;
				infilename = argv[i] + 2;
			}
		}
		else
		{
			helpSwitch = 1;
			break;
		}
	}

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
		if(inputFileSwitch == 0)
		{
			infile = stdin;
			if(outputFileSwitch == 0)
			{
				infile = stdout;
			}
		}
		else
		{
			infile = fopen(infilename, "rb");
			if(infile == NULL)
			{
				printf("Error: There was an error opening the file\n");
				exit(-1);
			}
		}

		if(outputFileSwitch == 0 && inputFileSwitch == 1)
		{
			if(srecSwitch == 0)
			{
				strcat(outfilename, ".asm");
			}
			else
			{
				strcat(outfilename, ".srec");
			}
		}
	}

	return 0;
}