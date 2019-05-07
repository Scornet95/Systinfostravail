#include "consumer_prod.h"

void* consumer_routine(void * tru_cons_prod){
  int* tru = tru_cons_prod;
 // il manque un while.
  //printf("1c\n");
  printf("c'est tru : %d\n",*tru);
  while(*tru==1){

      sem_wait(&(tab_circulaire->full));

      pthread_mutex_lock(&(tab_circulaire->mutex));

      char* res = malloc(sizeof(char)*16+1);
      uint8_t* tab32 = deleteByte_buff();


      if(reversehash(tab32, res, 16)){
        printf("%s\n",res);
      }

      free(res);

      pthread_mutex_unlock(&(tab_circulaire->mutex));
      sem_post(&(tab_circulaire->empty));
  }

  return NULL;
}
