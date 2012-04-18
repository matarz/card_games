/* 
   Author: Zakaria Almatar
   Date: 10/24/09
   Class: CS202
   Assignment: Program#1
*/
/*
   File name: trees.cpp
   Functions: This file has functions definitions of:
              class inner_tree:
                 -Constructor 
                 -Destructor
                 -Is empty: checks if the tree is empty
                 -add: adds a card to the tree
                 -removes: removes a card from the tree
                 -display: returns a LLL of the cards in the tree
                 -destroy: destroys the tree
              class outer tree:
                 -Constructor 
                 -Destructor
                 -Is empty: checks if the tree is empty
                 -add: adds a card to the tree
                 -removes: removes a card from the tree
                 -display: returns a LLL of the cards in the tree
                 -destroy: destroys the tree
*/

#include <cstdlib>
#include <iostream>
#include "header.h"
using namespace std;

/*************************************************************************
***                   inner_tree constructor                           ***
*************************************************************************/
//sets root and parent to NULL
inner_tree::inner_tree()
{
  root = NULL;
  parent =NULL;                      
}

/*************************************************************************
***                      inner_tree destructor                         ***
*************************************************************************/
//deallocates the tree 
inner_tree::~inner_tree()
{
  destroy_tree(root);
}

/*************************************************************************
***                       inner_tree is_empty                          ***
*************************************************************************/
//checks if the tree is empty or not
//returns 1 for empty, 0 otherwise. 
int inner_tree::is_empty()
{
  if(root)   
    return 0;
  else
    return 1;
}

/*************************************************************************
***                          inner_tree ADD                            ***
*************************************************************************/
//calls insert and supply it with root and data. Always returns 1. 
int inner_tree::add(card *crd)  
{
  insert(root, crd);
  return 1;  
}

/*************************************************************************
***                      inner_tree Remove                             ***
*************************************************************************/
//removes a tree node
//returns 1 for success, 0 for failure. 

int inner_tree::remove(card *crd)
{
  int flag=0; //values: 1 = root, 2 = right node, 3 = left node
  inn_tree_node *temp;          //temporary pointer
  inn_tree_node *successor;     //inorder successor
  inn_tree_node *successor_p;   //parent of inorder successor
  
  //calling find which will return a pointer to the node needed(if found)
  temp = find(root,root,crd);

  if(!temp)     //if match wasn't find or tree was empty
    return 0;   //return failer
  else          //if node was found
  {
    if(temp == root)              //if it the root node set flag to 1
      flag =1;
    else if(temp==parent->right)  //if it's a right node set flag to 2
      flag =2; 
    else if(temp==parent->left)   //if it's a left node set flag to 3
      flag =3;        

    if(!temp->right && !temp->left)  //if node has no children
    {                                //delete the node and set its parent
      delete temp;                   //pointer to NULL
      temp=NULL;
      if(flag==1)
        root = NULL;
      else if(flag==2)
        parent->right=NULL;
      else if(flag==3)
        parent->left=NULL;

      return 1;
    }  
    else if(!temp->right && temp->left)     //if node has left child
    {                                       //adopt child by parent and 
      if(flag==1)                           //delete the node
        root = temp->left;
      else if(flag==2)
        parent->right=temp->left;
      else if(flag==3)
        parent->left=temp->left;

      delete temp;
      temp=NULL;   
      return 1;
    }
    else if(temp->right && !temp->left)      //if node has right child
    {                                        //adopt child by parent and 
      if(flag==1)                            //delete the node
        root = temp->right;
      else if(flag==2)
        parent->right=temp->right;
      else if(flag==3)
        parent->left=temp->right;

      delete temp;
      temp=NULL;   
      return 1;
    }
    else if(temp->right && temp->left)     //if node has two children find  
    {                                      //the inorder successor and copy
      successor = temp->right;             //its data into the target node then
      if(!successor->left)                 //delete successor
      {
        copy_data(temp, successor);
        temp->right=successor->right;
        delete successor;     //deallocate successor
        successor =NULL;
        return 1;
      }
      else
      {  
        do    //do loop to find the inorder successor and its parent
        {
          successor_p = successor;        
          successor = successor->left;        
        }
        while(successor->left);

        copy_data(temp, successor);
        successor_p->left = successor->right;
        delete successor;       //deallocate successor
        successor =NULL;
        return 1;
      }
    }
  }
}

