/* 
   Author: Zakaria Almatar
   Date: 10/24/09
   Class: CS202
   Assignment: Program#1
*/
/*
   File name: main.cpp
   Functions: This file has functions definitions of:
              -main: user's main function takes info from the user and 
                     use it to run the game 
              -show card: displays a card
              -display hand: displays a hand to the screen
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"



using namespace std;

void show_card(card *crd);           //displays one card
void display_hand(LLL_node *head);   //displays a LLL of cards

/*************************************************************************
***                               Main                                 ***
*************************************************************************/
//client's functions
int main()
{
  int DECK_CARDS=100;            //number of total cards
  int CARDS_PER_PLAYER=7;        //number cards dealt to each player
  int n_player;                  //number of players
  int flag=0;                    //flag to determind an ending point
  char *player_card;             //to store the content of one card
  hand *hands;                   //a pointer to a player(hand)
  card *crd;                     //a pointer to a card
  card_stack *sh_deck;           //a pointer shuffled deck
  card_stack *discard_pile;      //a pointer to the discard_pile(cards played)
  card_game uno;                 //declaration of class card game

  //uno's set of cards: the first element is the name of the card and 
  //the second element is the color of the card. 
  card deck[]={{'0','R'},{'1','R'},{'1','R'},{'2','R'},{'2','R'},{'3','R'},
  {'3','R'},{'4','R'},{'4','R'},{'5','R'},{'5','R'},{'6','R'},{'6','R'},
  {'7','R'},{'7','R'},{'8','R'},{'8','R'},{'9','R'},{'9','R'},{'D','R'},
  {'D','R'},{'S','R'},{'S','R'},{'R','R'},{'R','R'},{'0','G'},{'1','G'},
  {'1','G'},{'2','G'},{'2','G'},{'3','G'},{'3','G'},{'4','G'},{'4','G'},
  {'5','G'},{'5','G'},{'6','G'},{'6','G'},{'7','G'},{'7','G'},{'8','G'},
  {'8','G'},{'9','G'},{'9','G'},{'D','G'},{'D','G'},{'S','G'},{'S','G'},
  {'R','G'},{'R','G'},{'0','B'},{'1','B'},{'1','B'},{'2','B'},{'2','B'},
  {'3','B'},{'3','B'},{'4','B'},{'4','B'},{'5','B'},{'5','B'},{'6','B'},
  {'6','B'},{'7','B'},{'7','B'},{'8','B'},{'8','B'},{'9','B'},{'9','B'},
  {'D','B'},{'D','B'},{'S','B'},{'S','B'},{'R','B'},{'R','B'},{'0','Y'},
  {'1','Y'},{'1','Y'},{'2','Y'},{'2','Y'},{'3','Y'},{'3','Y'},{'4','Y'},
  {'4','Y'},{'5','Y'},{'5','Y'},{'6','Y'},{'6','Y'},{'7','Y'},{'7','Y'},
  {'8','Y'},{'8','Y'},{'9','Y'},{'9','Y'},{'D','Y'},{'D','Y'},{'S','Y'},
  {'S','Y'},{'R','Y'},{'R','Y'}};


  cout<<"************************************************************\n";
  cout<<"***                Welcome to Uno202                     ***\n";
  cout<<"************************************************************\n";
  
  uno.start();  //starting the game through the base class
    
  cout<<"\nHow many players are playing?\n";
  cin>>n_player;
  hands = new hand[n_player];      //allocating memory for each player/hand

  cout<<"\nShuffling cards...\n(Hit enter when ready to play)";
  cin.get();
  cin.get();
  
  sh_deck = uno.shuffle(deck, DECK_CARDS);                 //shuffling
  uno.deal(sh_deck, hands, n_player, CARDS_PER_PLAYER);   //dealing
  discard_pile = new card_stack;                         //allocating memory
  discard_pile->push(sh_deck->gettop());      //adding a card to discard file
  sh_deck->pop();              //removing that card from the shuffled deck
  
    
  while(1)  //a loop that goes on until a break condition happens
  {
    for(int i=0;i<n_player;++i)
    {
      cout<<"\n******** It's player("<<i+1<<")'s turn. ********\n";        
      cout<<"The first card on the discard pile is: ";
      show_card(discard_pile->gettop());
      cout<<"\nYour hand is: ";
      display_hand(hands[i].show_hand());
      cout<<"\nType the exact name of the card you would like to play ";
      cout<<"then hit enter: ";
      player_card = new char[4];
      cin.getline(player_card, 4);
      cin.clear();
      
      crd = new card;
      crd->name= player_card[0];
      crd->color = player_card[2];
      
      if(hands[i].remove_card(crd))
      {
        discard_pile->push(crd);
        cout<<"Your card was played.\n";
      }
        
      if(hands[i].is_empty())
      {
        cout<<"Congrats, you \"player("<<i+1<<")\" have won!\n";                       
        flag = 1;
        break;                     
      }        
    }      
    if(flag)
      break;
  }
  cin.get();
  return 0;
}


/*************************************************************************
***                             Show card                              ***
*************************************************************************/
//takes a card struct and displays its data
void show_card(card *crd)
{
  cout<<crd->name<<"-"<<crd->color;
}

/*************************************************************************
***                           Display hand                             ***
*************************************************************************/
//takes a head pointer and displays the content of a LLL
void display_hand(LLL_node *head)
{
  LLL_node *temp = head;

  while(temp) 
  {
    cout<<temp->name<<"-"<<temp->color<<", ";
    temp=temp->next;
  }
  while(head)
  {
    temp = head->next;
    delete head;
    head = temp;
  } 
}



