// CSCI 2530
// Assignment: Assignment 8
// Author:     Trevor Strobel
// File:       huffman.cpp
// Tab stops:  2

// This program is designed to compress file containing only
// ASCII characters. The program reads characters from a file A,
// and using Huffman's algorithm, the characters
// are converted to binary and written to a file B.
//
// Tracing is available and enabled by running the
// program with the modifier "-t" following the name
// of the program.
//
// The input and output file names, respectively,
// are then needed.
//
// For example, if compiled and named huffman,
// one would run program with the following
// command (including "-t" if tracing is desired):
//
// ./huffman -t A B
//
// Files compressed with this program may be
// decompressed with unhuffman.cpp. See infor
// about that program in its documentation.


#include <cstdio>
#include "trace.h"
#include "tree.h"
#include "pqueue.h"
#include <cstring>
#include "binary.h"

using namespace std;

const int MAX_CHARS = 256;

// for debugging                                                                                                                                                                                            
void printInt(int i)
{
  printf("%d", i);
}


//------------------------------------------------
//                  writeZeros()
//------------------------------------------------
//------------------------------------------------
// The function writeZeros(a) writes the number 0
// to every index in the array a.
//
//------------------------------------------------

void writeZeros(int* a)
{
  for(int i = 0; i < MAX_CHARS; i++)
  {
    a[i] = 0;
  }
}

//------------------------------------------------
//                  writeNull()
//------------------------------------------------
//------------------------------------------------
// The function writeNull(a) stores null pointer
// in all of the indices of array a.
//
//------------------------------------------------
void writeNull(char** a)
{
  for(int i = 0; i < MAX_CHARS; i++)
  {
    a[i] = NULL;
  }
}

//------------------------------------------------
//             reallocPrefArray()
//------------------------------------------------
//------------------------------------------------
// The function reallocPrefArray(a,o,n) reallocates
// the array a, of size o, into a new array a, of
// size n.
//
//------------------------------------------------

void reallocPrefArray(char*& prefix, const int newSize)
{
  int n = newSize;
  char* prefixNew = new char[newSize];
  
  for(int i = 0; i < n; i++)
  {
    prefixNew[i] = prefix[i];
  }
  delete [] prefix;
  prefix = prefixNew;

}


//------------------------------------------------
//               getFrequencies()                  
//------------------------------------------------
//------------------------------------------------
// The function getFrequencies(f, a) reads file f
// and increments the corresponding index of array
// a for each time a character is encountered. The
// characters will be addressed by their ASCII
// values. For example, if the file contains "are",
// then the array indecies 97, 114, and 101,
// respectively, will be incremented.
//
//------------------------------------------------

bool getFrequencies(const char* path, int* freq)
{
  bool wasRead = false;
  int c;
  //writing zeros to the arrray.
  writeZeros(freq);
  FILE *file = fopen(path, "r");
  if(file != NULL)
  {
    wasRead = true;
    c = getc(file);
    while(c != EOF)
    {
      freq[c] += 1;
      c = getc(file);
    }
  }
  return wasRead;
}

//------------------------------------------------
//                insertLeaves()
//------------------------------------------------
//------------------------------------------------
// The function insertLeaves(f) creats leaves
// for each index in the array f that has a value
// of over 0. The leaves are also put into a
// Priority Queue q with their priority being the
// value from their array index, representing
// frequency of that character occuring. This
// function then returns the Priority Queue q.
//
//------------------------------------------------

PriorityQueue insertLeaves(int* freq)
{
  PriorityQueue q;

  for(int i = 0; i < MAX_CHARS; i++)
  {
    if(freq[i] > 0)
    {
      Tree t = new Node(i);
      insert(q, t, freq[i]);
    }
  }
  return q;
}

//------------------------------------------------
//                  makeTree()
//------------------------------------------------
//------------------------------------------------
// The function makeTree(q) alters the Priority
// Queue q so that it only holds one item, a
// Huffman Tree. A Huffman Tree is described in
// detail above in the file's main documentation.
//
//------------------------------------------------

PriorityQueue makeQueue(PriorityQueue& queue)
{
  int rp, sp;
  Tree rt, st;
  
  remove(queue, rt, rp);
  
  if(isEmpty(queue))
  {
    insert(queue, rt, rp);
    return queue;
  }
  else
  {
    remove(queue, st, sp);
    Tree t = new Node(rt, st);
    insert(queue, t, (rp + sp));
    return makeQueue(queue);
  }
}

