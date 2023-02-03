#include "../inc/encode.h"

void asmEncode(FILE* infile, FILE* outfile)
{
	const int kBufferSize = 1;
	char buffer[kBufferSize];
	int i = 0;

	while(!feof(infile))
	{
		fread(buffer, kBufferSize, 1, infile);
		
		if(i == 0)
		{
			fprintf(outfile, "dc.b\t");
		}

		fprintf(outfile, "$%02X", (unsigned char) buffer[0]);
  		i++;

		if (i == 16 || feof(infile)) 
		{
    		fprintf(outfile, "\n");
    		i = 0;
  		}
		else 
		{
    		fprintf(outfile, ", ");
  		}
	}
}