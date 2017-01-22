#ifndef SOLVER_H_
#define SOLVER_H_

/* 9x9 Sudoku Grid */
#define GRID 9

typedef struct
{
  int* sudoku;
  unsigned int skip_solution_count;
} SetupData;

extern unsigned int solution_count;

extern unsigned int skip_solution_count;

/* Holds the solution status of the current sudoku */
extern _Bool solution_found;

/* Returns the solution for a given sudoku */
void sudoku_solve(SetupData *data);

/* Finds the solution for a given sudoku with backtracking */
void sudoku_solve_backtracking(int sudoku[], int field);

/* Returns true if a given partial solution fits at a given place */
_Bool partial_solution_fits(int sudoku[], int val, int field);

/* Converts a given field to a certain column and row */
void field_to_coords(int field, int *col, int *row);

/* Returns a field calculated by the given column and row */
int choords_to_field(int col, int row);

/* Converts given column and row to a certain box column and box row */
void coords_to_box_coords(int col, int row, int *box_col, int *box_row);

/* Returns the first field of the given box coords */
int first_field_of_box_coords(int box_col, int box_row);

/* Prints a given sudoku to the console */
void print_sudoku(int sudoku[]);

/* Returns a string representing a given sudoku with val in sudoku[field] */
char* get_current_sudoku(int sudoku[], int field, int val);

#endif /* SOLVER_H_ */