/*************************************************************************
***                     inner_tree Public Display                      ***
*************************************************************************/
//calls displayAll and supply it with root.
//returns a head pointer to a LLL holding the data of the tree
LLL_node *inner_tree::display_all()
{
  LLL_node *head=NULL;
  LLL_node *cur;
  displayAll(root, head, cur);
  return head;        
}

/*************************************************************************
***                   inner_tree Destroy tree                         ***
*************************************************************************/
//deallocates all nodes in a tree. 
void inner_tree::destroy()
{
 if(root)
   destroy_tree(root);
}

/*************************************************************************
***                   inner_tree Private Display                       ***
*************************************************************************/
//takes a root of a tree and assign the data of its nodes into a LLL

void inner_tree::displayAll(inn_tree_node*&root1, LLL_node*&head, LLL_node*&cur)
{
  if(root1)   //if tree is not empty
  {
    displayAll(root1->left, head, cur);    //go left

    if(head)   //if a LLL exists
    {
      cur->next = new LLL_node;    //add a node at the end
      cur = cur->next;
      copy_data(cur, root1);   //copy the data into the node
      cur->next=NULL;
    }
    else      //if a LLL doesn't exist
    {
      head = new LLL_node;         //add a node to head
      copy_data(head, root1);      //copy the data into the node
      head->next=NULL;
      cur = head; 
    }
    displayAll(root1->right, head, cur);   //go right 
  }
}

/*************************************************************************
***                       inner_tree Insert                            ***
*************************************************************************/
//takes root of a tree and data then insert the data into the tree. 

void inner_tree::insert(inn_tree_node *&root1, card *&crd)
{
  if(!root1)  //if empty
  {
    //allocate memory and copy data into the root
    root1=new inn_tree_node;  
    copy_data(root1, crd);
    root1->left = NULL;
    root1->right = NULL;
  }
  else // if not empty
  {
    if(root1->name > crd->name)           //if node's data larger go left
      insert(root1->left, crd);
    else  //if the same do comparison with the first name
      insert(root1->right, crd);
  }
}

/*************************************************************************
***                    inner_tree Copy Data                            ***
*************************************************************************/
//copies data to a tree node
void inner_tree::copy_data(inn_tree_node *&to, card *&from)
{
  to->name = from->name;
  to->color = from->color;
}

/*************************************************************************
***                    inner_tree Copy Data                            ***
*************************************************************************/
//copies data from a tree node to a LLL node
void inner_tree::copy_data(LLL_node *&to, inn_tree_node *&from)
{
  to->name = from->name;
  to->color = from->color;
}

/*************************************************************************
***                    inner_tree Copy Data                            ***
*************************************************************************/
//copies data from a tree node to another tree node
void inner_tree::copy_data(inn_tree_node *&to, inn_tree_node *&from)
{
  to->name = from->name;
  to->color = from->color;
}

/*************************************************************************
***                   inner_tree Find a node                           ***
*************************************************************************/
//Finds a tree node, assigns a pointer to its parent and then return a pointer
//to the node (if found)
//returns a NULL for failur or a pointer to a node otherwise. 

inn_tree_node *inner_tree::find(inn_tree_node*&root1, inn_tree_node*&par, card *&crd)
{
  if(!root1)           //if node 
    return NULL;     //returns NULL
  else  //if not
  {
    if(root1->name > crd->name)              //if data is larger than node's
      return find(root1->left,root1,crd);    // data go right
    else if (root1->name < crd->name)          //if data is smaller than node's 
      return find(root1->right,root1,crd);     //data go left
    else   //if equal (we found our target)
      {
        parent = par;  //set parent to parent of the node
        return root1;   //return the node
      }
  }
}

