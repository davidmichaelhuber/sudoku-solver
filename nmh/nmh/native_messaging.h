#ifndef NATIVE_MESSAGING_H_
#define NATIVE_MESSAGING_H_

void read_native_message_tick();

int* read_native_message_sudoku();

void write_native_message(char* key, char* val);

#endif /* NATIVE_MESSAGING_H_ */