// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

#define N 9
#define EMPTY 0

int sudoku_generate(int * grid);
int sudoku_solve(int * grid);
int sudoku_classic(int * grid, int empty);