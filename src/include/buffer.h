#ifndef __BUFFER_H
#define __BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <pthread.h>
#include <semaphore.h>

#include "stack.h"

typedef struct arg_buffer{
  int in;
  int out;
  int in1;
  int out1;
  int length;
  int nbrt;
  int out_true;
  int boucle_cons;
  int boucle_cons1;
  int consonne;
  char* file_out;
  stack_t* stack_fin;
  sem_t empty;
  sem_t full;
  sem_t empty1;
  sem_t full1;
  pthread_mutex_t mutex;
  pthread_mutex_t mutex1;
  uint8_t  **buffer;
  char **buf;
}arg_buffer_t;

arg_buffer_t* tab_circulaire;

void init_buf(int numb_threads, int consonne, int arg_output, char* output);

void ajoutByte_buff(uint8_t *t);

uint8_t* deleteByte_buff();

void ajoutString_Buff(char * str);

char * deleteString_Buff();

void destroy_buffer_prod_cons();

void destroy_cons();

#endif
