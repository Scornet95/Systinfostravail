#include "consumer_prod.h"


void* consumer_routine(void * tru_cons_prod){
  int* tru = tru_cons_prod;

  while(*tru==1){
    //printf("premier wait\n")

      sem_wait(&(tab_circulaire->full));

      pthread_mutex_lock(&(tab_circulaire->mutex));

      //printf("le count est %d\n", tab_circulaire->count);
      //printf("le i est %d\n", tab_circulaire->i);
      if(tab_circulaire->i<tab_circulaire->count ){
        char* res = malloc(sizeof(char)*16+1);
        uint8_t* tab32 = malloc(sizeof(uint8_t)*32);
        deleteByte_buff(tab32);
        //if(tab32[0]!=NULL){
        //  printf("bloqué\n");

          if(reversehash(tab32, res, 16)){

            sem_wait(&(tab_circulaire1->empty1));

            pthread_mutex_lock(&(tab_circulaire1->mutex1));

            ajoutString_Buff(res);
            tab_circulaire1->count1 = tab_circulaire1->count1+1;
            pthread_mutex_unlock(&(tab_circulaire1->mutex1));

            sem_post(&(tab_circulaire1->full1));
          }

        //printf("6\n");
        free(res);
        free(tab32);
        tab_circulaire->i = tab_circulaire->i+1;
        if(tab_circulaire->boucle_cons==0 ){
          pthread_mutex_unlock(&(tab_circulaire->mutex));
          sem_post(&(tab_circulaire->full));
        }
        else{
          pthread_mutex_unlock(&(tab_circulaire->mutex));
          sem_post(&(tab_circulaire->empty));
        }
      }
      else{
        if(tab_circulaire->nbr<tab_circulaire->nbrt-1){
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
          char* res1 = malloc(sizeof(char)*16+1);
          uint8_t* tab321 = malloc(sizeof(uint8_t)*32);
          deleteByte_buff(tab321);
          //if(tab32[0]!=NULL){
          //  printf("bloqué\n");

            if(reversehash(tab321, res1, 16)){
              sem_wait(&(tab_circulaire1->empty1));

              pthread_mutex_lock(&(tab_circulaire1->mutex1));

              ajoutString_Buff(res1);
              tab_circulaire1->count1 = tab_circulaire1->count1+1;
              tab_circulaire1->boucle_cons1=0;

              pthread_mutex_unlock(&(tab_circulaire1->mutex1));

              sem_post(&(tab_circulaire1->full1));
            }

          //printf("6\n");
          free(res1);
          free(tab321);
          *tru = 0;
          if(tab_circulaire->boucle_cons==0 ){
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->full));
          }
          else{
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->empty));
          }
        }
      }

  }
  sem_post(&(tab_circulaire1->full1));
  return NULL;
}
