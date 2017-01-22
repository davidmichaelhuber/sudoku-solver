#ifndef SOLVER_H_
#define SOLVER_H_

/* 9x9 Sudoku Grid */
#define GRID 9

/* Holds the data the Chrome Native Messaging application sends before starting
to solve a given sudoku */
typedef struct
{
  int* sudoku;
  unsigned int skip_solution_count;
} SetupData;

/* Holds the number of solutions found */
extern unsigned int solution_count;

/* Holds the number of solutions that should not be sent */
extern unsigned int skip_solution_count;

/* Holds the solution status of the current sudoku */
extern _Bool solution_found;

/* Initiates the backtracking algorithm with the given SetupData*/
void sudoku_solve(SetupData *data);

#endif /* SOLVER_H_ */