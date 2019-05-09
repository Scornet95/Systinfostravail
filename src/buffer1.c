#include "buffer1.h"

//pre: le nombre de thread entré par l'utilisateur, variable indiquant si il y a une consonne, si il y a un output et le fichier de sortie.
//post la deuxième structure  initialisé avec comme variable : le in1, le out1, out°_true pour savoir si il y a un output,consonne, une stack, length,
//le nombre de thread nbrt, nbr, i, count, boucle_cons1, les sémaphore empty et full, le mutex et pour finir le premier buffer, count1, i1.
void init_buf_string(int nthread, int consonne, int arg_output, char* output){

//initialisation de la structure.
  tab_circulaire1 = malloc(sizeof(arg_buffer_string_t));
  if (tab_circulaire1 == NULL){
    exit(EXIT_FAILURE);
  }

//les variable initialiser.
  tab_circulaire1->in1=0;
  tab_circulaire1->out1=0;
  tab_circulaire1->nbrt1= nthread;
  tab_circulaire1->out_true=arg_output;
  tab_circulaire1->boucle_cons1=1;
  tab_circulaire1->consonne=consonne;
  tab_circulaire1->length = (2*nthread);
  tab_circulaire1->stack_fin = stack_init();
  tab_circulaire1->count1=0;
  tab_circulaire1->i1=0;
  int err;

  //initialisation des sémaphore et du mutex.
  err = sem_init(&(tab_circulaire1->empty1), 0, (tab_circulaire1->length)/2);
  if(err!=0){
    printf("sem_init empty1");
  }

  err = sem_init(&(tab_circulaire1->full1), 0, 0);
  if(err!=0){
    printf("sem_init full1");
  }

  err = pthread_mutex_init(&(tab_circulaire1->mutex1),NULL);
   if(err!=0){
    printf("pthread_mutex_init un");
   }
 //allouer de la mémoir pour le fichier de sortie
   tab_circulaire1->file_out = malloc(sizeof(char)*strlen(output)+1);
   if(tab_circulaire1->file_out == NULL){
     exit(EXIT_FAILURE);
   }
   memcpy(tab_circulaire1->file_out, output, strlen(output)+1);
//allouer de la mémoir pour le buffer.
   tab_circulaire1->buf = (void *) malloc(sizeof(char *)*(tab_circulaire1->length/2));
   if(tab_circulaire1->buf==NULL){
     exit(EXIT_FAILURE);
   }
   for(int j = 0 ; j<(tab_circulaire1->length/2); j = j+1){
     tab_circulaire1->buf[j]= malloc(sizeof(char)*17);
   }

}
//pré: un string.
//out: un string mis dans le deuxième buffer avec la variable out1 incrémenté et avec un modulo la taille du buffer.
void ajoutString_Buff(char * str){
  memcpy(tab_circulaire1->buf[tab_circulaire1->out1], str, 17);
  tab_circulaire1->out1 = ((tab_circulaire1->out1)+1)%(tab_circulaire1->length/2);
}

//pré: un string.
//out: un string mis dans le deuxième buffer avec la variable in1 incrémenté et avec un modulo la taille du buffer.
void deleteString_Buff(char * temp){
  memcpy(temp,tab_circulaire1->buf[tab_circulaire1->in1], 17);
  tab_circulaire1->in1 = ((tab_circulaire1->in1)+1) % (tab_circulaire1->length/2);
}

//pré: rien.
//post: on free le deuxième buffer et la stack comprenant les string.
void destroy_cons(){
  for(int i=0; i<(tab_circulaire1->length)/2; i++){
    free(tab_circulaire1->buf[i]);
  }
  free(tab_circulaire1->buf);
  stack_destroy(tab_circulaire1->stack_fin);
}
