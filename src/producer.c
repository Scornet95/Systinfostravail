#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "include/stack.h"
#include "include/buffer.h"
#include "include/prod_cons.h"


void producer_routine(stack_t *stack){
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
      ajoutByte_Buff(buf, tab_circulaire->buffer, tab_circulaire->length, tab_circulaire);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
    }
  }
}