/*************************************************************************
***                      inner_tree Destroy tree                       ***
*************************************************************************/
//deallocates all nodes in a tree. 
void inner_tree::destroy_tree(inn_tree_node *&root1)
{
  if(root1)     
  {
     destroy_tree(root1->left);
     destroy_tree(root1->right);
     delete root1;                
  }
}

//######################################################################//
//######################################################################//


/*************************************************************************
***                     outter_tree Constructor                        ***
*************************************************************************/
//sets root and parent to NULL
outter_tree::outter_tree()
{
  root = NULL;
  parent =NULL;                      
}

/*************************************************************************
***                    outter_tree Destructor                          ***
*************************************************************************/
//deallocates the tree 
outter_tree::~outter_tree()
{
  destroy_tree(root);
}

/*************************************************************************
***                      outter_tree is empty                          ***
*************************************************************************/
//checks if the tree is empty or not
//returns 1 for empty, 0 otherwise. 
int outter_tree::is_empty()
{
  if(root)   
    return 0;
  else
    return 1;
}

/*************************************************************************
***                       outter_tree ADD                              ***
*************************************************************************/
//calls insert and supply it with root and data. Always returns 1. 
int outter_tree::add(card *crd)  
{
  insert(root, crd);
  return 1;  
}

/*************************************************************************
***                     outter_tree Remove                             ***
*************************************************************************/
//removes a contact
//returns 1 for success, 0 for failure. 
int outter_tree::remove(card *crd)
{
  int flag=0; //values: 1 = root, 2 = right node, 3 = left node
  out_tree_node *temp;          //temporary pointer
  out_tree_node *successor;     //inorder successor
  out_tree_node *successor_p;   //parent of inorder successor
  
  //calling find which will return a pointer to the node needed(if found)
  temp = find(root,root,crd);

  if(!temp)     //if match wasn't find or tree was empty
    return 0;   //return failer
  else          //if node was found
  {
    if(!temp->tree->is_empty())
      temp->tree->remove(crd);
    
    if(temp->tree->is_empty())
    {    
      if(temp == root)              //if node is root set flag to 1
        flag =1;
      else if(temp==parent->right)  //if it's a right node set flag to 2
        flag =2; 
      else if(temp==parent->left)   //if it's a left node set flag to 3
              flag =3;        

      if(!temp->right && !temp->left)  //if node has no children
      {                                //delete the node and set its parent
        delete temp;                   //pointer to NULL
        temp=NULL;
        if(flag==1)
          root = NULL;
        else if(flag==2)
          parent->right=NULL;
        else if(flag==3)
          parent->left=NULL;
 
        return 1;
      }  
      else if(!temp->right && temp->left)     //if node has left child
      {                                       //adopt child by parent and 
        if(flag==1)                           //delete the node
          root = temp->left;
        else if(flag==2)
          parent->right=temp->left;
        else if(flag==3)
          parent->left=temp->left;
 
        delete temp;
        temp=NULL;   
        return 1;
      } 
      else if(temp->right && !temp->left)      //if node has right child
      {                                        //adopt child by parent and 
        if(flag==1)                            //delete the node
          root = temp->right;
        else if(flag==2)
          parent->right=temp->right;
        else if(flag==3)
          parent->left=temp->right;

        delete temp;
        temp=NULL;   
        return 1;
      }
      else if(temp->right && temp->left)     //if node has two children find  
      {                                      //the inorder successor and copy
        successor = temp->right;             //its data into the target node then
        if(!successor->left)                 //delete successor
        {
          copy_data(temp, successor);
          temp->right=successor->right;
          delete successor;     //deallocate successor
          successor =NULL;
          return 1;
        }
        else
        {  
          do    //do loop to find the inorder successor and its parent
          {
            successor_p = successor;        
            successor = successor->left;        
          }
          while(successor->left);
 
          copy_data(temp, successor);
          successor_p->left = successor->right;
          delete successor;       //deallocate successor
          successor =NULL;
          return 1;
        }
      }
    }  
  }
}

