// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

#include <stdlib.h>
#include <time.h>
#include "sudoku_c.h"

static int getAt(int * grid, int x, int y)
{
  int index = y * N + x;
  int value = *(grid + index);
  return value;
}

static int findEmptyIndex(int * grid)
{
  int length = N * N;
  int i;

  for (i = 0; i < length; i++) {
    if (*(grid + i) == EMPTY) {
      return i;
    }
  }

  return -1;
}

static int isPossible(int * grid, int index, int value)
{
  int boxN = N / 3;
  int x = index % N;
  int y = index / N;
  int boxX = x - (x % boxN);
  int boxY = y - (y % boxN);
  int i;

  for (i = 0; i < N; i++) {
    if (getAt(grid, i, y) == value ||
      getAt(grid, x, i) == value ||
      getAt(grid, boxX + (int)(i % boxN), boxY + (int)(i / boxN)) == value) {
      return 0;
    }
  }

  return 1;
}

static int candidates(int * grid, int index)
{
  int boxN = N / 3;
  int x = index % N;
  int y = index / N;
  int boxX = x - (x % boxN);
  int boxY = y - (y % boxN);
  int i;
  int counts[N + 1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int candidate = 0;

  for (i = 0; i < N; i++) {
    counts[getAt(grid, i, y)]++;
    counts[getAt(grid, x, i)]++;
    counts[getAt(grid, boxX + (int)(i % boxN), boxY + (int)(i / boxN))]++;
  }

  for (i = 1; i <= N; i++) {
    if (*(counts + i) == 0) {
      if (candidate > 0) {
        return 0;
      }
      candidate = i;
    }
  }

  grid[index] = candidate;
  return candidate > 0;
}

static void swap(int * a, int * b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

static void shuffle(int * array, int length)
{
  int i, r;

  srand(time(NULL));

  for (i = length - 1; i > 0; i--) {
    r = rand() % (i + 1);
    swap(&array[i], &array[r]);
  }
}

static void fill(int * array, int length, int start)
{
  int i;

  for (i = 0; i < length; i++) {
    array[i] = start + i;
  }
}

int sudoku_generate(int * grid)
{
  int index = findEmptyIndex(grid);
  int values[N], i, value;

  if (index == -1) {
    return 1;
  }

  fill(values, N, 1);
  shuffle(values, N);

  for (i = 0; i < N; i++) {
    value = *(values + i);

    if (isPossible(grid, index, value)) {
      grid[index] = value;
      
      if (sudoku_generate(grid)) {
        return 1;
      }

      grid[index] = EMPTY;
    }
  }

  return 0;
}

static int solveWithConditions(int * grid)
{
  int empty = 0;
  int change = 0;
  int i;

  for (i = 1; i <= N; i++) {
    if (*(grid + i) == EMPTY) {
      if (candidates(grid, i)) {
        change = 1;
      } else {
        empty = 1;
      }
    }
  }

  if (empty) {
    if (change) {
      return solveWithConditions(grid);
    } else {
      return 0;
    }
  }

  return 1;
}

static int solveWithBacktracking(int * grid)
{
  int index = findEmptyIndex(grid);
  int i;

  if (index == -1) {
    return 1;
  }

  for (i = 1; i <= N; i++) {
    if (isPossible(grid, index, i)) {
      grid[index] = i;
      
      if (solveWithBacktracking(grid)) {
        return 1;
      }

      grid[index] = EMPTY;
    }
  }

  return 0;
}

int sudoku_solve(int * grid)
{
  if (!solveWithConditions(grid)) {
    return solveWithBacktracking(grid);
  }
  return 1;
}

int sudoku_classic(int * grid, int empty)
{
  int length = N * N;
  int indicesToRemove[length];
  int i;

  fill(indicesToRemove, length, 0);
  shuffle(indicesToRemove, length);

  for (i = 0; i < empty; i++) {
    grid[*(indicesToRemove + i)] = EMPTY;
  }

  return 1;
}