#ifndef __MAIN_H
#define __MAIN_H

#include "stack.h"

typedef struct arg_buffer{
  int in;
  int out;
  int numb_threads;
  uint8_t  **buffer;
  int consonne;
}arg_buffer_t;

void ini_struct();



#endif
