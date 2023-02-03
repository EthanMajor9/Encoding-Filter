#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SREC_LENGTH 32
#define MAX_BUFFER 16

void srecEncode(FILE* infile, FILE* outfile);
void asmEncode(FILE* infile, FILE* outfile);