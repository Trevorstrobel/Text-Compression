// CSCI 2530
// Assignment: Assignment 8
// Author:     Trevor Strobel
// File:       trace.h
// Tab stops:  2

#include "tree.h"

extern int traceLevel;

// Public functions funcitons

void enableTracing(int argc, char** args);
void printFreq(int* a);
void prettyPrintTree(const Tree t);
void printCode(char** code);
void charDesc(unsigned char c);
