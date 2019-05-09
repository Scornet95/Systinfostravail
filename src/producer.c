#include "producer.h"

//pré: un stack avec les fichier en entrée.
//post: les éléments des fichier sont mis dans le premier buffer.
void* producer_routine(void* stack){
  stack_t* new_stack = (stack_t*) stack;
 FILE* f;

  while (new_stack->size != 0){
    char *fichier = stack_pop(new_stack, strlen(new_stack->head->data)); // prend le premier fichier à lire.
    f = fopen(fichier, "rb");


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
        tab_circulaire->count=tab_circulaire->count+1; //compte le nombre de hash ajouter dans le buffer pour le communiquer au consumer_prod.
        free(buf);

      }
      else{
        tru=0; //fin de la boucle while.
        tab_circulaire->boucle_cons=0; //dire au consumer_prod que le producteur a fini.
        free(buf);
      }
      pthread_mutex_unlock(&(tab_circulaire->mutex));
      sem_post(&(tab_circulaire->full));
    }
    free(fichier);
    //free(f);
  }
  fclose(f);
  stack_destroy(new_stack);
  return NULL;
}
