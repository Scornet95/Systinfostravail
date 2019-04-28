#include "consumer_prod.h"

void* consumer_routine(){
 // il manque un while.
  //printf("1c\n");

  while((tab_circulaire->boucle_cons)==1 || tab_circulaire->in!=tab_circulaire->out){
    int nbr=0;
    //printf("sem_wait_cons_prod full avant\n");
    if(tab_circulaire->boucle_cons==0){
      if(nbr!=tab_circulaire->nbrt-1){
        tab_circulaire->boucle_cons1=tab_circulaire->boucle_cons1+1;
        nbr=nbr+1;
        return NULL;
      }      
    }

    sem_wait(&(tab_circulaire->full));

    //printf("SE_WAIT_CONS_PROD FULL APRES\n");

    //printf("mutex lock prod_cons avant\n");

    pthread_mutex_lock(&(tab_circulaire->mutex));

    //que faire pour sortir les dernier thread.

    //printf("MUTEX LOCK PROD_CONS APRES\n");

    char* res = malloc(sizeof(char)*16+1);
    uint8_t* tab32 = deleteByte_buff();

    if (reversehash(tab32, res, 16)){
      //printf("sem_wait_prod_cons empty1 avant\n");
      sem_wait(&(tab_circulaire->empty1));
      //printf("sem_wait_prod_cons empty1 après\n");
      //printf("mutex1 lock prod_cons avant\n");
      pthread_mutex_lock(&(tab_circulaire->mutex1));
      //printf("mutex1 lock prod_cons après\n");
      ajoutString_Buff(res);
      //printf("mutex1 unlock prod_cons avant\n");
      pthread_mutex_unlock(&(tab_circulaire->mutex1));
      //printf("mutex1 unlock prod_cons après\n");
      //printf("sem_post_prod_cons full1 avant\n");
      sem_post(&(tab_circulaire->full1));
      //printf("sem_post_prod_cons full1 après\n");
    }
  //  printf("4c\n");
    res = NULL;
    free(res);
    pthread_mutex_unlock(&(tab_circulaire->mutex));
    sem_post(&(tab_circulaire->empty));
 }

  tab_circulaire->boucle_cons1=tab_circulaire->boucle_cons1+1;
  printf("%d",tab_circulaire->boucle_cons1);
  destroy_buffer_prod_cons();
  printf("5c\n");
  return NULL;
}
