/*
* FILE: encode.h
* PROJECT: A-02 EncodeInput Utility
* FIRST VERSION: 02/01/2023
* PROGRAMMER(s): Ethan Major, Cosmin Matei
* DESCRIPTION: This file contains all function prototypes and constant definitions for the encodeInput utility
*/
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_SREC_LENGTH 32
#define MAX_BUFFER 16

void srecEncode(FILE* infile, FILE* outfile);
void asmEncode(FILE* infile, FILE* outfile);
char* encode_srec(int address, char data[MAX_SREC_LENGTH], int length);