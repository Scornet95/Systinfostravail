#include "buffer1.h"

void init_buf_string(int nthread, int consonne, int arg_output, char* output){

  tab_circulaire1 = malloc(sizeof(arg_buffer_string_t));
  if (tab_circulaire1 == NULL){
    exit(EXIT_FAILURE);
  }

  tab_circulaire1->in1=0;
  tab_circulaire1->out1=0;
  tab_circulaire1->nbrt1= nthread;
  tab_circulaire1->out_true=arg_output;
  tab_circulaire1->boucle_cons1=0;
  tab_circulaire1->consonne=consonne;
  tab_circulaire1->length = (2*nthread);
  tab_circulaire1->stack_fin = stack_init();
  tab_circulaire1->tru_cons=1;

  int err;
  err = sem_init(&(tab_circulaire1->empty1), 0, (tab_circulaire1->length)/2);
  if(err!=0){
    printf("sem_init empty1");
  }

 printf("init\n");

  err = sem_init(&(tab_circulaire1->full1), 0, 0);
  if(err!=0){
    printf("sem_init full1");
  }

  err = pthread_mutex_init(&(tab_circulaire1->mutex1),NULL);
   if(err!=0){
    printf("pthread_mutex_init un");
   }

   tab_circulaire1->file_out = malloc(sizeof(char)*strlen(output)+1);
   if(tab_circulaire1->file_out == NULL){
     exit(EXIT_FAILURE);
   }
   memcpy(tab_circulaire1->file_out, output, strlen(output)+1);

   tab_circulaire1->buf = (void *) malloc(sizeof(char *)*(tab_circulaire1->length/2));
   if(tab_circulaire1->buf==NULL){
     exit(EXIT_FAILURE);
   }
   for(int j = 0 ; j<(tab_circulaire1->length/2); j = j+1){
     tab_circulaire1->buf[j]= malloc(sizeof(char)*17);
   }

}

void ajoutString_Buff(char * str){
  memcpy(tab_circulaire1->buf[tab_circulaire1->out1], str, 17);
  tab_circulaire1->out1 = ((tab_circulaire1->out1)+1)%(tab_circulaire1->length/2);
}

char * deleteString_Buff(){
  char* temp = malloc(sizeof(char)*17);
  memcpy(temp,tab_circulaire1->buf[tab_circulaire1->in1], 17);
  tab_circulaire1->in1 = ((tab_circulaire1->in1)+1) % (tab_circulaire1->length/2);
  return temp;
}
void destroy_cons(){
  for(int i=0; i<(tab_circulaire1->length)/2; i++){
    free(tab_circulaire1->buf[i]);
  }
  free(tab_circulaire1->buf);
  stack_destroy(tab_circulaire1->stack_fin);
}
