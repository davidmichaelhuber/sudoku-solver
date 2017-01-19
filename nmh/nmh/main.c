#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "solver.h"
#include "native_messaging.h"

int main()
{
	/* 136259748725418936489367150364780219518692374972134685240576893853921467697840520 */
	int sudoku[] =	{
								1, 3, 6, 2, 5, 9, 7, 4, 8, 
								7, 2, 5, 4, 1, 8, 9, 3, 6, 
								4, 8, 9, 3, 6, 7, 1, 5, 0, 
								3, 6, 4, 7, 8, 0, 2, 1, 9, 
								5, 1, 8, 6, 9, 2, 3, 7, 4,
								9, 7, 2, 1, 3, 4, 6, 8, 5, 
								2, 4, 0, 5, 7, 6, 8, 9, 3, 
								8, 5, 3, 9, 2, 1, 4, 6, 7, 
								6, 9, 7, 8, 4, 0, 5, 2, 0 
							};

	sudoku_solve(sudoku);

	return 0;
}