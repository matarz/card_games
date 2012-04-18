/* 
   Author: Zakaria Almatar
   Date: 10/24/09
   Class: CS202
   Assignment: Program#1
*/
/*
   File name: stack.cpp
   Functions: This file has functions definitions of:
              class stack:
                 -Constructor 
                 -Destructor
                 -Is empty: checks if the stack is empty
                 -Push: adds a card to the stack
                 -Pop: removes a card from the stack
                 -Gettop: returns a the first card on the stack
*/


#include <iostream>
#include <stdio.h>
#include <time.h>
#include "header.h"
using namespace std;



/*************************************************************************
***                        Stack Constructor                           ***
*************************************************************************/
//constructor: sets the nodes to NULL
card_stack::card_stack() 
{
  head = NULL;
  temp = NULL;
}

/*************************************************************************
***                         Stack Destructor                           ***
*************************************************************************/
//stack destructor: deallocates the stack
card_stack::~card_stack() 
{
  while(head)
  {  
    temp = head->next;
    delete head;
    head = temp;
  }
}


/*************************************************************************
***                               Push                                 ***
*************************************************************************/
//Push function to add a word to the stack
//Returns 1 for success, 0 for failure.
int card_stack::push(card *crd)
{
  if(head)        //if not empty
  {
    temp= new LLL_node;          //allocate 

    temp->name = crd->name;      //copy data
    temp->color = crd->color;    
    temp->next = head;           //insert the new node
    head = temp;           
    temp =NULL;
    return 1;
  }
  else if(!head)      //if empty
  {
    head= new LLL_node;          //allocate new memory for head
    head->name = crd->name;      //copy data
    head->color = crd->color;    
    head->next=NULL;
    return 1;
  }
  else
    return 0;
}

/*************************************************************************
***                               Pop                                  ***
*************************************************************************/
//pop function to remove the first node from thestack
//Returns 1 for success, 0 for failure.
int card_stack::pop()
{
  if(head)         //if not empty
  {
    temp=head->next;     //set temp to the next node
    delete head;         //delete first node
    head=temp;          //set head to temp
    temp=NULL;
    return 1;
  }
  else
    return 0;
}
    
/*************************************************************************
***                             Is Empty                               ***
*************************************************************************/
//to check if the stack is empty or not
//Returns 1 if the stack is empty, 0 if not.
int card_stack::isEmpty()
{
  if(head)     //if not empty
    return 0;
  else          //if empty
    return 1;    
}

/*************************************************************************
***                            Get Top                                 ***
*************************************************************************/
//copies the first node on the stack and returns a pointer the the copy.
//for success it returns a pointer to copy of the top node. For failure it 
//returns NULL; 
card *card_stack::gettop()
{
  card *temp;

  if(head)          //if not empty
  {
    temp=new card;        //allocate new memory 
    temp->name = head->name;      //copy data
    temp->color = head->color;      //copy data
    return temp;        //return pointer to new memory
  }
  else
    return NULL;
}
