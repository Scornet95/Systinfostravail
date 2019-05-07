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
  int length;
  int nbrt;
  int nbr;
  int count;
  int i;
  int boucle_cons;
  sem_t empty;
  sem_t full;
  pthread_mutex_t mutex;
  uint8_t  **buffer;
}arg_buffer_t;

arg_buffer_t* tab_circulaire;

void init_buf(int numb_threads);

void ajoutByte_buff(uint8_t *t);

void deleteByte_buff(uint8_t* temp);

void destroy_buffer_prod_cons();


#endif
