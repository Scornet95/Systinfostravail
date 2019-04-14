#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/producer.h"

typedef struct arg_prod_cons{
  stack_t *stack_file;
  int in=0;
  int out=0;
  int numb_threads;
  uint8_t* buffer[32];
  int consonne;
}

int ajoutByte_Prod(uint8_t *t, uint8_t * tab[], int tailleTab){
  tab[out]=t;
  if(out==0 && in !=0){
    in= in-1;
  }
  out = (out+1) %tailleTab;
  return 9;
}

void producer_routine(void* arg){
  char*fichier=(char*)arg;
  uint8_t *buf = malloc(32);
  FILE* f = fopen(fichier, "rb");
    if (f == NULL){
      exit(EXIT_FAILURE);
    }
    int j=0;
    while(fread(buf, 32, 1, f) > 0 && j!=10){
      j=j+1;
      //sem_wait(&empty);
      //pthread_mutex_lock(&mutex);
      ajoutByte_Prod(buf, buffer, 10);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
  }
}
