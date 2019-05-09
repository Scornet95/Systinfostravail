#include "buffer.h"

//pre: le nombre de thread entré par l'utilisateur.
//post la première structure  initialisé avec comme variable: le in, le out, la longueur du buffer,
//le nombre de thread, nbr, i, count, boucle_cons, les sémaphore empty et full, le mutex et pour finir le premier buffer.
void init_buf(int numb_threads){

  //allouer la structure.
  tab_circulaire = malloc(sizeof(arg_buffer_t));
  if (tab_circulaire == NULL){
    exit(EXIT_FAILURE);
  }
  //initialiser les variables.
  tab_circulaire->length = (2*numb_threads);
  tab_circulaire->nbrt = numb_threads;
  tab_circulaire->in = 0;
  tab_circulaire->out = 0;
  tab_circulaire->count=0;
  tab_circulaire->i=0;
  tab_circulaire->boucle_cons=1;


  int err;
  //initialisation des mutex et sémaphore.
  err = pthread_mutex_init(&(tab_circulaire->mutex),NULL);
   if(err!=0){
    printf("pthread_mutex_init");
   }

   err = sem_init(&(tab_circulaire->empty), 0, (tab_circulaire->length));
   if(err!=0){
     printf("sem_init empty");
   }

   err = sem_init(&(tab_circulaire->full), 0, 0);
   if(err!=0){
     printf("sem_init full");
   }

//allouer le premier buffer.
  tab_circulaire->buffer = malloc(sizeof(uint8_t *)*tab_circulaire->length);
  if (tab_circulaire->buffer == NULL){
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < tab_circulaire->length; i++){
    tab_circulaire->buffer[i] = malloc(sizeof(uint8_t)*32);
  }

}

//pré: un hash de 32 bytes.
//out: un hash de 32 bytes mis dans le premier buffer avec la variable out incrémenté et avec un modulo la taille du buffer.
void ajoutByte_buff(uint8_t *t){
  memcpy(tab_circulaire->buffer[tab_circulaire->out], t, 32);
  tab_circulaire->out = ((tab_circulaire->out)+1) % tab_circulaire->length;
}

//pré: un hash de 32 bytes.
//out: un hash de 32 bytes mis dans le premier  buffer avec la variable in incrémenté et avec un modulo la taille du buffer.
void deleteByte_buff(uint8_t* temp){
  memcpy(temp,tab_circulaire->buffer[tab_circulaire->in], 32);
  tab_circulaire->in = ((tab_circulaire->in)+1) % tab_circulaire->length;
}

//pré: aucune entrée.
//post: on free le premier buffer.
void destroy_buffer_prod_cons(){
  for(int i=0;i<tab_circulaire->length;i++){
    free(tab_circulaire->buffer[i]);
  }
  free(tab_circulaire->buffer);
}
