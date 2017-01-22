#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "solver.h"
#include "native_messaging.h"

int main()
{
  while(1)
  {
    write_native_message("status", "ready");
    sudoku_solve(get_setup_data());
  }

  return 0;
}