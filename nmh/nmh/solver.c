#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "solver.h"
#include "native_messaging.h"

/* Solves a given sudoku and sends the partial solution(s), solved solution(s)
and solution tries to the Chrome Native Messaging application */
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

/* Returns a string representing a given sudoku with val in sudoku[field] */
char* get_current_sudoku(int sudoku[], int field, int val);

/* Holds the number of solutions found */
unsigned int solution_count;

/* Holds the number of solutions that should not be sent */
unsigned int skip_solution_count;

/* Holds the solution status of the current sudoku */
_Bool solution_found;

void sudoku_solve(SetupData *data)
{
  solution_count = 0;
  skip_solution_count = data->skip_solution_count;
  sudoku_solve_backtracking(data->sudoku, 0);
  free(data->sudoku);
  free(data);
  solution_found = false;
}

void sudoku_solve_backtracking(int sudoku[], int field)
{
  int val;

  /* Check that current field is not predefined */
  if (sudoku[field] == 0)
  {
    /* Loop through all possible values for sudoku[field] */
    for (val = 1; val <= GRID; val++)
    {
      solution_count++;
      if (!solution_found && skip_solution_count != 1 && (solution_count % skip_solution_count == 0))
      {
        write_native_message("unsolved", get_current_sudoku(sudoku, field, val));
        get_tick();
      }

      if (partial_solution_fits(sudoku, val, field))
      {
        /* Set partial solution */
        sudoku[field] = val;

        /* Check if sudoku is completely solved */
        if (field >= (GRID * GRID) - 1)
        {
          solution_found = true;
          write_native_message("solved", get_current_sudoku(sudoku, field, val));

          /* Calculates the length of an integer */
          char *tries = malloc((size_t)floor(log10(abs((int)solution_count))) + 1 * sizeof(char));
          sprintf(tries, "%d", solution_count);
          write_native_message("tries", tries);
          free(tries);
        }

        /* Keep on solving */
        sudoku_solve_backtracking(sudoku, field + 1);

        /* Partial solution is invalid, reset partial solution */
        sudoku[field] = 0;
      }
    }
  }
  else
  {
    sudoku_solve_backtracking(sudoku, field + 1);
  }
}

_Bool partial_solution_fits(int sudoku[], int val, int field)
{
  int i, j;
  int col, row;
  int box_col, box_row;
  int first_field;
  field_to_coords(field, &col, &row);

  /* Check if val is already in use horizontally or vertically */
  for (i = 1; i <= GRID; i++)
  {
    if (sudoku[choords_to_field(i, row)] == val)
    {
      return false;
    }
    if (sudoku[choords_to_field(col, i)] == val)
    {
      return false;
    }
  }

  /* Check if val is already in use in its own box */
  coords_to_box_coords(col, row, &box_col, &box_row);
  first_field = first_field_of_box_coords(box_col, box_row);

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (sudoku[first_field + (i * GRID) + j] == val)
      {
        return false;
      }
    }
  }

  return true;
}

void field_to_coords(int field, int *col, int *row)
{
  *row = (field / GRID) + 1;
  *col = (field % GRID) + 1;
}

int choords_to_field(int col, int row)
{
  return (row - 1) * GRID + (col - 1);
}

void coords_to_box_coords(int col, int row, int *box_col, int *box_row)
{
  int i;
  *box_col =  *box_row = 0;
  for (i = 0; i < col; i++)
  {
    if (i % 3 == 0)
    {
      *box_col += 1;
    }
  }

  for (i = 0; i < row; i++)
  {
    if (i % 3 == 0)
    {
      *box_row += 1;
    }
  }
}

int first_field_of_box_coords(int box_col, int box_row)
{
  return (GRID * 3 * (box_row - 1)) + (box_col - 1) * 3;
}

char* get_current_sudoku(int sudoku[], int field, int val)
{
  int i;
  int temp = sudoku[field];
  char* buffer = malloc((sizeof(char) * GRID * GRID) + sizeof(char));

  sudoku[field] = val;

  for (i = 0; i < (GRID * GRID); i++)
  {
    buffer[i] = (char)(sudoku[i] + '0');
  }

  buffer[GRID * GRID] = '\0';

  sudoku[field] = temp;

  return buffer;
}
