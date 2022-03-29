/* Filename: tree.h
 * Student Name: Greg Shalay (UoG: 1096689)
 * Description: Header file for tree.c - Contains function and struct prototypes for CRUD operations and search operations for a binary tree.
 */

#ifndef _TREE_H
  #define _TREE_H
  
  #define MATCH_FOUND 0
  #define LEFT -1
  #define RIGHT 1
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
  /* STRUCTURES */
  struct Performance{
    unsigned int reads;
    unsigned int writes;
    unsigned int mallocs;
    unsigned int frees;
  };
  
  struct Node{
    void * data;
    struct Node * lt;  // Stores values less than that of the node's data.
    struct Node * gte; // Stores values greater than or equal to the node's data.
  };
  
  /* BASIC PROTOTYPES */
  struct Performance * newPerformance();
  
  void attachNode(struct Performance * performance, struct Node ** node_ptr, void * src, unsigned int width);
  
  int comparNode(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * target);
  
  struct Node ** next(struct Performance * performance, struct Node ** node_ptr, int direction);
  
  void readNode(struct Performance * performance, struct Node ** node_ptr, void * dest, unsigned int width);
  
  void detachNode(struct Performance * performance, struct Node ** node_ptr);
  
  int isEmpty(struct Performance * performance, struct Node ** node_ptr);
  
  
  /* DERIVED PROTOTYPES */
  void addItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * src, 
               unsigned int width);
	       
  void freeTree(struct Performance * performance, struct Node ** node);
  
  
  /* THE LAST 20% */  
  int searchItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * target, 
                 unsigned int width);
#endif