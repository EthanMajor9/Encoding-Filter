#include "../inc/encode.h"

char* header;
uint8_t headerCount = 15;
uint16_t headerAdd = 0000;
const uint8_t headerData[] = {0x63,0x6F,0x73,0x6D,0x69,0x6E,0x2D,0x65,0x74,0x68,0x61,0x6E};

void srecEncode(FILE* in, FILE* out)
{
    int dataline = 0;

    fprintf(out, "S00F0000636F736D696E2D657468616E");
    uint8_t checksum = headerCount + headerAdd;

    for(int i = 0; i < 12; i++)
    {
        checksum += headerData[i];
    }
    fprintf(out, "%02X\n", (~checksum) & 0xFF);

    char buffer[MAX_BUFFER];
    while(fread(buffer, MAX_BUFFER, 1, in) == 1)
    {

    }

    fprintf(out, "S50300%02d", dataline);
    checksum = 3 + dataline;
    fprintf(out, "%02X", (~checksum) & 0xFF);

    fprintf(out, "S9030000FC");
}

void encode_srec(uint16_t address, uint8_t data[MAX_SREC_LENGTH], uint8_t length, char *output)
{
    int i;
    uint8_t checksum = 0;
    uint8_t count = length + 3;

    sprintf(output, "S1%02X%04X", count, address);
    checksum = count + address;

    for (i = 0; i < length; i++) {
        sprintf(output + 7 + (i * 2), "%02X", data[i]);
        checksum += data[i];
    }

    sprintf(output + 7 + (length * 2), "%02X\n", (~checksum) & 0xFF);
}