#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "native_messaging.h"

void read_native_message()
{
	char bInLen[4];
	read(0, bInLen, 4);
	unsigned int inLen = *(unsigned int *)bInLen;
	char *inMsg = (char *)malloc(inLen);
	read(0, inMsg, inLen);
	inMsg[inLen] = '\0';
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