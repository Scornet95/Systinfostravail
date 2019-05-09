#include "consumer_prod.h"

//pré: une variable pour la boucle while.
//post: a transformé les hash du premier buffer en string et les a mis dans le deuxième buffer.
void* consumer_routine(void * tru_cons_prod){
  int* tru = tru_cons_prod;

  while(*tru==1){
      sem_wait(&(tab_circulaire->full));
      pthread_mutex_lock(&(tab_circulaire->mutex));

      if(tab_circulaire->i<tab_circulaire->count){
        printf("%d, %d coke est un con \n",tab_circulaire->i,tab_circulaire->count); //tant qu'il y a plus qu'un élement dans le premier buffer..
        char* res = malloc(sizeof(char)*16+1);
        uint8_t* tab32 = malloc(sizeof(uint8_t)*32);//compte le nombre de string ajouté dans le deuxième buffer.
        tab_circulaire->i = tab_circulaire->i+1;
        tab_circulaire1->count1 = tab_circulaire1->count1+1;
        deleteByte_buff(tab32);
        //printf("unlock\n");
      pthread_mutex_unlock(&(tab_circulaire->mutex));
        //printf("rever\n");
      if(reversehash(tab32, res, 16)){

        sem_wait(&(tab_circulaire1->empty1));
            //printf("empty\n");
        pthread_mutex_lock(&(tab_circulaire1->mutex1));
            //printf("222\n");
        ajoutString_Buff(res);
        pthread_mutex_lock(&(tab_circulaire->mutex));
        pthread_mutex_unlock(&(tab_circulaire1->mutex1));

        sem_post(&(tab_circulaire1->full1));
        free(res);
        free(tab32);
          }

        if(tab_circulaire->boucle_cons==0 ){ // si le producteur a fini de mettre tous les hash dans le premier buffer.
          pthread_mutex_unlock(&(tab_circulaire->mutex));
          sem_post(&(tab_circulaire->full));
        }
        else{  // si le producteur n'a pas fini de mettre tous les hash dans le premier buffer.
          pthread_mutex_unlock(&(tab_circulaire->mutex));
          sem_post(&(tab_circulaire->empty));
        }
      }
      else{//si il reste que un seul hash/un seul slot dans le premier buffer.
        if(tab_circulaire->nbr<tab_circulaire->nbrt-1){ //si il reste moin qu'un thread.
          if(tab_circulaire->boucle_cons==0){ // si le producteur a fini de mettre tous les hash dans le premier buffer.
            tab_circulaire->nbr=tab_circulaire->nbr+1;
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->full));
          }
          else{ // si le producteur n'a pas fini de mettre tous les hash dans le premier buffer.
            tab_circulaire->nbr=tab_circulaire->nbr+1;
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->empty));
          }
          return NULL;
        }
        else{// si il reste qu'un thread.
          *tru = 0; //permet de sortir de la boucle.
          tab_circulaire1->boucle_cons1=0;
          if(tab_circulaire->boucle_cons==0 ){// si le producteur a fini de mettre tous les hash dans le premier buffer.
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->full));
          }
          else{ // si le producteur n'a pas fini de mettre tous les hash dans le premier buffer.
            pthread_mutex_unlock(&(tab_circulaire->mutex));
            sem_post(&(tab_circulaire->empty));
          }
        }
      }

  }
  sem_post(&(tab_circulaire1->full1));
  return NULL;
}
