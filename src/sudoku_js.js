// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

var sudoku = exports;

sudoku.generate = function()
{
  var grid = [];

  for (var i = 0; i < 81; i++) {
    grid[i] = 0;
  }

  this._generate(grid);

  return grid;
};

sudoku.solve = function(grid)
{
  var index = this._findEmptyCell(grid);

  if (index == -1) {
    return true;
  }

  for (var i = 1; i <= 9; i++) {
    if (this._isPossible(grid, index, i)) {
      grid[index] = i;

      if (this.solve(grid)) {
        return true;
      }

      grid[index] = 0;
    }
  }

  return false;
};

/** @private */
sudoku._generate = function(grid)
{
  function fill(length)
  {
    var arr = [];

    for (var i = 0; i < length; i++) {
      arr[i] = i + 1;
    }

    return arr;
  }

  function randomItem(array)
  {
    return array.splice(Math.floor(Math.random() * array.length), 1)[0];  
  }

  var index = this._findEmptyCell(grid);

  if (index == -1) {
    return true;
  }

  var values = fill(9);
  var value;

  for (var i = 0; i < 9; i++) {
    value = randomItem(values);

    if (this._isPossible(grid, index, value)) {
      grid[index] = value;
      
      if (this._generate(grid)) {
        return true;
      }

      grid[index] = 0;
    }
  }

  return false;
}

/** @private */
sudoku._findEmptyCell = function(grid)
{
  var gridLength = grid.length;

  for (var i = 0; i < gridLength; i++) {
    if (grid[i] === 0) {
      return i;
    }
  }

  return -1;
};

/** @private */
sudoku._isPossible = function(grid, index, value)
{
  var x = Math.floor(index % 9);
  var y = Math.floor(index / 9);
  var squareX = x - (x % 3);
  var squareY = y - (y % 3);

  for (var i = 0; i < 9; i++) {
    if (this._getAt(grid, i, y) == value ||
      this._getAt(grid, x, i) == value ||
      this._getAt(grid, squareX + Math.floor(i % 3), squareY + Math.floor(i / 3)) == value) {
      return false;
    }
  }

  return true;
};

/** @private */
sudoku._getAt = function(grid, x, y)
{
  return grid[y * 9 + x];
};