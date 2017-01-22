#ifndef NATIVE_MESSAGING_H_
#define NATIVE_MESSAGING_H_

/* Reads a JSON string from the Chrome Native Messaging application. So the
contents of the JSON string don't matter but for further development the JSON
string should look like this: {"tick":"next"} */
void get_tick();

/* Reads two JSON strings from the Chrome Native Messaging application. The 81
sudoku fields awaited first followed by the number of solutions to skip. The
JSON strings must look like this (in that exact order):
{"sudoku":"<81 Fields of Sudoku>"}, {"skip_solution_count":"<Number>"} */
SetupData *get_setup_data();

/* Writes a JSON string to the Chrome Native Messaging application. key and val
get de-allocated after sending */
void write_native_message(char* key, char* val);

#endif /* NATIVE_MESSAGING_H_ */