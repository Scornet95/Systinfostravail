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
  int boucle_cons;
  sem_t empty;
  sem_t full;
  pthread_mutex_t mutex;
  pthread_mutex_t mutex1;
  uint8_t  **buffer;
  char **buf;
}arg_buffer_t;

arg_buffer_t* tab_circulaire;

void init_buf(int numb_threads);

void ajoutByte_buff(uint8_t *t);

uint8_t* deleteByte_buff();

void ajoutString_Buff(char * str);

char * deleteString_Buff();

#endif
