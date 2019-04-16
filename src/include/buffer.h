#ifndef __MAIN_H
#define __MAIN_H
#include "stack.h"

typedef struct *arg_buffer_t{
  int in;
  int out;
  int length;
  uint8_t  **buffer;
}arg_buffer_t;

void init_struct();



#endif
