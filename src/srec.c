#include "../inc/encode.h"

char* header;
uint8_t headerCount = 15;
uint16_t headerAdd = 0000;
const uint8_t headerData[] = {0x63,0x6F,0x73,0x6D,0x69,0x6E,0x2D,0x65,0x74,0x68,0x61,0x6E};

void srecEncode(FILE* infile, FILE* outfile)
{
    int dataline = 0;

    fprintf(outfile, "S00F0000636F736D696E2D657468616E");
    int checksum = headerCount + headerAdd;

    for(int i = 0; i < 12; i++)
    {
        checksum += headerData[i];
    }
    fprintf(outfile, "%02X\n", (~checksum) & 0xFF);

    char buffer[MAX_BUFFER];
    char* output;
    
    while(!feof(infile))
    {
        fread(buffer, MAX_BUFFER, 1, infile)
        encode_srec(0, buffer, strlen(buffer), &output);
        fprintf(outfile, "%s", output);
    }

    fprintf(outfile, "S50300%02d", dataline);
    checksum = 3 + dataline;
    fprintf(outfile, "%02X", (~checksum) & 0xFF);

    fprintf(outfile, "S9030000FC");
}

void encode_srec(int address, char data[MAX_SREC_LENGTH], int length, char *output)
{
    int checksum = 0;
    int count = length + 3;

    sprintf(output, "S1%02X%04X", count, address);
    checksum = count + address;

    for (int i = 0; i < length; i++) {
        sprintf(output + 7 + (i * 2), "%02X", data[i]);
        checksum += data[i];
    }

    sprintf(output + 7 + (length * 2), "%02X\n", (~checksum) & 0xFF);
}