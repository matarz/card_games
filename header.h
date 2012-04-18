/* 
   Author: Zakaria Almatar
   Date: 10/24/09
   Class: CS202
   Assignment: Program#1
*/
/*
   File name: header.h
   Contains: This file has the prototypes of classes and structures: 
            -Struct card: represents a card
            -Struct LLL_node: reperests a Linear Link List node
            -Struct inn_tree_node: represnts a tree node for the inner tree 
            -Struct out_tree_node: represnts a tree node for the outter tree
            -Class inner_tree: reperests a tree that sorts cards by their name
            -Class outter_tree: reperests a tree that sorts inner trees by
                                the color of their cards.
            -Class card_stack: represents a stack(pile) of cards.
            -Class hand: represents a hand (player) that takes and gives cards. 
            -Class game: has the general functions of most games. 
            -Class card game: has the general functions of card games.  
*/


#include <iostream>
#include <stdio.h>
using namespace std;

/*************************************************************************
***                        Structure card                              ***
*************************************************************************/
//a structure that holds the data of a card
struct card  
{
  char name;
  char color;     
};

/*************************************************************************
***                            LLL node                                ***
*************************************************************************/
//a node that holds the data of a card and has a pointer to a next node
struct LLL_node
{
  char name;
  char color;
  LLL_node *next;     
};

/*************************************************************************
***                       Inner tree node                              ***
*************************************************************************/
//a BST tree node that holds the data of a card and has two pointers to children
struct inn_tree_node  
{
  char name;
  char color;
  inn_tree_node *left;
  inn_tree_node *right;
};  

/*************************************************************************
***                           Inner Tree                               ***
*************************************************************************/
//a tree class that sorts cards by their name
class inner_tree
{
  public:
    inner_tree();             //sets root to NULL
    ~inner_tree();            //deallocates the tree and sets root to NULL
    int is_empty();           //checks if the tree is empty
    int add(card *crd);       //adds a card 
    int remove(card *crd);    //removes a card
    LLL_node *display_all();  //displays all cards
    void destroy();            //destroyss the tree
        
  protected:
    //displays all cards stored in the tree
    void displayAll(inn_tree_node *&root1, LLL_node*&head, LLL_node*&cur);                          
    //inserts a card
    void insert(inn_tree_node *&root1, card *&crd);            
    //copies data to a tree node;
    void copy_data(inn_tree_node *&to, card *&from);
    //copies data from a tree node to a LLL node.
    void copy_data(LLL_node *&to, inn_tree_node *&from);   
    //copies data from a tree node to another tree node;
    void copy_data(inn_tree_node *&to, inn_tree_node *&from);
    //finds a node and its parent
    inn_tree_node *find(inn_tree_node *&root, inn_tree_node *&par, card *&crd);
    //deletes the tree
    void destroy_tree(inn_tree_node *&root1);
    
    inn_tree_node *root;      //root pointer
    inn_tree_node *parent;    //used for removal
};

/*************************************************************************
***                      Outter tree node                              ***
*************************************************************************/
//a BST tree node that holds the color of a card and has a pointer to a tree
//and two pointers to children.
struct out_tree_node 
{
  char color;
  inner_tree *tree;
  out_tree_node *left;
  out_tree_node *right;
};

/*************************************************************************
***                         Outter Tree                                ***
*************************************************************************/
//a tree class that sorts inner trees based on the color of their cards.
/* what this tree does is that it adds, removes and displays inner trees which 
   has a list of cards. the sorting is based on the color of which the cards of 
   each tree have. 
*/
class outter_tree
{
  public:
    outter_tree();             //sets root to NULL
    ~outter_tree();            //deallocates the tree and sets root to NULL
    int is_empty();            //checks if the tree is empty
    int add(card *crd);        //adds a card
    int remove(card *crd);     //removes a card
    LLL_node *display_all();   //displays all cards
    void destroy();            //destroyss the tree
        
  protected:
    //takes a card and adds it to the tree
    void displayAll(out_tree_node *&root1, LLL_node*&head, LLL_node*&cur);
    //inserts a card
    void insert(out_tree_node *&root1, card *&crd);
    //copies data to a tree node;
    void copy_data(out_tree_node *&to, card *&from);
    //copies data from a tree node to another tree node;
    void copy_data(out_tree_node *&to, out_tree_node *&from);
    //finds a node and its parent
    out_tree_node *find(out_tree_node *&root, out_tree_node *&par, card *&crd);
    //deletes the tree
    void destroy_tree(out_tree_node *&root1);
    
    out_tree_node *root;      //root pointer
    out_tree_node *parent;    //used for removal
};

/*************************************************************************
***                          Card Stack                                ***
*************************************************************************/
//a stack class that adds, removes and displays a stack(pile) of cards.
class card_stack
{
  public:

    //constructor: sets the nodes to NULL
    card_stack(); 
    
    //stack destructor: deallocates the stack
    ~card_stack(); 

    //Push function to add a card to the stack
    int push(card *crd);

    //pop function to remove the first card from the stack
    int pop();
    
    //to check if the stack is empty or not
    int isEmpty();

    //returns a pointer to a copy first word on the stack
    card *gettop();

   private:
    LLL_node *head;  //pointer to first node
    LLL_node *temp;  //a temorary pointer
};

/*************************************************************************
***                             Hand                                   ***
*************************************************************************/
//A class that represents a hand (player) that takes a card, gives a card, and
//shows all cards.
class hand
{
  private:
    outter_tree *tree;   //pointer to an outter tree
  public:
    hand();
    ~hand();
    void take_card(card *crd);    //adds a card
    int remove_card(card *crd);   //removes a card
    int is_empty();               //checks if empty
    LLL_node *show_hand();        //displays all cards
};


//a class repersenting a game
class game
{
  public:
    game();
    ~game();
    void start();  //start game
    void quit();   //end game
    int save();   //save
};


//class representing a card game and inheriting class game
class card_game: public game
{
  public:
    card_game();     //constructor
    ~card_game();    //destructor
    card_stack *shuffle(card *deck, int len);   //shuffler
    int deal(card_stack *deck, hand *hands, int n_hands, int n_cards);
};


