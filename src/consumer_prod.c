#include "consumer_prod.h"

//pré: une variable pour la boucle while.
//post: a transformé les hash du premier buffer en string et les a mis dans le deuxième buffer.
void* consumer_routine(void * tru_cons_prod){
  int* tru = tru_cons_prod;

  while(*tru==1){

      sem_wait(&(tab_circulaire->full));

      pthread_mutex_lock(&(tab_circulaire->mutex));

      if(tab_circulaire->i<tab_circulaire->count ){ //tant qu'il y a plus qu'un élement dans le premier buffer..
        char* res = malloc(sizeof(char)*16+1);
        uint8_t* tab32 = malloc(sizeof(uint8_t)*32);
        deleteByte_buff(tab32);

          if(reversehash(tab32, res, 16)){

            sem_wait(&(tab_circulaire1->empty1));

            pthread_mutex_lock(&(tab_circulaire1->mutex1));

            ajoutString_Buff(res);
            tab_circulaire1->count1 = tab_circulaire1->count1+1;//compte le nombre de string ajouté dans le deuxième buffer.
            pthread_mutex_unlock(&(tab_circulaire1->mutex1));

            sem_post(&(tab_circulaire1->full1));
          }

        free(res);
        free(tab32);
        tab_circulaire->i = tab_circulaire->i+1;
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
          char* res1 = malloc(sizeof(char)*16+1);
          uint8_t* tab321 = malloc(sizeof(uint8_t)*32);
          deleteByte_buff(tab321);

            if(reversehash(tab321, res1, 16)){
              sem_wait(&(tab_circulaire1->empty1));

              pthread_mutex_lock(&(tab_circulaire1->mutex1));

              ajoutString_Buff(res1);
              tab_circulaire1->count1 = tab_circulaire1->count1+1;
              tab_circulaire1->boucle_cons1=0;

              pthread_mutex_unlock(&(tab_circulaire1->mutex1));

              sem_post(&(tab_circulaire1->full1));
            }

          free(res1);
          free(tab321);
          *tru = 0; //permet de sortir de la boucle.
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
