#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "solver.h"
#include "native_messaging.h"

_Bool solution_found;

void sudoku_solve(int sudoku[])
{
	sudoku_solve_backtracking(sudoku, 0);
	solution_found = false;
	write_native_message("Ready for next sudoku");
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
			if (!solution_found)
			{
				write_native_message(get_current_sudoku(sudoku, field, val));
				read_native_message_tick();
			}
			
			if (partial_solution_fits(sudoku, val, field))
			{
				/* Set partial solution */
				sudoku[field] = val;

				/* Check if sudoku is completely solved */
				if (field >= (GRID * GRID) - 1)
				{	
					if (!solution_found)
					{
						solution_found = true;
						write_native_message("Solution found");	
					}
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
	*box_col = 	*box_row = 0;
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

void print_sudoku(int sudoku[])
{
	int i;
	for (i = 0; i < (GRID * GRID); i++)
	{
		if (i != 0 && i % GRID == 0)
			printf("\n");
		if (i != 0 && i % 3 == 0 && i % 9 != 0)
			printf("║ ");
		if (i != 0 && i % 27 == 0)
			printf("══════╬═══════╬══════\n");
		printf("%d ", sudoku[i]);
	}
	printf("\n");
}

char* get_current_sudoku(int sudoku[], int field, int val)
{
	int i;
	int temp = sudoku[field];
	size_t str_length = (sizeof(char) * GRID * GRID) + 1;
	/* number_count + 1 for terminating null */
	char* buffer = malloc(str_length);

	sudoku[field] = val;

	for (i = 0; i < (GRID * GRID); i++)
	{
		buffer[i] = (char)(sudoku[i] + '0');
	}

	buffer[str_length - 1] = '\0';

	sudoku[field] = temp;

	return buffer;
}
