#include "../inc/encode.h"

// our names (cosmin-ethan) in hex values
const uint8_t headerData[] = {0x63,0x6F,0x73,0x6D,0x69,0x6E,0x2D,0x65,0x74,0x68,0x61,0x6E};

void srecEncode(FILE* infile, FILE* outfile)
{
    // the address, is incremented by 16 bits
    int addline = 0;
    // the number of lines of data
    int dataline = 0;
    // the total count for the header is our names (12) plus the address (2) plus the checksum (1)
	int headerCount = 15;
    // the address starts at 0
	int headerAddress = 0;
	
    fprintf(outfile, "S00F0000636F736D696E2D657468616E");
    // calculating the header checksum, count + address + all data
    int checksum = headerCount + headerAddress;

    for(int i = 0; i < 12; i++)
    {
        checksum += headerData[i];
    }
    fprintf(outfile, "%02X\n", (~checksum) & 0xFF);

    // reading the file until it reaches the end
    while(!feof(infile))
    {
        char buffer[MAX_BUFFER] = "";
        // reading in 1 byte up to 16 times to fill the buffer
        size_t bytes = fread(buffer, 1, MAX_BUFFER, infile);
        // calling the s1 encoding function which returns a string
        char *outbuffer = encode_srec(addline, buffer, bytes);
        fprintf(outfile, "%s", outbuffer);
        // incrementing the address by 16 and the number of data lines by 1
        addline += 16;
        dataline += 1;
        free(outbuffer);
    }

    // printing out the summation line
    fprintf(outfile, "S503%04X", dataline);
    checksum = 3 + dataline;
    fprintf(outfile, "%02X\n", (~checksum) & 0xFF);

    // printing out the trailer line
    fprintf(outfile, "S903%04XFC", headerAddress);
}

char* encode_srec(int address, char data[MAX_SREC_LENGTH], int length)
{
    char* output;
    int checksum = 0;
    // the count is the length of data plus the address (2) and the checksum (1)
    int count = length + 3;
    // the out size is twice the size of the data plus the address (4), s1 (2), count (2), checksum (2) and a newline character (1)
    int output_size = (length * 2) + 11;
    output = malloc(output_size);

    sprintf(output, "S1%02X%04X", count, address);
    checksum = count + address;

    // iterate through the data and adding it to the output string after the first 8 chars (S1, count, address)
    for (int i = 0; i < length; i++) {
        sprintf(output + 8 + (i * 2), "%02X", data[i]);
        checksum += data[i];
    }

    sprintf(output + 8 + (length * 2), "%02X\n", (~checksum) & 0xFF);

    return output;
}