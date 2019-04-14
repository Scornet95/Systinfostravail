#ifndef __MAIN_H
#define __MAIN_H

/* permet de récupérer les arguments */
struct args_t {
  int nthreads = 1;
  int consonne = 0;
  char *output = NULL;
  stack_t *input;
};

struct args_t* init_args(int argc, char *argv[]);

#endif
