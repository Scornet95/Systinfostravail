#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_t.h"
#include <unistd.h>
#include <getopt.h>

void init_structure(struct args_t *test){
  if (test == NULL){
    exit(EXIT_FAILURE);
  }
  test->input = malloc(sizeof(struct stack_t));
  test->nthreads = 1;
  test->consonne = 0;
  test->output = NULL;
  test->input->head->filename = NULL;
}
void init_args(int argc, char * const argv[], struct args_t *test){
  int opt;
  while ((opt = getopt(argc, argv, "t:o:c"))){
    switch(opt){
      case 't':
        test->nthreads = (int)optarg;
        break;
      case 'c':
        test->consonne = 1;
        break;
      case 'o' :
        strcpy(test->output, optarg);
        break;
    }
  for (; optind < argc; optind++){
    push(test->input, argv[optind]);
}
}
}
int main(int argc, char * const argv[]) {
  struct args_t  *test = malloc(sizeof(struct args_t));
  init_structure(test);
  init_args(argc, argv, test);
  printf("nombre de threads %d %d \n", test->nthreads, test->consonne);
  return 1;
}
