#include "buffer.h"
#include <inttypes.h>


void init_buf(int numb_threads){
  tab_circulaire = malloc(sizeof(arg_buffer_t));
  if (tab_circulaire == NULL){
    exit(EXIT_FAILURE);
  }
  tab_circulaire->length = (2*numb_threads);
  tab_circulaire->nbrt = numb_threads;
  tab_circulaire->in = 0;
  tab_circulaire->out = 0;
  tab_circulaire->count=0;
  tab_circulaire->i=0;
  tab_circulaire->boucle_cons=1;


  int err;

  err = pthread_mutex_init(&(tab_circulaire->mutex),NULL);
   if(err!=0){
    printf("pthread_mutex_init");
   }
   //printf("2\n");

   err = sem_init(&(tab_circulaire->empty), 0, (tab_circulaire->length));
   if(err!=0){
     printf("sem_init empty");
   }

   err = sem_init(&(tab_circulaire->full), 0, 0);
   if(err!=0){
     printf("sem_init full");
   }


  tab_circulaire->buffer = malloc(sizeof(uint8_t *)*tab_circulaire->length);
  if (tab_circulaire->buffer == NULL){
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < tab_circulaire->length; i++){
    tab_circulaire->buffer[i] = malloc(sizeof(uint8_t)*32);
  }

}

void ajoutByte_buff(uint8_t *t){
  //printf("%" PRIu8 " le uint8_t\n", t[0]);
  memcpy(tab_circulaire->buffer[tab_circulaire->out], t, 32);
  tab_circulaire->out = ((tab_circulaire->out)+1) % tab_circulaire->length;
}

uint8_t* deleteByte_buff(){
  uint8_t* temp = malloc(sizeof(uint8_t)*32);
  memcpy(temp,tab_circulaire->buffer[tab_circulaire->in], 32);
  tab_circulaire->in = ((tab_circulaire->in)+1) % tab_circulaire->length;

  return temp;
}


void destroy_buffer_prod_cons(){
  for(int i=0;i<tab_circulaire->length;i++){
    free(tab_circulaire->buffer[i]);
  }
  free(tab_circulaire->buffer);
}
