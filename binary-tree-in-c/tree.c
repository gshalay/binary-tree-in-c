/* Filename: tree.c
 * Student Name: Greg Shalay (UoG: 1096689)
 * Description: Implementation file for tree.h. Will implement varying CRUD operations for a binary tree.
 * Will also search the binary tree for particular node data.
 */

#include "tree.h"

/* BASIC FUCNTIONS */
struct Performance * newPerformance(){
  struct Performance * performance;
  
  performance = (struct Performance *) malloc(sizeof(struct Performance));
  
  if (performance != NULL){
    performance->reads = 0;
    performance->writes = 0;
    performance->mallocs = 0;
    performance->frees = 0;
    
    return performance;
  }
  else{
    fprintf(stderr, "Failed to allocate memory for Performance struct.\n");
    exit(EXIT_FAILURE);
  }
}
  
void attachNode(struct Performance * performance, struct Node ** node_ptr, void * src, unsigned int width){
  struct Node * newNode;
  
  newNode = (struct Node *) malloc(sizeof(struct Node));
  
  if(newNode != NULL){
    newNode->data = (void *) malloc(width);
      
    if(newNode->data != NULL){
      memcpy(newNode->data, src, width);
      
      newNode->lt = NULL;
      newNode->gte = NULL;
    
      *node_ptr = newNode; // Should attach the node to the specified location.
      
      performance->mallocs++;
      performance->writes++;
      
    }
    else{
      fprintf(stderr, "Failed to allocate memory for the new node data.\n");
      exit(EXIT_FAILURE);
    }
  }
  else{
    fprintf(stderr, "Failed to allocate memory for the new node.\n");
    exit(EXIT_FAILURE);
  }

}
  
int comparNode(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * target){
  performance->reads++;
  return compar(target, ((*node_ptr)->data)); // Pass the data of the node pointed to by node_ptr.;
}
  
struct Node ** next(struct Performance * performance, struct Node ** node_ptr, int direction){
  if(isEmpty(performance, node_ptr)){
    fprintf(stderr, "Cannot find next node, tree provided is empty.\n");
    exit(EXIT_FAILURE);
  }
  else{
    if(direction < 0){ // Return lt
      performance->reads++;
      return (&((*node_ptr)->lt));
    }
    else if(direction >= 0){ // Return gte
      performance->reads++;
      return (&((*node_ptr)->gte));
    }
    else{
      fprintf(stderr, "Cannot determine next node. The direction provided is invalid.\n");
      exit(EXIT_FAILURE);
    }
  }

}
  
void readNode(struct Performance * performance, struct Node ** node_ptr, void * dest, unsigned int width){
  if(isEmpty(performance, node_ptr)){
    fprintf(stderr, "Cannot read node, node provided is empty.\n");
    exit(EXIT_FAILURE);
  }
  else{
    memcpy(dest, ((*node_ptr)->data), width); // Copy node data to the dest.
    
    performance->reads++;
  }
}
  
void detachNode(struct Performance * performance, struct Node ** node_ptr){
  struct Node ** nodeToDetach = node_ptr;
 
  if(isEmpty(performance, node_ptr)){
    fprintf(stderr, "Cannot detach node, node provided is empty.\n");
    exit(EXIT_FAILURE);
  }
  else{
    free(((*nodeToDetach)->data));
    free(*nodeToDetach);
    
    *node_ptr = NULL;  
    
    performance->frees++;
  }
}

int isEmpty(struct Performance * performance, struct Node ** node_ptr){
  if(*node_ptr == NULL){
    return 1;
  }
  else{
    return 0;
  }
}
  
  
/* DERIVED FUNCTIONS */
void addItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * src, 
             unsigned int width){
  struct Node ** tempNode = node_ptr;
  
  int direction = LEFT;
  
  while(!isEmpty(performance, tempNode)){
    direction = comparNode(performance, tempNode, compar, src);
    
    tempNode = next(performance, tempNode, direction);
  }
  
  //Once here, we are at a NULL node, so attach one.
  attachNode(performance, tempNode, src, width);
}
	       
void freeTree(struct Performance * performance, struct Node ** node){
  int direction = LEFT;
  
  struct Node ** leftChild; 
  struct Node ** rightChild;
  
  //Recursive Case: node != NULL
  if(!isEmpty(performance, node)){
    leftChild = next(performance, node, direction);
    freeTree(performance, leftChild);
    
    direction = RIGHT;
    rightChild = next(performance, node, direction);
    freeTree(performance, rightChild);
    
    detachNode(performance, node);  
  }
  
  //Non-Recursive Case: node == NULL
  //Do nothing.
  else{
    return;
  }
}
  
  
/* THE LAST 20% */  
int searchItem(struct Performance * performance, struct Node ** node_ptr, int (*compar)(const void *, const void *), void * target, 
                 unsigned int width){
  int direction;
  int result;

  //Recursive Case: Current node is non-null.
  if(!isEmpty(performance, node_ptr)){
    result = comparNode(performance, node_ptr, compar, target);
    
    if(result == MATCH_FOUND){
      readNode(performance, node_ptr, target, width);
      return 1;
    }
    else if(result < MATCH_FOUND){
      direction = LEFT;
      return searchItem(performance, next(performance, node_ptr, direction), compar, target, width);
      
    }
    else if(result > MATCH_FOUND){
      direction = RIGHT;
      return searchItem(performance, next(performance, node_ptr, direction), compar, target, width);
    }
    else{
      fprintf(stderr, "Something went wrong when determining compar result. Cannot find item.\n");
      exit(EXIT_FAILURE);
    }
  }

  //Non-Recursise Case: Current node is null or match was found.
  return 0;
}