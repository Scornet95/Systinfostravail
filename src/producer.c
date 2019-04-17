#include "producer.h"
#include <semaphore.h>
#include <pthread.h>


void* producer_routine(void* stack){
  stack_t* new_stack = (stack_t*) stack;
  while (new_stack->size != 0){
    printf("hello, %p", new_stack->head->data);
    char *fichier = stack_pop(new_stack, strlen(new_stack->head->data));
    uint8_t *buf = malloc(32);
    FILE* f = fopen(fichier, "rb");
    if (f == NULL){
      exit(EXIT_FAILURE);
    }
    while(fread(buf, 32, 1, f) > 0){
      //sem_wait(&empty);
      sem_wait(&(tab_circulaire->empty));
      //pthread_mutex_lock(&mutex);
      pthread_mutex_lock(&(tab_circulaire->mutex));
      printf("%d", tab_circulaire->out);
      ajoutByte_Buff(buf);
      //pthread_mutex_unlock(&mutex);
      pthread_mutex_unlock(&(tab_circulaire->mutex));
      //sem_post(&full);
      sem_post(&(tab_circulaire->full));
    }
  }
  return 0;
}
