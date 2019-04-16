#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "include/stack.h"

#include "include/prod_cons.h"

int ajoutByte_Prod(uint8_t *t, uint8_t * tab[], int tailleTab, arg_buffer_t* buffer){
  tab[arg.out]=t;
  if(arg.out==0 && arg.in !=0){
    arg.in= arg.in-1;
  }
  arg.out = (arg.out+1) % arg.numb_threads;
  return 9;
}

void producer_routine(stack_t stack){
  while (stack->size != 0){
    char *fichier = stack_pop(stack, strlen(stack->head->data));
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
      ajoutByte_Prod(buf, tab_circulaire->buffer, tab_circulaire->length, tab_circulaire);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
    }
  }
}
