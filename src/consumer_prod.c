#include "consumer_prod.h"

void* consumer_routine(){
 // il manque un while.
  //printf("1c\n");

  while((tab_circulaire->boucle_cons)==1 || tab_circulaire->in!=tab_circulaire->out){

    sem_wait(&(tab_circulaire->full));
    pthread_mutex_lock(&(tab_circulaire->mutex));

    //printf("2c\n");

    char* res = malloc(sizeof(char)*16+1);
    uint8_t* tab32 = deleteByte_buff();

    //printf("3c\n");

    if (reversehash(tab32, res, 16)){
      ajoutString_Buff(res);
    }

    //printf("4c\n");
    res = NULL;
    free(res);

    pthread_mutex_unlock(&(tab_circulaire->mutex));
    sem_post(&(tab_circulaire->empty));

 }


  //printf("5c\n");

  return 0;
}