//------------------------------------------------
//               getHuffTree()
//------------------------------------------------
//------------------------------------------------
// The function getHuffTree(a) returns a Huffman
// Tree based on an array of character
// frequencies, a.
//
//------------------------------------------------

Tree getHuffTree(int* freq)
{
  Tree x;
  int  i;
  PriorityQueue queue = insertLeaves(freq);
  queue = makeQueue(queue);
  remove(queue, x, i);
  return x;
}

//------------------------------------------------
//                buildCode()
//------------------------------------------------
//------------------------------------------------
// The function buildCode(t,c) fills the Code array
// c such that if character c occurs at a leaf in
// Tree t, then Code[c] holds the code for c. If
// the character c doesn't occur in t, then Code[c]
// is NULL.
//
//------------------------------------------------
void buildCode(Tree t, char** Code, char* prefix)
{
  if(t->kind == leaf)
  {
    Code[(unsigned int)t->ch] = prefix;
  }
  else
  {
    size_t i = strlen(prefix);
    Tree leftT = t->left;
    char* prefLeft = new char[i+2];
    strcpy(prefLeft, prefix);
    strcat(prefLeft, "0");
    buildCode(leftT, Code, prefLeft);
    
    Tree rightT = t->right;
    char* prefRight = new char[i+2];
    strcpy(prefRight, prefix);
    strcat(prefRight, "1");
    buildCode(rightT, Code, prefRight);
  }
}

//------------------------------------------------
//                 writeCode()
//------------------------------------------------
//------------------------------------------------
// The function writeCode(b,c) writes the code at
// array index c to file b.
//
//------------------------------------------------

void writeCode(BFILE* write, char* chCode)
{
  for(int i = 0; chCode[i] != '\0'; i++)
  {
    writeBit(write, (chCode[i]-48));
  }
}


//------------------------------------------------
//              translateToBits()
//------------------------------------------------
//------------------------------------------------
// The function translateToBits(a,b,c) opens a file with
// name a and converts the characters inside to
// bits based on a Huffman Tree. The codes resulting
// from said Huffman tree are stored in c.
// The bits are then written to file named b.
//
//------------------------------------------------

void translateToBits(const char* A, BFILE* write, char** Code)
{
  int c;
  FILE *file = fopen(A, "r");
  c = getc(file);
  while(c != EOF)
  {
    writeCode(write, Code[c]);
    c = getc(file);
  }
}

//------------------------------------------------
//               writeTreeBinary()
//------------------------------------------------
//------------------------------------------------
// The function writeTreeBinary(f,t) writes a binary
// description of the tree t to the binary file f.
//
//------------------------------------------------

void writeTreeBinary(BFILE* file, Tree t)
{
  if(t->kind == leaf)
  {
    writeBit(file, 1);
    writeByte(file, t->ch);
  }
  else
  {
    writeBit(file, 0);
    writeTreeBinary(file, t->left);
    writeTreeBinary(file, t->right);
  }
}

//------------------------------------------------
//                  main()
//------------------------------------------------
//------------------------------------------------

int main(int argc, char* argv[])
{
  enableTracing(argc, argv);

  int* freq = new int[MAX_CHARS];
  bool fileExists = getFrequencies(argv[argc-2], freq);
  if(!fileExists)
  {
    printf("The file \"%s\" was unable to be read or does not exist.\n", argv[argc-2]);
    return 1;
  }
  
  printFreq(freq);

  //Making Huffman Tree
  Tree t = getHuffTree(freq);
  prettyPrintTree(t);
  printf("\n");

  // building code
  char** code = new char*[MAX_CHARS];
  char* prefix = new char[1];
  prefix[0] = '\0';
  writeNull(code);
  buildCode(t, code, prefix);
  printCode(code);

  //file writing 
  BFILE* writeFile = openBinaryFileWrite(argv[argc-1]);
  if(writeFile == NULL)
  {
    printf("The file \"%s\" was not able to be opened or created.\n", argv[argc-1]);
  }
  else
  {
   // translateToBits(argv[argc-2], writeFile, code);
    writeTreeBinary(writeFile, t);
  }

  translateToBits(argv[argc-2], writeFile, code);
  closeBinaryFileWrite(writeFile);
  return 0;
}
