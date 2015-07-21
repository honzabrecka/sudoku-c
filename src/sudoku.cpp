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

void Solve(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments.")));
    return;
  }

  if (!args[0]->IsArray()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Expected array.")));
    return;
  }

  Local<Array> grid = Local<Array>::Cast(args[0]);
  int gridLength = grid->Length();

  if (gridLength != N * N) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong grid given - invalid length.")));
    return;
  }

  int *xgrid = new int[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = grid->Get(i)->Uint32Value();
  }

  int result = sudoku_solve(xgrid);

  if (!result) {
    delete[] xgrid;
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Invalid board given.")));
    return;
  }

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(isolate, *(xgrid + i)));
  }

  delete[] xgrid;
  args.GetReturnValue().Set(grid);
}

void Generate(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);
  int gridLength = N * N;
  Local<Array> grid = Array::New(isolate, gridLength);
  int *xgrid = new int[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = EMPTY;
  }

  sudoku_generate(xgrid);

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(isolate, *(xgrid + i)));
  }

  delete[] xgrid;
  args.GetReturnValue().Set(grid);
}

void Classic(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  HandleScope scope(isolate);

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments.")));
    return;
  }

  if (!args[0]->IsArray()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Expected array.")));
    return;
  }

  if (!args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Expected number.")));
    return;
  }

  Local<Array> grid = Local<Array>::Cast(args[0]);
  int gridLength = grid->Length();

  if (gridLength != N * N) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong grid given - invalid length.")));
    return;
  }

  int *xgrid = new int[gridLength];
  int i;

  for (i = 0; i < gridLength; i++) {
    *(xgrid + i) = grid->Get(i)->Uint32Value();
  }

  sudoku_classic(xgrid, args[1]->Uint32Value());

  for (i = 0; i < gridLength; i++) {
    grid->Set(i, Uint32::New(isolate, *(xgrid + i)));
  }

  delete[] xgrid;
  args.GetReturnValue().Set(grid);
}

void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "solve", Solve);
  NODE_SET_METHOD(target, "generate", Generate);
  NODE_SET_METHOD(target, "classic", Classic);
}

NODE_MODULE(sudoku, init)