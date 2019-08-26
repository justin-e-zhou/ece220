#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/********************************INTRO PARAGRAPH*****************************
 * The sparsemat program implements load_tuples, gv_tuples, set_tuples,
 * add_tuples, mult_tuples, save_tuples, and destroy_tuples.
 * The load_tuples function loads a matrix from a given file name.
 * The gv_tuples returns the value in a cell given its row and column.
 * The set_tuples function fills a cell of given row and col with the given
 * value. If the given value is 0, it does not create a new tuple, and if
 * the cell was previously a zero, it creates a new tuple sorted into the
 * correct position.
 * The add_tuples function adds two matricies together and returns a matrix
 * with the two added.
 * The mult_tuples function multiplies two matricies together and returns a
 * matrix with the two multiplied.
 * The save_tuples function saves a matrix to a file given the file name and
 * matrix.
 * The destroy_tuples function frees all memory associated with the given
 * matrix.
 */

int removeHeadZeroes(sp_tuples_node** headptr){
  sp_tuples_node* head = *headptr;  //head of matrix
  sp_tuples_node* cur = *headptr; //current tuple
  int count = 0;  //counter
  if(head==NULL)  //if empty matrix, return 0
    return 0;
  while(head->value==0){  //if value of head is zero, remove it and change the head pointer to the next node
    cur = head->next;
    free(head);
    head = cur;
    *headptr = head;
    count++;  //increment count
  }
  return count;
}

int removeDuplicates(sp_tuples_node* head){  //remove duplicates for SORTED linked list
  sp_tuples_node* current = head;
  sp_tuples_node* next_next = NULL;  //node after the one to be deleted
  int count = 0;
  if(head==NULL)
    return 0;
  while(current->next!=NULL){ //traverse list
    if((current->row==current->next->row && current->col==current->next->col)||current->next->value==0){ //compare current row and col with next row and col and delete the next if they are the same or if the value is 0
      next_next = current->next->next;
      free(current->next);
      current->next = next_next;
      count++;
    }
    else  //advance if there are no deletions
      current = current->next;
  }
  return count;
}
sp_tuples_node* sortedMerge(sp_tuples_node* a,sp_tuples_node* b){
  sp_tuples_node* result = NULL;
  if(a==NULL)
    return b;
  else if(b==NULL)
    return a;

  if(a->row < b->row){  //sort by row first
    result = a;
    result->next = sortedMerge(a->next,b);
  }
  else if(a->row > b->row){
    result = b;
    result->next = sortedMerge(a,b->next);
  }
  else if(a->col < b->col){ //sort by col second
    result = a;
    result->next = sortedMerge(a->next,b);
  }
  else if(a->col > b->col){
    result = b;
    result->next = sortedMerge(a,b->next);
  }
  else{       //if r and c are same, use b
    result = b;
    result->next = sortedMerge(a,b->next);
  }
  return result;
}
//split the list into two halves
void split(sp_tuples_node* source, sp_tuples_node** front, sp_tuples_node** back){
  sp_tuples_node* fast;
  sp_tuples_node* slow;
  slow = source;
  fast = source->next;
  while(fast!=NULL){    //fast advances 2 nodes, slow advances 1
    fast = fast->next;
    if(fast!=NULL){
      slow = slow->next;
      fast = fast->next;
    }
  }
  *front = source;    //front is the first
  *back = slow->next; //back is the next one after slow
  slow->next = NULL;
}

void mergeSort(sp_tuples_node** headptr){
  sp_tuples_node* head = *headptr;
  sp_tuples_node* a;
  sp_tuples_node* b;
  if((head==NULL)||(head->next==NULL)) //base case
    return;
  split(head,&a,&b);  //split list in half
  mergeSort(&a);      //recurse for first half
  mergeSort(&b);      //recurse for second half
  *headptr = sortedMerge(a,b); //join the two halves and sort
}

