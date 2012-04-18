/* 
   Author: Zakaria Almatar
   Date: 10/24/09
   Class: CS202
   Assignment: Program#1
*/
/*
   File name: funcs.cpp
   Functions: This file has functions definitions of:
              class hand:
                 -Constructor 
                 -Destructor
                 -Is empty: checks if the hand is empty
                 -take card: adds a card to the hand
                 -removes card: removes a card from the hand
                 -show hand: returns a LLL of the cards in the hand
              class card games:
                 -Constructor 
                 -Destructor
                 -Is empty: checks if the hand is empty
                 -Shuffle: shuffles a deck of cards
                 -Deal: deals cards to players(hands)
              class games:
                 -Constructor 
                 -Destructor
                 -Start: Starts the game
                 -Save: Saves the game (Not implemented)
                 -Quit: Ends the game
*/


#include <cstdlib>
#include <iostream>
#include <time.h>
#include "header.h"
using namespace std;

/*************************************************************************
***                         Hand Constructor                           ***
*************************************************************************/
//sets root and parent to NULL
hand::hand()
{
  tree = NULL;
}

/*************************************************************************
***                        Hand Destructor                             ***
*************************************************************************/
//deallocates the hand
hand::~hand()
{
  tree->destroy();
}

/*************************************************************************
***                           hand is empty                            ***
*************************************************************************/
//checks whether the hand is empty or not
int hand::is_empty()
{
  if(tree->is_empty()) 
    return 1;
  else
    return 0;   
}

/*************************************************************************
***                           hand take card                           ***
*************************************************************************/
//takes a card and adds it to the hand (tree)
void hand::take_card(card *crd)
{
  if(tree)
    tree->add(crd);
  else
  {
    tree = new outter_tree;
    tree->add(crd);    
  }     
}

/*************************************************************************
***                           hand remove card                         ***
*************************************************************************/
//removes a card from the tree(hand)
int hand::remove_card(card *crd)
{
  if(tree)
    return tree->remove(crd);
  else
    return 0; 
}

/*************************************************************************
***                         hand show hand                             ***
*************************************************************************/
//returns a pointer to LLL that holds a hand's cards sorted inorder
LLL_node *hand::show_hand()
{
  if(tree)
    return tree->display_all();
  else
    return NULL; 
}

/*************************************************************************
***                     Card game Constructor                          ***
*************************************************************************/
card_game::card_game()
{
}

/*************************************************************************
***                     Card game Denstructor                             ***
*************************************************************************/
card_game::~card_game()
{
}

/*************************************************************************
***                        Card game Shuffle                           ***
*************************************************************************/
//shuffling function. This function takes a pointer to an array of card
//structs and the length then creates an array of pointers and assigns each
//one a card's address (struct). After the assignments is done it shuffles 
//the pointer and we end up with what seems like a shuffled array of structs.
//the function then assigns the shuffled structor to stack and return a 
//pointer to that stack. the point of all this is to have a shuffled array
//without the need to copy data from one struct to another. 
card_stack *card_game::shuffle(card *deck, int len)
{
  card_stack *sh_deck;  //pointer to a stack
  card *crd_ptrs[len];  //array of pointers to struct
  card *temp;          //temp pointer
  int n;               //an int to hold the randomly generated number
    
  //assigning the addresses of array of structs elements to elemetns of 
  //array of pointers to structs
  for(int i=0;i<len;++i)
    crd_ptrs[i] = &deck[i];
    
  //shuffling pointers
  for(int i=0;i<len;++i)
  {
    srand ( time(NULL) );
    n = rand() %(len-i);
    temp = crd_ptrs[len-(i+1)]; 
    crd_ptrs[len-(i+1)] = crd_ptrs[n];
    crd_ptrs[n] = temp;
  }

  sh_deck = new card_stack;   //allocating memory for a stack
  
  //assinging the shuffled cards to the stack
  for(int i=0; i<len; ++i)
    sh_deck->push(crd_ptrs[i]);
           
  return sh_deck;  //return stack pointer
}

/*************************************************************************
***                       Card game Deal                               ***
*************************************************************************/
//takes a pointer to stack of cards and a pointer an array of class hand
//and the number of cards and the number of cards each player will get. 
//returns 1 for success. 
int card_game::deal(card_stack *deck, hand *hands, int n_hands, int n_cards)
{
  for(int i=0;i<n_cards;++i)   //loop x times for number of cards to be dealt
                               //to each player
    for(int j=0;j<n_hands;++j) // loop x times for the number of players (hands)
    { 
      //take a card from card stack and give it to a player (hand)
      hands[j].take_card(deck->gettop());  
      deck->pop();
    }
  return 1;    
}

/*************************************************************************
***                          Game Constructor                          ***
*************************************************************************/
game::game()
{
}

/*************************************************************************
***                         Game Denstructor                           ***
*************************************************************************/
game::~game()
{
}

/*************************************************************************
***                          Game Start                                ***
*************************************************************************/
//Start takes the user's choice and does one of the available options
void game::start()
{
  int choice;
  do
  {
    cout<<"\nWhat whould you like to do:\n";
    cout<<"    1-Start\n";
    cout<<"    2-Save\n";
    cout<<"    3-Quit\n";

    cin>>choice;

    if(choice == 2)
      choice = save();
    else if(choice == 3)
      quit();

  }while(choice <1 || choice > 3);
}

/*************************************************************************
***                           Game quit                                ***
*************************************************************************/
//exits the game
void game::quit()
{
  exit(1);
}

/*************************************************************************
***                          Game Save                                 ***
*************************************************************************/
int game::save()
{
  cout<<"\nSorry, this feature is not implemented.\n";
  return 4;
}




