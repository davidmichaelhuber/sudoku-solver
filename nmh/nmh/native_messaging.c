#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "solver.h"
#include "native_messaging.h"

void read_native_message_tick()
{
	char bInLen[4];
	read(0, bInLen, 4);
	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);
	free(inMsg);
}

int* read_native_message_sudoku()
{
	unsigned int i;
	unsigned int fields = GRID * GRID;
	int *sudoku = malloc(sizeof(int) * fields);
	int sudoku_easy[] =	{
							1, 3, 6, 2, 5, 9, 7, 4, 8, 
							7, 2, 5, 4, 1, 8, 9, 3, 6, 
							4, 8, 9, 3, 6, 7, 1, 5, 0, 
							3, 6, 4, 7, 8, 0, 2, 1, 9, 
							5, 1, 8, 6, 9, 2, 3, 7, 4,
							9, 7, 2, 1, 3, 4, 6, 8, 5, 
							2, 4, 0, 5, 7, 6, 8, 9, 3, 
							8, 5, 3, 9, 2, 1, 4, 6, 7, 
							6, 9, 7, 8, 4, 0, 5, 2, 0 
						};

	for (i = 0; i < fields; i++)
	{
		sudoku[i] = sudoku_easy[i];
	}

	return sudoku;
}

void write_native_message(char* text)
{
	char* json_pre = "{\"text\":\"";
	char* json_post = "\"}";

	size_t msg_length = ((sizeof(char)) * (strlen(json_pre) + strlen(text) + strlen(json_post))) + (sizeof(char));
	char* msg = malloc(msg_length);

	strcpy(msg, json_pre);
	strcat(msg, text);
	strcat(msg, json_post);

	msg[msg_length - 1] = '\0';

	unsigned int outLen = strlen(msg);
	char *bOutLen = (char *)&outLen;
	write(1, bOutLen, 4);
	write(1, msg, outLen);
	fflush(stdout);
	free(msg);
}