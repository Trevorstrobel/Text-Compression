// CSCI 2530
// Assignment: Assignment 8
// Author:     Trevor Strobel
// File:       trace.cpp
// Tab stops:  2


//TODO: MAKE THIS DESCRIPTION MORE ROBUST.
// provides an global variable that can be switched
// off and on to enable or disable tracing.

#include <cstdio>
#include "trace.h"
#include "tree.h"
#include <cstring>
#include <cctype>

// Global variable to enable/disable tracing.
// A value of 1 is enabled, a value of 0 is
// disabled.

int traceLevel = 0;


//------------------------------------------------
//              enableTracing()
//------------------------------------------------
//------------------------------------------------
// The function enableTracing(x,y) searches the
// array y, of size x, for the string "-t". If
// that string is present, then tracing is enabled.
//
//------------------------------------------------

void enableTracing(int argc, char** args)
{
  if(argc >= 2)
  {
    for(int i = 1; i < argc; i++)
    {
      if(strcmp(args[i], "-t") == 0)
      {
        traceLevel = 1;
      }
    }
  }
}

//------------------------------------------------
//               charDesc()
//------------------------------------------------
//------------------------------------------------
//  The function charDesc(c) prints the description
//  of an unsigned char c.
//
//------------------------------------------------

void charDesc(unsigned char c)
{
  
  if(isprint(c) && c != 32)
  {
    printf("%c", char(c));
  }
  else
  {
    switch(c)
    {
      case 32: printf("Space");
               break;
      case 10: printf("\\n");
               break;
      case 9:  printf("tab");
               break;
      default: printf("\\%d", c);
               break;
    }
  }
}

//------------------------------------------------
//                  printFreq()
//------------------------------------------------
//------------------------------------------------
// The function printFreq(a) is only run when
// tracing is enabled. printFreq(a) prints the
// frequencies of all characters that occur at least
// once in a given array a.
//
//------------------------------------------------

void printFreq(int* a)
{
  if(traceLevel == 1)
  {
    printf("The character frequencies are:\n");
    for(int i = 0; i < 256; i++)
    {
      if(a[i] > 0)
      {
        charDesc(i);
        printf("      %d\n", a[i]);
      }
    }
  }
}


//------------------------------------------------
//                  printTree()
//------------------------------------------------
//------------------------------------------------
// The function printTree(t) prints the tree t to
// the the standard output using the following
// format. A leaf is shown as the character at
// that leaf. A nonleaf is shown as the two
// subtrees, surrounded by parenthese and separated
// by a comma.
//
// For example:
//
// ((c,(b,d)),(a,e))
//
// Represents a tree that looks like this:
//
//               0
//            |      |
//          0          0
//        |   |      |   |
//       c     0    a     e
//           |  |
//          b    d
//------------------------------------------------

void printTree(const Tree t)
{ 
  if(t->kind == leaf)
  {
    charDesc(t->ch);
  }
  else
  {
    printf("(");
    printTree(t->left);
    printf(",");
    printTree(t->right);
    printf(")");
  }
}

//------------------------------------------------
//                 prettyPrintTree()
//------------------------------------------------
//------------------------------------------------
// The function prettyPrintTree(t) prints a heading
// for the recursive function printTree(). 
//
//------------------------------------------------

void prettyPrintTree(const Tree t)
{
  if(traceLevel == 1)
  {
    printf("\nThe resulting tree is: \n");
    printTree(t);
    printf("\n");
  }
}


//------------------------------------------------
//                  printCode()
//------------------------------------------------
//------------------------------------------------
// The function printCode(c) prints, to the
// standard out, the contents of an array of
// null-terminated string, c, as well as the indices,
// represented by characters, that are associated
// to those null-terminated strings.
//
//------------------------------------------------

void printCode(char** code)
{
  if(traceLevel == 1)
  {
    printf("\nThe Code array is as follows: \n");

    for(int i = 0; i < 256; i++)
    {
      if(code[i] != NULL)
      {
        printf("char desc: ");
        charDesc(i);
        printf("  code:");
        printf("    %s\n", code[i]);
      }
    }
  }
}
