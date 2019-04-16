#ifndef __MAIN_H
#define __MAIN_H
#include "stack.h"

typedef struct arg_buffer_t{
  int in;
  int out;
  int length;
  uint8_t  **buffer;
}arg_buffer_t;

struct arg_buffer_t tab_circulaire;
void init_struct();

void ajoutByte_Buff(uint8_t *t, uint8_t * tab[], int tailleTab, arg_buffer_t* arg);



#endif
