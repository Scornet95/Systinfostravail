#include "include/buffer.h"
#include <semaphore.h>
#include <pthread.h>

void init_buf(int numb_threads){
  tab_circulaire = malloc(sizeof(arg_buffer_t));
  if (tab_circulaire == NULL){
    exit(EXIT_FAILURE);
  }
  tab_circulaire->length = (2*numb_threads);
  sem_init(&(tab_circulaire->empty), 0, tab_circulaire->length);
  sem_init(&(tab_circulaire->full), 0, 0);
  pthread_mutex_init(&(tab_circulaire->mutex), NULL);
  tab_circulaire->in = 0;
  tab_circulaire->out = 0;
  tab_circulaire->buffer = malloc(sizeof(uint8_t *)*tab_circulaire->length);
  if (tab_circulaire->buffer == NULL){
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < tab_circulaire->length; i++){
    tab_circulaire->buffer[i] = malloc(sizeof(uint8_t)*32);
  }
}

void ajoutByte_Buff(uint8_t *t, uint8_t * tab[], int tailleTab, arg_buffer_t* arg){
  tab[arg->out]=t;
  if(arg->out==0 && arg->in !=0){
    arg->in= arg->in-1;
  }
  arg->out = (arg->out+1) % arg->length;
}
