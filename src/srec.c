#include "../inc/encode.h"

const uint8_t headerData[] = {0x63,0x6F,0x73,0x6D,0x69,0x6E,0x2D,0x65,0x74,0x68,0x61,0x6E};

void srecEncode(FILE* infile, FILE* outfile)
{
    int addline = 0;
    int dataline = 0;
	int headerCount = 15;
	int headerAddress = 0;
	
    fprintf(outfile, "S00F0000636F736D696E2D657468616E");
    int checksum = headerCount + headerAddress;

    for(int i = 0; i < 12; i++)
    {
        checksum += headerData[i];
    }
    fprintf(outfile, "%02X\n", (~checksum) & 0xFF);

    while(!feof(infile))
    {
        char buffer[MAX_BUFFER] = "";

        size_t bytes = fread(buffer, 1, MAX_BUFFER, infile);
        char *outbuffer = encode_srec(addline, buffer, bytes);
        fprintf(outfile, "%s", outbuffer);
        addline += 16;
        dataline += 1;
        free(outbuffer);
    }

    fprintf(outfile, "S503%04X", dataline);
    checksum = 3 + dataline;
    fprintf(outfile, "%02X\n", (~checksum) & 0xFF);

    fprintf(outfile, "S9030000FC");
}

char* encode_srec(int address, char data[MAX_SREC_LENGTH], int length)
{
    char* output;
    int checksum = 0;
    int count = length + 3;
    int output_size = (length * 2) + 9;
    output = malloc(output_size);

    sprintf(output, "S1%02X%04X", count, address);
    checksum = count + address;

    for (int i = 0; i < length; i++) {
        sprintf(output + 8 + (i * 2), "%02X", data[i]);
        checksum += data[i];
    }

    sprintf(output + 8 + (length * 2), "%02X\n", (~checksum) & 0xFF);

    return output;
}