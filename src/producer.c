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
      //printf("wait\n");
      sem_wait(&(tab_circulaire->empty));
      pthread_mutex_lock(&(tab_circulaire->mutex));
      uint8_t *buf = (uint8_t *) malloc(sizeof(uint8_t)*32);
      if(fread(buf, 1, 32, f)!=0){
        ajoutByte_buff(buf);
        tab_circulaire->count=tab_circulaire->count+1;
        free(buf);

      }
      else{
        tru=0;
        tab_circulaire->boucle_cons=0;
      }
      pthread_mutex_unlock(&(tab_circulaire->mutex));
      sem_post(&(tab_circulaire->full));
    }
    free(fichier);
  }

  free(new_stack);
  return NULL;
}
