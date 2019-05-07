#include "consumer_prod.h"
#include <inttypes.h>


void* consumer_routine(void * tru_cons_prod){
  int* tru = tru_cons_prod;

  while(*tru==1){
    //printf("premier wait\n");
      sem_wait(&(tab_circulaire->full));

      pthread_mutex_lock(&(tab_circulaire->mutex));
      //printf("le count est %d\n", tab_circulaire->count);
      //printf("le i est %d\n", tab_circulaire->i);
      if(tab_circulaire->i<tab_circulaire->count ){
        char* res = malloc(sizeof(char)*16+1);
        uint8_t* tab32 = deleteByte_buff();
        //if(tab32[0]!=NULL){
        //  printf("bloqué\n");

          if(reversehash(tab32, res, 16)){
            printf("%s\n",res);
          }

        //printf("6\n");
        free(res);
        tab_circulaire->i = tab_circulaire->i+1;
      }
      else{
        if(tab_circulaire->nbr!=tab_circulaire->nbrt-1){
         //printf("nbrt est %d\n", tab_circulaire->nbr);
          if(tab_circulaire->boucle_cons==0){
            tab_circulaire->nbr=tab_circulaire->nbr+1;
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->full));
          }
          else{
            tab_circulaire->nbr=tab_circulaire->nbr+1;
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->empty));
          }

          return NULL;
        }
        else{
          //printf("FINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n");
          *tru = 0;
        }
      }
      if(tab_circulaire->boucle_cons==0 ){
        pthread_mutex_unlock(&(tab_circulaire->mutex));
        sem_post(&(tab_circulaire->full));
      }
      else{
        pthread_mutex_unlock(&(tab_circulaire->mutex));
        sem_post(&(tab_circulaire->empty));
      }

  }
  printf("FIN2\n");
  return NULL;
}
