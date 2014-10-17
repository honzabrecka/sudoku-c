// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

var assert = require('assert');
var sudoku = require('../index');

describe('sudoku.solve()', function()
{
  it('should solve sudoku', function()
  {
  	var expected = [
	  4, 9, 2, 3, 6, 8, 1, 7, 5,
	  8, 7, 6, 9, 5, 1, 2, 3, 4,
	  3, 1, 5, 2, 7, 4, 6, 8, 9,
	  9, 3, 4, 1, 2, 7, 8, 5, 6,
	  2, 5, 7, 8, 3, 6, 9, 4, 1,
	  1, 6, 8, 4, 9, 5, 3, 2, 7,
	  5, 2, 1, 6, 4, 3, 7, 9, 8,
	  7, 8, 3, 5, 1, 9, 4, 6, 2,
	  6, 4, 9, 7, 8, 2, 5, 1, 3
	];
  	var actual = sudoku.solve([
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
    assert.equal(actual.join(','), expected.join(','));
  });
});

describe('sudoku.generate()', function()
{
  it('should generate a valid grid', function()
  {
  	var actual = sudoku.generate();
    assert.equal(81, actual.length);
    assert.equal(-1, actual.indexOf(0));
  });
});