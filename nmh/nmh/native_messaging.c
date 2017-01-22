#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

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

void parse_json(char* json, char** key, char** val)
{
	char* json_pre_key = "{\"";
	char* json_post_key = "\":\"";
	char* json_end = "\"}";

	char *temp = strstr(json, json_pre_key);
	int index_key_start = (temp - json) + (int)strlen(json_pre_key);
	temp = strstr(json, json_post_key);
	int index_key_end = temp - json;
	int index_val_start = index_key_end + (int)strlen(json_post_key);
	temp = strstr(json, json_end);
	int index_val_end = temp - json;

	size_t key_length = (size_t)(index_key_end - index_key_start);
	size_t val_length = (size_t)(index_val_end - index_val_start);

	*key = malloc((sizeof(char) * key_length) + sizeof(char));
	*val = malloc((sizeof(char) * val_length) + sizeof(char));

	memcpy(*key, &json[index_key_start], key_length);
	memcpy(*val, &json[index_val_start], val_length);

	(*key)[key_length] = '\0';
	(*val)[val_length] = '\0';
}

int* read_native_message_sudoku()
{
	char bInLen[4];
	read(0, bInLen, 4);

	exit_if_app_is_offline();

	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);

	char* key;
	char* val;

	parse_json(inMsg, &key, &val);

	unsigned int i;
	unsigned int fields = GRID * GRID;
	int *sudoku = malloc(sizeof(int) * fields);

	for (i = 0; i < fields; i++)
	{
		sudoku[i] = val[i] - '0';
	}

	free(inMsg);
	free(key);
	free(val);

	return sudoku;
}

unsigned int read_native_message_skip_solution_count()
{
	unsigned int skip_solution_count;

	char bInLen[4];
	read(0, bInLen, 4);

	exit_if_app_is_offline();

	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);

	char* key;
	char* val;

	parse_json(inMsg, &key, &val);

	skip_solution_count = (unsigned int)strtoumax(val, NULL, 10);

	free(inMsg);
	free(key);
	free(val);

	return skip_solution_count;
}

SetupData *read_native_message_setup_data()
{
	SetupData *data = malloc(sizeof(SetupData));
	data->sudoku = read_native_message_sudoku();
	data->skip_solution_count = read_native_message_skip_solution_count();

	return data;
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