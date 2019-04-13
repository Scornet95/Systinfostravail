#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_t.h"


int main() {
  struct args_t *test = malloc(sizeof(struct args_t));
  if (test == NULL){
    printf("Ne marche pas\n");
    return 0;
  }
  test->nthreads = 2;
  test->input = malloc(sizeof(struct stack_t));
  if (test->input == NULL){
    exit(EXIT_FAILURE);
  }
  push(test->input, "third");
  push(test->input, "second");
  push(test->input, "first");
  pop(test->input);
  test->consonne = 1;
  test->output = "fichier.txt";
  printf("c'est la structure avec %d threads, qui recherche des %d qui a un output du nom de %s dont le premier node est %s et qui a une longueur de stack de %d\n",test->nthreads, test->consonne,test->output, test->input->head->filename, test->input->length);
  return 1;
}
