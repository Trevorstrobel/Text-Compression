// CSCI 2530
// Assignment: Assignment 6
// Author:     Trevor Strobel
// File:       pqueue.cpp
// Tab stops:  2

// This module defines 4 functions for the creation and manipulation
// of a priority queue. A priority queue is a collection of items
// each having a priority.  A priority queue supports three fundamental
// operations:
//
//  1. You can ask a priority queue whether it is empty.
//  2. You can insert an itme with a given priority.
//  3. You can remove the item that has the smalled priority.
//
// The 4 functions described here are as follows:
//
//  PriorityQueue    a constructor that makes an empty priority queue.
//  isEmpty(q)       returns true if q is an empty priority queue.
//  insert(q,x,p)    inserts item x with priority p into q.
//  remove(q,x,p)    removes the item that has the smallest priority from q.
//
//

#include <cstdlib>
#include <cstdio>
#include "pqueue.h"
using namespace std;

// An object of type PQCell represents a cell in a priority
// queue.
//
// The fields are:
//
// item          The item that this cell holds. ItemType is changeable
//               in pqueue.h
//
// priority      The given to this cell. PriorityType is changeable in
//               pqueue.h
//
// tail          A pointer to the next cell in the priority queue.

struct PQCell
{
  PQCell*      tail;
  ItemType     item;
  PriorityType priority;

  PQCell(PQCell* t, ItemType x, PriorityType p)
  {
    tail = t;
    item = x;
    priority = p;
  }

};


//------------------------------------------------
//                  isEmpty()
//------------------------------------------------
//------------------------------------------------
// The function isEmpty(q) returns true if the
// priority queue, q, is empty, and false if q
// is not empty.
//
//------------------------------------------------

bool isEmpty(const PriorityQueue& q)
{
  return q.head == NULL;
}

//------------------------------------------------
//                  insertCell()
//------------------------------------------------
//------------------------------------------------
// **This is a helper function. Not to be exported**
// The function insertCell(L,x,p) insterts item x
// with priority p into linked list L. This only
// a helper function to be used in insert() and
// not exported.
//
//------------------------------------------------

void insertCell(PQCell*& L, ItemType x, PriorityType p)
{
  if(L == NULL || p <= L->priority)
  {
    L = new PQCell(L, x, p);
  }
  else
  {
    insertCell(L->tail, x, p);    
  }
}

//------------------------------------------------
//                  insert()
//------------------------------------------------
//------------------------------------------------
// The function insert(q,x,p) inserts item x with
// priority p into PriorityQueue object q.
//
//------------------------------------------------

void insert(PriorityQueue& q, ItemType x, PriorityType p)
{
  insertCell(q.head, x, p);
}



//------------------------------------------------
//             printPriorityQueue()
//------------------------------------------------
//------------------------------------------------
//   **This funciton is only for debugging**
// The function printPriorityQueue(q,pi,pp) prints
// the priority queue q.  Calling this function
// requires the file using this module to outline
// how items and priorities should be printed in
// functions passed as pi() and pp() respectively.
//
//------------------------------------------------

void printPriorityQueue(const PriorityQueue& q,
                        ItemPrinter pi, PriorityPrinter pp)
{
  PriorityQueue L = q;
  
  printf("The Priority Queue is as follows:\n\nItem      Priority\n");

  while(L.head != NULL)
  {
    pi(L.head->item);
    printf("      ");
    pp(L.head->priority);
    printf("\n");
    L.head = L.head->tail;
  }
}

//------------------------------------------------
//                  remove()
//------------------------------------------------
//------------------------------------------------
// The function remove(q,x,p) removes the item
// from q that has the smallest priority. It stores
// the item in x and the priority in p. If two items
// have the same priority, it removes one of them.
//
//------------------------------------------------

void remove(PriorityQueue& q, ItemType& x, PriorityType& p)
{
  if(q.head != NULL)
  {
    PQCell* L = q.head;
    x = L->item;
    p = L->priority;
    q.head = L->tail;
    delete L;
  }

}
