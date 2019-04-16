#ifndef __MAIN_H
#define __MAIN_H

#include "stack.h"

typedef struct arg_prod_cons{
  stack_t *stack_file;
  int in;
  int out;
  int numb_threads;
  uint8_t  **buffer;
  int consonne;
}arg_prod_cons_t;

#endif
