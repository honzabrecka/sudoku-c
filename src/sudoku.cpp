// -----------------------------------------------------------------------
//  sudoku-c
//  Copyright 2014 Jan Břečka. All Rights Reserved.
//
//  This program is free software. You can redistribute and/or modify it
//  in accordance with the terms of the accompanying license agreement.
// -----------------------------------------------------------------------

#include <node.h>
#include <v8.h>

extern "C" {
  #include "sudoku_c.h"
}

using namespace v8;

Handle<Value> Solve(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments.")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsArray()) {
    ThrowException(Exception::TypeError(String::New("Expected array.")));
    return scope.Close(Undefined());
  }

  Handle<Array> grid = Handle<Array>::Cast(args[0]);
  int gridLength = grid->Length();

  if (gridLength != N * N) {
    ThrowException(Exception::TypeError(String::New("Wrong grid given - invalid length.")));
    return scope.Close(Undefined());
  }

  int xgrid[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = grid->Get(i)->Uint32Value();
  }

  int result = sudoku_solve(xgrid);

  if (!result) {
    ThrowException(Exception::TypeError(String::New("Invalid board given.")));
    return scope.Close(Undefined());
  }

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(*(xgrid + i)));
  }

  return scope.Close(grid);
}

Handle<Value> Generate(const Arguments& args) {
  HandleScope scope;
  int gridLength = N * N;
  Local<Array> grid = Array::New(gridLength);
  int xgrid[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = EMPTY;
  }

  sudoku_generate(xgrid);

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(*(xgrid + i)));
  }

  return scope.Close(grid);
}

Handle<Value> Classic(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments.")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsArray()) {
    ThrowException(Exception::TypeError(String::New("Expected array.")));
    return scope.Close(Undefined());
  }

  if (!args[1]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Expected number.")));
    return scope.Close(Undefined());
  }

  Handle<Array> grid = Handle<Array>::Cast(args[0]);
  int gridLength = grid->Length();

  if (gridLength != N * N) {
    ThrowException(Exception::TypeError(String::New("Wrong grid given - invalid length.")));
    return scope.Close(Undefined());
  }

  int xgrid[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = grid->Get(i)->Uint32Value();
  }

  sudoku_classic(xgrid, args[1]->Uint32Value());

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(*(xgrid + i)));
  }

  return scope.Close(grid);
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "solve", Solve);
  NODE_SET_METHOD(target, "generate", Generate);
  NODE_SET_METHOD(target, "classic", Classic);
}

NODE_MODULE(sudoku, init)