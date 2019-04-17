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

void ajoutByte_Buff(uint8_t *t){
  tab_circulaire->buffer[tab_circulaire->out]=t;
  tab_circulaire->out = ((tab_circulaire->out)+1) % tab_circulaire->length;
}

uint8_t* delete_buff(){
  uint8_t* temp = malloc(sizeof(uint8_t)*32);
  temp = tab_circulaire->buffer[tab_circulaire->in];
  tab_circulaire->in = (tab_circulaire->in+1) % tab_circulaire->length;
  return temp;
}
