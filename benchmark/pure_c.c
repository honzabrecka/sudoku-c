// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

#include "./../src/sudoku_c.h"

int main(int argc, char **argv)
{
  static int grid[N * N];
  int result = sudoku_solve(grid);
  return !result;
}