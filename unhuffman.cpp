// CSCI 2530
// Assignment: Assignment 8
// Author:     Trevor Strobel
// File:       unhuffman.cpp
// Tab stops:  2

// This program is designed to uncompress a binary file created by huffman.cpp
// This function will take in a binary file B, representing a compressed
// file containing ASCII characters, and write an uncompressed file A.
//
// If compiled and named unhuffman, one would run this software with
// the following command:
//
// ./unhuffman B C
//
// Further documentation regarding how compression works is available
// in huffman.cpp.
//


#include <cstdio>
#include "trace.h"
#include "binary.h"
#include "tree.h"

using namespace std;

//------------------------------------------------
//              readBinaryTree()
//------------------------------------------------
//------------------------------------------------
// The function readBinaryTree(f) reads a tree
// represented in binary from a file f and returns
// that tree.
//
//------------------------------------------------

Tree readBinaryTree(BFILE* file)
{
  int bit = readBit(file);
  if(bit == 1)
  {
    Tree t = new Node(readByte(file));
    return t;
  }
  else
  {
    Tree leftT = readBinaryTree(file);
    Tree rightT = readBinaryTree(file);
    Tree t = new Node(leftT, rightT);
    return t;
  }
}

//------------------------------------------------
//                 readCode()
//------------------------------------------------
//------------------------------------------------
// The function readCode(t,f) reads bits one at a
// time from a binary file f and uses those bits
// to navigate a Tree t, returning an integer
// representing the present leaf when a leaf is
// encountered.
//
//------------------------------------------------

int readCode(const Tree t, BFILE* file)
{
  int ch = 0;
  
  if(t->kind == leaf)
  {
    ch = t->ch;
  }
  else
  {
    int bit = readBit(file);
    if(bit == -1)
    {
      ch = -1;
    }
    else if(bit == 0)
    {
      Tree tLeft = t->left;
      ch = readCode(tLeft,file);
    }
    else
    {
      Tree tRight = t->right;
      ch = readCode(tRight,file);
    }
  }
  return ch;
}

//------------------------------------------------
//               decompress()
//------------------------------------------------
//------------------------------------------------
// The function decompress(a,b,t) decrompresses
// the compressed file b, and using the Huffman
// Tree t, writes the corresponding characters
// to file a.
//
//------------------------------------------------

void decompress(char* A, BFILE* B, Tree t)
{
  FILE* writeFile = fopen(A, "w");
  if(writeFile == NULL)
  {
    printf("The file \"%s\" was not able to be opened or created.\n", A);
  }
  else
  {
    int ch = readCode(t,B);
    while(ch != -1)
    {
      putc((char)ch,writeFile);
      ch = readCode(t,B);
    }

  }
}


//------------------------------------------------
//                  main()
//------------------------------------------------
//------------------------------------------------

int main(int argc, char* argv[])
{
  enableTracing(argc, argv);
  Tree t;
  //opening binary file 
  BFILE* readFile = openBinaryFileRead(argv[argc-2]);

  if(readFile == NULL)
  {
    printf("The file \"%s\" was unable to be opened or does not exist.", argv[argc-2]);
    return 1;
  }
  else
  {
    t =  readBinaryTree(readFile);      
  }
  
  prettyPrintTree(t);

  decompress(argv[argc-1], readFile, t);
  //closing the binary file
  closeBinaryFileRead(readFile);
  return 0;
}
