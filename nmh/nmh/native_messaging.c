#ifdef _WIN32
  #define OS 1
  #ifdef _WIN64
    #define OS 1
  #endif
#elif __APPLE__
  #define OS 2
#else
  #define OS 0
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "solver.h"
#include "native_messaging.h"

/* Returns an array representing a sudoku by reading a JSON string from the
Chrome Native Messaging application. The JSON string must look like this:
{"sudoku":"<81 Fields of Sudoku>"} */
int* get_sudoku();

/* Returns the value for the amount of solutions to skip when solving the sudoku
by reading a JSON string from the Chrome Native Messaging application. The JSON
string must look like this: {"skip_solution_count":"<Number>"} */
unsigned int get_skip_solution_count();

/* Reads a JSON string from the Chrome Native Messaging application. The
resulting JSON string is used like a key-value pair, so JSON strings sent by
the Chrome Native Messaging application need to have exactly one key and one
value. Example: {"<key>":"<value>"} */
char* read_native_message();

/* Terminates the native message host if the Chrome Native Messaging application
is offline by checking if the stdin buffer is empty when it should hold data */
void exit_if_app_is_offline();

/* Parses a given json string by extracting the key and value. Due to JSON
strings are used like a key-value pairs within this context the JSON strings
sent by the Chrome Native Messaging application need to have exactly one key and
one value. Example: {"<key>":"<value>"}
The pointer to the JSON string is getting de-allocated within the function. */
void parse_json(char* json, char** key, char** val);

void get_tick()
{
  char* key;
  char* val;
  parse_json(read_native_message(), &key, &val);
}

SetupData *get_setup_data()
{
  SetupData *data = malloc(sizeof(SetupData));
  data->sudoku = get_sudoku();
  data->skip_solution_count = get_skip_solution_count();

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

  free(msg);
}

int* get_sudoku()
{
  char* key;
  char* val;
  parse_json(read_native_message(), &key, &val);

  unsigned int i;
  unsigned int fields = GRID * GRID;
  int *sudoku = malloc(sizeof(int) * fields);

  for (i = 0; i < fields; i++)
  {
    sudoku[i] = val[i] - '0';
  }

  free(key);
  free(val);

  return sudoku;
}

unsigned int get_skip_solution_count()
{
  char* key;
  char* val;
  parse_json(read_native_message(), &key, &val);

  unsigned int skip_solution_count;

  skip_solution_count = (unsigned int)strtoumax(val, NULL, 10);

  free(key);
  free(val);

  return skip_solution_count;
}

char* read_native_message()
{
  char bInLen[4];
  read(0, bInLen, 4);

  exit_if_app_is_offline();

  unsigned int inLen = *(unsigned int *)bInLen;
  char *inMsg = (char *)malloc(inLen);
  read(0, inMsg, inLen);

  return inMsg;
}

void exit_if_app_is_offline()
{
  switch (OS)
  {
    /* No OS detected */
    case 0:
      exit(0);
    /* Windows */
    case 1:
      fseek(stdin, 0, SEEK_END);
      if (ftell(stdin) <= 0) exit(0);
      break;
    /* OS X, closes the nmh automatically after closing the app */
    /*
    case 2:
      break;
    */
  }
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

  free(json);

  (*key)[key_length] = '\0';
  (*val)[val_length] = '\0';
}