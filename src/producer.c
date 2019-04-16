#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/stack.h"
#include "include/buffer.h"



void producer_routine(stack_t *stack){
  while (stack->size != 0){
    char *fichier = stack_pop(stack, strlen(stack->head->data));
    uint8_t *buf = malloc(32);
        printf("zeb\n");
    FILE* f = fopen(fichier, "rb");

    if (f == NULL){
      exit(EXIT_FAILURE);
    }
    while(fread(buf, 32, 1, f) > 0){
      //sem_wait(&empty);
      //pthread_mutex_lock(&mutex);
      ajoutByte_Buff(buf, tab_circulaire->buffer, tab_circulaire->length, tab_circulaire);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
    }
  }
}
