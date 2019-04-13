#ifndef __STRUCT_T_H
#define __STRUCT_T_H
#include <string.h>
int un = 1;
struct stack_t{
  struct node *head;
  int length;
};

struct node { /*créer un noeud dans la pile reprenant les files*/
  char *filename;
  struct node *next;
};

int pop(struct stack_t* stack){
  if (stack->head == NULL){
    return 0;
  }
  if (stack->head->next == NULL){
    stack->head = NULL;
    stack->length--;
    free(stack->head);
    return 0;
  }
  struct node *copie = malloc(sizeof(struct node));
  if (copie == NULL){
    return -1;
  }
  copie = stack->head;
  stack->head = copie->next;
  stack->length--;
  free(copie);
  return 1;
}

void push(struct stack_t* stack, char* filename){
  struct node *Newelement = malloc(sizeof(struct node));
  if (Newelement == NULL){
    exit(EXIT_FAILURE);
  }
  Newelement->filename = filename;
  Newelement->next = stack->head;
  stack->head = Newelement;
  stack->length++;
}
struct args_t{ /* permet de récupérer les arguments */
  int nthreads;
  int consonne;
  char *output;
  struct stack_t *input;
};



#endif
