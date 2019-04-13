#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_t.h"


int main() {
  struct stack_t *test = malloc(sizeof(struct stack_t));
  if (test == NULL){
    printf("Ne marche pas\n");
    return 0;
  }
  struct node *defiler = malloc(sizeof(struct node));
  char *p = "Premier";
  push(test, p);
  push(test, "file.txt");
  pop(test);
  push(test, "route");
  push(test, "casos");
  push(test, "erlang");
  defiler = test->head;
  while(defiler != NULL){
    printf("c'est la stack %s, %d\n", defiler->filename, test->length);
    defiler = defiler->next;}
  return 1;
}