/*************************************************************************
***                  outter_tree Public Display                        ***
*************************************************************************/
//calls displayAll and supply it with root.
//returns a head pointer to a LLL holding the data of the tree
LLL_node *outter_tree::display_all()
{
  LLL_node *head=NULL;
  LLL_node *cur;
  displayAll(root, head, cur);
  return head;        
}

/*************************************************************************
***                   outter_tree Destroy                              ***
*************************************************************************/
//deallocates all nodes in a tree. 
void outter_tree::destroy()
{
 if(root)
   destroy_tree(root);
}

/*************************************************************************
***                 outter_tree Private Display                        ***
*************************************************************************/
//takes a root of a tree and assign the data of its nodes into a LLL
//Or it takes a root and a head to a LLL. copy the tree data into a LLL and 
//combine the new LLL with the one that was given.
void outter_tree::displayAll(out_tree_node*&root1, LLL_node*&head, LLL_node*&cur)
{
  if(root1)   //if tree is not empty
  {
    displayAll(root1->left, head, cur);    //go left

    if(head)   //if a LLL exists
    {
      cur->next = root1->tree->display_all();    //add a node at the end
      while(cur->next)
        cur = cur->next;
    }
    else      //if a LLL doesn't exist
    {
      head = root1->tree->display_all();    //add a node to head
      cur = head; 
      while(cur && cur->next)
        cur = cur->next;
    }
    displayAll(root1->right, head, cur);   //go right 
  }
}

/*************************************************************************
***                       outter_tree Insert                           ***
*************************************************************************/
//takes root of a tree and data then insert the data into the tree. 
void outter_tree::insert(out_tree_node *&root1, card *&crd)
{
  if(!root1)  //if empty
  {
    //allocate memory and copy data into the root
    root1=new out_tree_node;  
    copy_data(root1, crd);
    root1->left = NULL;
    root1->right = NULL;
  }
  else // if not empty
  {
    if(root1->color > crd->color)           //if node's data larger go left
      insert(root1->left, crd);
    else if(root1->color < crd->color)
      insert(root1->right, crd);
    else  //if the same do comparison with the first name
      root1->tree->add(crd);
  }
}

/*************************************************************************
***                      outter_tree Copy Data                         ***
*************************************************************************/
//copies data to a tree node
void outter_tree::copy_data(out_tree_node *&to, card *&from)
{
  to->color = from->color;
  to->tree = new inner_tree;
  to->tree->add(from);
}

/*************************************************************************
***                      outter_tree Copy Data                         ***
*************************************************************************/
//copies data from a tree node to another tree node
void outter_tree::copy_data(out_tree_node *&to, out_tree_node *&from)
{
  to->color = from->color;
  to->tree = from->tree;
}

/*************************************************************************
***                  outter_tree Find a node                           ***
*************************************************************************/
//Finds a tree node, assigns a pointer to its parent and then return a pointer
//to the node (if found)
//returns a NULL for failur or a pointer to a node otherwise. 
out_tree_node *outter_tree::find(out_tree_node*&root1, out_tree_node*&par, card *&crd)
{
  if(!root1)           //if node 
    return NULL;     //returns NULL
  else  //if not
  {
    if(root1->color > crd->color)         //if data is larger than node's data go right
      return find(root1->left,root1,crd);
    else if (root1->color < crd->color)     //if data is smaller than node's data go left
      return find(root1->right,root1,crd);  
    else   //if equal
      {
        parent = par;  //set parent to parent of the node
        return root1;   //return the node
      }
  }
}

/*************************************************************************
***                   outter_tree Destroy tree                         ***
*************************************************************************/
//deallocates all nodes in a tree. 
void outter_tree::destroy_tree(out_tree_node *&root1)
{
  if(root1)     
  {
     destroy_tree(root1->left);
     destroy_tree(root1->right);
     root1->tree->destroy();
     delete root1;    
     root1=NULL;
  }
}

