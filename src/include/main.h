#ifndef __MAIN_H
#define __MAIN_H
#include "stack.h"

/* permet de récupérer les arguments */
typedef struct args_t {
  int nthreads;
  int consonne;
  char *output;
  stack_t *input;
} Arg;

struct args_t init_args(int argc, char *argv[]);

#endif
