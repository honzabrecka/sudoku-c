// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

#include <stdio.h>
#include "../src/sudoku_c.c"

// minunit - http://www.jera.com/techinfo/jtns/jtn002.html

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)

#define L 81

int assertDeepEqual(int * actual, int * expected, int length)
{
  int i;

  for (i = 0; i < length; i++) {
    if (*(actual + i) != *(expected + i)) {
      return 0;
    }
  }

  return 1;
}

int assertNoEmpty(int * actual, int length)
{
  int i;

  for (i = 0; i < length; i++) {
    if (*(actual + i) == 0) {
      return 0;
    }
  }

  return 1;
}

int tests_run = 0;

//------------------
// tests

static char * test_assertDeepEqual()
{
  static int a[2] = {1, 2};
  static int b[2] = {1, 2};
  mu_assert("e: test_assertDeepEqual", assertDeepEqual(a, b, 2));
  return 0;
}

static char * test_assertNoEmpty()
{
  static int a[2] = {1, 5};
  mu_assert("e: test_assertNoEmpty", assertNoEmpty(a, 2));
  return 0;
}

static char * test_getAt()
{
  static int grid[L] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  mu_assert("e: test_getAt", getAt(grid, 2, 4) == 3);
  return 0;
}

static char * test_findEmptyIndex()
{
  static int grid[L] = {
    1, 2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
  };
  mu_assert("e: test_findEmptyIndex", findEmptyIndex(grid) == 2);
  return 0;
}

static char * test_findEmptyIndexInSolvedGrid()
{
  static int grid[L] = {
    4, 9, 2, 3, 6, 8, 1, 7, 5,
    8, 7, 6, 9, 5, 1, 2, 3, 4,
    3, 1, 5, 2, 7, 4, 6, 8, 9,
    9, 3, 4, 1, 2, 7, 8, 5, 6,
    2, 5, 7, 8, 3, 6, 9, 4, 1,
    1, 6, 8, 4, 9, 5, 3, 2, 7,
    5, 2, 1, 6, 4, 3, 7, 9, 8,
    7, 8, 3, 5, 1, 9, 4, 6, 2,
    6, 4, 9, 7, 8, 2, 5, 1, 3
  };
  mu_assert("e: test_findEmptyIndexInSolvedGrid", findEmptyIndex(grid) == -1);
  return 0;
}

static char * test_isPossible()
{
  static int grid[L] = {
    4, 9, 2, 3, 6, 8, 1, 7, 5,
    8, 7, 6, 9, 5, 1, 2, 3, 4,
    3, 1, 0, 2, 7, 4, 6, 8, 9,
    9, 3, 4, 1, 2, 7, 8, 5, 6,
    2, 5, 7, 8, 3, 6, 9, 4, 1,
    1, 6, 8, 4, 9, 5, 3, 2, 7,
    5, 2, 1, 6, 4, 3, 7, 9, 8,
    7, 8, 3, 5, 1, 9, 4, 6, 2,
    6, 4, 9, 7, 8, 2, 5, 1, 3
  };
  mu_assert("e: test_isPossible", isPossible(grid, 20, 5) == 1);
  return 0;
}

static char * test_isImpossible()
{
  static int grid[L] = {
    4, 9, 2, 3, 6, 8, 1, 7, 5,
    8, 7, 6, 9, 5, 1, 2, 3, 4,
    3, 1, 5, 2, 7, 4, 6, 8, 9,
    9, 3, 4, 1, 2, 7, 8, 5, 6,
    2, 5, 7, 8, 3, 6, 9, 4, 1,
    1, 6, 8, 4, 9, 5, 3, 2, 7,
    5, 2, 1, 6, 4, 3, 7, 9, 8,
    7, 8, 3, 5, 1, 9, 4, 6, 2,
    6, 4, 9, 7, 8, 2, 5, 1, 3
  };
  mu_assert("e: test_isImpossible", isPossible(grid, 20, 5) == 0);
  return 0;
}

static char * test_swap()
{
  int a = 5;
  int b = 3;
  swap(&a, &b);
  mu_assert("e: test_swap", a == 3 && b == 5);
  return 0;
}

static char * test_fill()
{
  static int array[2];
  fill(array, 2);
  mu_assert("e: test_fill", *array == 1 && *(array + 1) == 2);
  return 0;
}

static char * test_sudoku_generate()
{
  static int actual[L];
  int result = sudoku_generate(actual);
  int noEmpty = assertNoEmpty(actual, L);
  mu_assert("e: test_sudoku_generate()", result && noEmpty);
  return 0;
}

static char * test_sudoku_solve()
{
  static int actual[L] = {
    0, 0, 0, 0, 6, 0, 1, 7, 0,
    8, 0, 0, 9, 0, 0, 0, 0, 0,
    3, 0, 5, 0, 0, 4, 6, 0, 0,
    0, 0, 4, 1, 0, 7, 0, 5, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 6, 0, 4, 0, 5, 3, 0, 0,
    0, 0, 1, 6, 0, 0, 7, 0, 8,
    0, 0, 0, 0, 0, 9, 0, 0, 2,
    0, 4, 9, 0, 8, 0, 0, 0, 0
  };
  static int expected[L] = {
    4, 9, 2, 3, 6, 8, 1, 7, 5,
    8, 7, 6, 9, 5, 1, 2, 3, 4,
    3, 1, 5, 2, 7, 4, 6, 8, 9,
    9, 3, 4, 1, 2, 7, 8, 5, 6,
    2, 5, 7, 8, 3, 6, 9, 4, 1,
    1, 6, 8, 4, 9, 5, 3, 2, 7,
    5, 2, 1, 6, 4, 3, 7, 9, 8,
    7, 8, 3, 5, 1, 9, 4, 6, 2,
    6, 4, 9, 7, 8, 2, 5, 1, 3
  };
  int result = sudoku_solve(actual);
  int deepEqual = assertDeepEqual(actual, expected, L);
  mu_assert("e: test_sudoku_solve()", result && deepEqual);
  return 0;
}

//------------------
// runner

static char * all_tests()
{
  mu_run_test(test_assertDeepEqual);
  mu_run_test(test_assertNoEmpty);

  mu_run_test(test_getAt);
  mu_run_test(test_findEmptyIndex);
  mu_run_test(test_findEmptyIndexInSolvedGrid);
  mu_run_test(test_isPossible);
  mu_run_test(test_isImpossible);
  mu_run_test(test_swap);
  mu_run_test(test_fill);
  mu_run_test(test_sudoku_generate);
  mu_run_test(test_sudoku_solve);

  return 0;
}

int main(int argc, char **argv)
{
  char * result = all_tests();

  if (result == 0) {
    printf("OK\n");
  } else {
    printf("%s\n", result);
  }
  
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}