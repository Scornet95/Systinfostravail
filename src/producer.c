#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "stack.h"
#include "include/producer.h"

typedef struct arg_prod_cons_t{
  stack_t *stack_file;
  int in;
  int out;
  int numb_threads;
  uint8_t  **buffer;
  int consonne;
}arg_prod_cons;

int ajoutByte_Prod(uint8_t *t, uint8_t * tab[], int tailleTab, arg_prod_cons arg){
  tab[arg.out]=t;
  if(arg.out==0 && arg.in !=0){
    arg.in= arg.in-1;
  }
  arg.out = (arg.out+1) % arg.numb_threads;
  return 9;
}

void producer_routine(arg_prod_cons arg){
  arg.buffer = malloc(sizeof(uint8_t)*2*arg.numb_threads*32);
  arg.in = 0;
  arg.out = 0;
  while (arg.stack_file->size != 0){
    char *fichier = stack_pop(arg.stack_file, strlen(arg.stack_file->head->data));
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
      ajoutByte_Prod(buf, arg.buffer, 2*arg.numb_threads, arg);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
    }
  }
}