sp_tuples * load_tuples(char* input_file)
{
  int row,col;
  double val;
  sp_tuples_node* prev = NULL;     //prev node pointer
  sp_tuples* tuples = malloc(sizeof(sp_tuples));  //allocate memory for tuples
  FILE *file = fopen(input_file,"r"); //open file
  fscanf(file,"%d %d\n",&(tuples->m),&(tuples->n));   //get row and cell data
  tuples->nz = 0;                               //set non-zeroes to 0
  sp_tuples_node* first_tuple = malloc(sizeof(sp_tuples_node));   //allocate memory for 1st node
  if(fscanf(file,"%d %d %lf\n",&row,&col,&val)!=EOF){  //if matrix is not blank
    if(val!=0){                               //if first val!=0
      tuples->tuples_head = first_tuple;     //point head to first tuple
      (tuples->nz)++;                        //increment nz count
      prev = first_tuple;                    //set prev node to 1st
    }
    else{
      free(first_tuple);
      tuples->tuples_head = NULL;
    }
  }
  else{                                    //else
    tuples->tuples_head = NULL;            //head pointer = NULL
    free(first_tuple);                     //free first_tuple
    return tuples;                         //return tuple pointer
  }
  while(fscanf(file,"%d %d %lf\n",&row,&col,&val)!=EOF){    //while there are still lines to read
    if(val!=0){ //if value is not zero
      sp_tuples_node* next_tuple = malloc(sizeof(sp_tuples_node));  //allocate memory for a new node next_tuple
      if(tuples->tuples_head==NULL){
        tuples->tuples_head = next_tuple;
      }
      prev->next = next_tuple;      //the previous node now points to the new node
      prev = next_tuple;            //prev now points to new node
      next_tuple->row = row;        //initialize the fields for the new node
      next_tuple->col = col;
      next_tuple->value = val;
      tuples->nz++;
    }
  }

  mergeSort(&(tuples->tuples_head)); //sort
  (tuples->nz) = tuples->nz - removeDuplicates(tuples->tuples_head);  //delete any duplicate cells
  (tuples->nz) = tuples->nz - removeHeadZeroes(&(tuples->tuples_head)); //remove any zeroes on the head

  fclose(file);
  prev->next = NULL;  //once there are no more values to read, the prev node point to NULL
  return tuples;      //return
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  sp_tuples_node* node = mat_t->tuples_head; //set node to head
  while(node!=NULL){  //while node is not null
    if(node->row==row && node->col==col){ //if row and col match
      return (node->value);    //reutrn value of tuple
    }
    node = node->next;    //otherwise, point node to next tuple
  }
  return 0; //if node is null, return 0
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  sp_tuples_node* current = mat_t->tuples_head;
  sp_tuples_node* next_next = NULL;
  while(current->next!=NULL){ //traverse thru list
    if(current->next->row==row && current->next->col==col && value==0){ //if value is 0 and it matches a cell
      next_next = current->next->next;  //set current->next to one after next
      free(current->next);    //free next node
      current->next = next_next;
      return;
    }
    else if(current->next->row==row && current->next->col==col && value!=0){  //if value is not 0 and it matches a cell
      current->next->value = value; //set next cell value to value
      return;
    }
    current = current->next;  //increment
  }
  if(value==0){ //if cell is not already initialized and value is 0, exit
    return;
  }
  current->next = malloc(sizeof(sp_tuples_node)); //allocate mem for new cell
  current = current->next;  //put it on the end of the list
  current->row = row;
  current->col = col;
  current->value = value;
  current->next = NULL; //initialize the fields
  mat_t->nz++;  //increment nz
  mergeSort(&(mat_t->tuples_head)); //sort
  return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE* file = fopen(file_name,"w");  //create file
  sp_tuples_node* current = mat_t->tuples_head;
  fprintf(file,"%d %d\n",mat_t->m,mat_t->n);  //write row and cols to file
  while(current!=NULL){ //while not at end of list
    fprintf(file,"%d %d %lf\n",current->row,current->col,current->value); //write row col and value
    current = current->next;  //increment
  }
  fclose(file); //close file
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
  sp_tuples *matC = malloc(sizeof(sp_tuples));
  sp_tuples_node *next_tuple = NULL;
  sp_tuples_node *prev = NULL;
  sp_tuples_node *curA = matA->tuples_head; //set curA to head of A
  sp_tuples_node *curB = matB->tuples_head; //set curB to head of B
  matC->m = matA->m;  //set size of matC
  matC->n = matA->n;
  matC->nz = 0;
  if(curA==NULL && curB==NULL){ //if A and B are empty, C is empty
    matC->tuples_head = NULL;
    return matC;
  }
  sp_tuples_node* first_node = malloc(sizeof(sp_tuples_node));  //allocate memory for first node
  matC->tuples_head = first_node;
  if(curA!=NULL){ //if A is not empty
    first_node->row = curA->row;  //fill first node with first node of A
    first_node->col = curA->col;
    first_node->value = curA->value;
    curA = curA->next;  //increment curA
    matC->nz++; //increment nz
  }
  else{ //else if A is empty
    first_node->row = curB->row;  //fill first node with first node of B
    first_node->col = curB->col;
    first_node->value = curB->value;
    curB = curB->next;
    matC->nz++;
  }
  sp_tuples_node *curC = first_node;  //set curC to first node
  prev = first_node;  //set prev to first node
  while(curA!=NULL){  //while curA!=NULL
    next_tuple = malloc(sizeof(sp_tuples_node));  //allocate memory for next tuple
    prev->next = next_tuple;  //set prev->next to next tuple
    prev = next_tuple;  //set next tuple to prev
    next_tuple->row = curA->row;  //initialize new tuple to next node in A
    next_tuple->col = curA->col;
    next_tuple->value = curA->value;
    matC->nz++;
    curA = curA->next; //increment curA
  }
  prev->next = NULL;  //once end of A is reached, set prev->next to NULL
  curC = first_node;  //set curC to first node again
  while(curB!=NULL){  //while curB!=NULL
    while(curC!=NULL){  //loop thru curC
      if(curB->row==curC->row && curB->col==curC->col){ //if row and cols equal, add val of B to C
        curC->value+=curB->value;
        break;
      }
      prev = curC;  //if the row/col do not equal set prev to curC
      curC = curC->next;  //and increment curC
    }
    if(curC==NULL){ //if reached the end of matrix C without adding
      prev->next = malloc(sizeof(sp_tuples_node));  //allocate new memory for next node
      prev->next->row = curB->row;  //initialize it with B
      prev->next->col = curB->col;
      prev->next->value = curB->value;
      prev->next->next = NULL;
      matC->nz++;
    }
    curC = first_node;  //set curC back to first_node
    curB = curB->next;  //increment curB
  }
  mergeSort(&(matC->tuples_head));  //sort
	return matC;
}


sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
    return matA;

}



void destroy_tuples(sp_tuples * mat_t){
  sp_tuples_node* current = mat_t->tuples_head;
  sp_tuples_node* next;
  while(current!=NULL){
    next = current->next;
    free(current);
    current = next;
  }
  return;
}






