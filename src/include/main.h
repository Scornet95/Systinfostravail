#ifndef __MAIN_H
#define __MAIN_H


struct stack_t{
  node *head;
  int length;
};
struct node { /*créer un noeud dans la pile reprenant les files*/
  char *filename;
  node *next;
};

int pop(struct stack_t* stack){
  if (stack->head == NULL){
    return 0;
  }
  if (stack->head->next == NULL){
    stack->head = NULL;
    stack->length--;
    free stack.head;
    return 0;
  }
  struct node* copie = malloc(sizeof(struct node));
  if (copie == NULL){
    return -1;
  }
  copie = stack->head;
  stack->head = copie->next;
  free(copie);
  return 1;
};

void push(struct stack_t* stack, const char* filename);{
  struct node Newelement = malloc(sizeof(struct node));
  if (Newelement == NULL){
    exit(EXIT_FAILURE);
  }
  strncpy(Newelement->filename, filename);
  Newelement->next = stack->head;
  stack->head = Newelement;
  stack->length++;
}


struct args_t{ /* permet de récupérer les arguments */
  int nthreads = 1;
  int consonne = 0;
  char *output = NULL;
  stack_t *input;
};

struct args_t init_args(int argc, char *argv[]);




#endif
