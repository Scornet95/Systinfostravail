#ifndef __BUFFER1_H
#define __BUFFER1_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>

#include "stack.h"

typedef struct arg_buffer_string{
  int in1;
  int out1;
  int nbrt1;
  int out_true;
  int boucle_cons1;
  int consonne;
  int length;
  int tru_cons;
  stack_t* stack_fin;
  sem_t empty1;
  sem_t full1;
  pthread_mutex_t mutex1;
  char* file_out;
  char **buf;
}arg_buffer_string_t;

arg_buffer_string_t* tab_circulaire1;

void init_buf_string(int nthread, int consonne, int arg_output, char* output);

void ajoutString_Buff(char * str);

char * deleteString_Buff();

void destroy_cons();


#endif
