#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "solver.h"
#include "native_messaging.h"

void exit_if_app_is_offline()
{
	fseek (stdin, 0, SEEK_END);
	int num = ftell(stdin);

	if (num <= 0)
	{
		exit(0);
	}
}

void read_native_message_tick()
{
	char bInLen[4];
	read(0, bInLen, 4);

	exit_if_app_is_offline();

	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);

	free(inMsg);
}

int* read_native_message_sudoku()
{
	char bInLen[4];
	read(0, bInLen, 4);

	exit_if_app_is_offline();

	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);

	char text[GRID * GRID];
	memcpy(text, &inMsg[11], GRID * GRID);
	text[GRID * GRID] = '\0';

	free(inMsg);

	unsigned int i;
	unsigned int fields = GRID * GRID;
	int *sudoku = malloc(sizeof(int) * fields);

	for (i = 0; i < fields; i++)
	{
		sudoku[i] = text[i] - '0';
	}

	return sudoku;
}

void write_native_message(char* key, char* val)
{
	char* json_pre_key = "{\"";
	char* json_post_key = "\":\"";
	char* json_end = "\"}";

	size_t msg_length = ((sizeof(char)) * 
												(
													strlen(json_pre_key) + 
													strlen(key) +
													strlen(json_post_key) +
													strlen(val) + 
													strlen(json_end)
												)) + (sizeof(char)
											);

	char* msg = malloc(msg_length);

	strcpy(msg, json_pre_key);
	strcat(msg, key);
	strcat(msg, json_post_key);
	strcat(msg, val);
	strcat(msg, json_end);

	msg[msg_length - 1] = '\0';

	unsigned int outLen = strlen(msg);
	char *bOutLen = (char *)&outLen;
	write(1, bOutLen, 4);
	write(1, msg, outLen);
	fflush(stdout);
	free(key);
	free(val);
	free(msg);
}