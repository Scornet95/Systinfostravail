#ifndef __BUFFER_H
#define __BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "stack.h"
#include <pthread.h>
#include <semaphore.h>

typedef struct arg_buffer{
  int in;
  int out;
  int length;
  sem_t empty;
  sem_t full;
  pthread_mutex_t mutex;
  uint8_t  **buffer;
}arg_buffer_t;

arg_buffer_t* tab_circulaire;

void init_buf(int numb_threads);

void ajoutByte_Buff(uint8_t *t, uint8_t * tab[], int tailleTab, arg_buffer_t* arg);



#endif
