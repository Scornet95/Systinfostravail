#include "include/buffer.h"


void init_buf(int numb_threads, int consonne){
  tab_circulaire = malloc(sizeof(arg_buffer_t));
  if (tab_circulaire == NULL){
    exit(EXIT_FAILURE);
  }
  tab_circulaire->length = (2*numb_threads);
  tab_circulaire->nbrt = numb_threads;
  tab_circulaire->in = 0;
  tab_circulaire->out = 0;
  tab_circulaire->boucle_cons=1;
  tab_circulaire->boucle_cons1=0;
  tab_circulaire->consonne = consonne;
  tab_circulaire->stack_fin = stack_init();

  int err;

  err = pthread_mutex_init(&(tab_circulaire->mutex),NULL);
   if(err!=0){
    printf("pthread_mutex_init");
   }
   err = pthread_mutex_init(&(tab_circulaire->mutex1),NULL);
    if(err!=0){
     printf("pthread_mutex_init un");
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

   err = sem_init(&(tab_circulaire->empty1), 0, (tab_circulaire->length)/2);
   if(err!=0){
     printf("sem_init empty1");
   }

   err = sem_init(&(tab_circulaire->full1), 0, 0);
   if(err!=0){
     printf("sem_init full1");
   }


  tab_circulaire->buffer = malloc(sizeof(uint8_t *)*tab_circulaire->length);
  if (tab_circulaire->buffer == NULL){
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < tab_circulaire->length; i++){
    tab_circulaire->buffer[i] = malloc(sizeof(uint8_t)*32);
  }

  tab_circulaire->buf = (void *) malloc(sizeof(char *)*(tab_circulaire->length/2));
  if(tab_circulaire->buf==NULL){
    exit(EXIT_FAILURE);
  }
  for(int j = 0 ; j<(tab_circulaire->length/2); j = j+1){
    tab_circulaire->buf[j]= malloc(sizeof(char)*16);
  }

}

void ajoutByte_buff(uint8_t *t){
  tab_circulaire->buffer[tab_circulaire->out]=t;
  tab_circulaire->out = ((tab_circulaire->out)+1) % tab_circulaire->length;
}

uint8_t* deleteByte_buff(){
  uint8_t* temp = malloc(sizeof(uint8_t)*32);
  temp = tab_circulaire->buffer[tab_circulaire->in];
  tab_circulaire->in = ((tab_circulaire->in)+1) % tab_circulaire->length;
  return temp;
}

void ajoutString_Buff(char * str){
  tab_circulaire->buf[tab_circulaire->out1]=  str;
  tab_circulaire->out1 = ((tab_circulaire->out1)+1)%(tab_circulaire->length/2);
}

char * deleteString_Buff(){
  char* temp = malloc(sizeof(char)*16);
  temp =  tab_circulaire->buf[tab_circulaire->in1];
  tab_circulaire->in1 = ((tab_circulaire->in1)+1) % (tab_circulaire->length/2);
  return temp;
}
void destroy_buffer_prod_cons(){
  for(int i=0;i<tab_circulaire->length;i++){
    free(tab_circulaire->buffer[i]);
  }
  free(tab_circulaire->buffer);
}

void destroy_cons(){
  for(int i=0; i<(tab_circulaire->length)/2; i++){
    free(tab_circulaire->buf[i]);
  }
  free(tab_circulaire->buf);
  stack_destroy(tab_circulaire->stack_fin);
}
