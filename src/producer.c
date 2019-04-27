#include "producer.h"


void* producer_routine(void* stack){
  stack_t* new_stack = (stack_t*) stack;
  while (new_stack->size != 0){;
    char *fichier = stack_pop(new_stack, strlen(new_stack->head->data));
    //printf("%s\n",fichier);


    //printf("7\n");

    FILE* f = fopen(fichier, "rb");

    //printf("8\n");

    if (f == NULL){

      //printf("9\n");

      exit(EXIT_FAILURE);
    }

    //printf("10\n");
    int tru = 1;
    while(tru==1){
      uint8_t *buf = malloc(32);
      if(fread(buf, 32, 1, f)>0){

        //printf("11\n");

        sem_wait(&(tab_circulaire->empty));

        pthread_mutex_lock(&(tab_circulaire->mutex));

        //printf("12\n");

        ajoutByte_buff(buf);

        //printf("13\n");

        //printf("le in est %d\n",tab_circulaire->in);
        //printf("le out est %d\n",tab_circulaire->out);

        pthread_mutex_unlock(&(tab_circulaire->mutex));

        sem_post(&(tab_circulaire->full));

        //printf("14\n");
        buf = NULL;
        free(buf);
      }
      else{
        tru=0;
        tab_circulaire->boucle_cons=0;
        //printf("%d", tab_circulaire->boucle_cons);
      }
    }
  }
  return 0;
}
