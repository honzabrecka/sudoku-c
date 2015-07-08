# sudoku-c [![Build Status](https://travis-ci.org/honzabrecka/sudoku-c.svg?branch=master)](https://travis-ci.org/honzabrecka/sudoku-c) [![Coverage Status](https://coveralls.io/repos/honzabrecka/sudoku-c/badge.svg?branch=master&service=github)](https://coveralls.io/github/honzabrecka/sudoku-c?branch=master)

As fast as possible sudoku solver and generator using the backtracking algorithm. It's a native node.js extension written in C.

## Installation

	npm install sudoku-c

## Usage

```javascript
var sudoku = require('sudoku-c');

// generate random grid - an array of 81 (9x9) integers
sudoku.generate();

// replace 54 random values with 0
sudoku.classic(sudoku.generate(), 54);

// solve given grid
sudoku.solve([
  0, 0, 0, 0, 6, 0, 1, 7, 0,
  8, 0, 0, 9, 0, 0, 0, 0, 0,
  3, 0, 5, 0, 0, 4, 6, 0, 0,
  0, 0, 4, 1, 0, 7, 0, 5, 0,
  2, 0, 0, 0, 0, 0, 0, 0, 1,
  0, 6, 0, 4, 0, 5, 3, 0, 0,
  0, 0, 1, 6, 0, 0, 7, 0, 8,
  0, 0, 0, 0, 0, 9, 0, 0, 2,
  0, 4, 9, 0, 8, 0, 0, 0, 0
]);
```