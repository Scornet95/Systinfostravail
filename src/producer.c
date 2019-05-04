#include "producer.h"


void* producer_routine(void* stack){
  stack_t* new_stack = (stack_t*) stack;
  while (new_stack->size != 0){;
    char *fichier = stack_pop(new_stack, strlen(new_stack->head->data));

    FILE* f = fopen(fichier, "rb");

    if (f == NULL){

      exit(EXIT_FAILURE);
    }

    int tru = 1;
    while(tru==1){
      uint8_t *buf = malloc(32);
      if(fread(buf, 32, 1, f)>0){

        sem_wait(&(tab_circulaire->empty));
        pthread_mutex_lock(&(tab_circulaire->mutex));

        ajoutByte_buff(buf);

        pthread_mutex_unlock(&(tab_circulaire->mutex));
        sem_post(&(tab_circulaire->full));

        buf = NULL;
        free(buf);
      }
      else{
        tru=0;
        tab_circulaire->boucle_cons=0;
      }
      free(buf);
    }
  }
  stack_destroy(stack);
  return NULL;
}
