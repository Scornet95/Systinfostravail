#include "consumer.h"


void* tri_String(void * tru1){
  int *tru_cons= tru1;

  while(*tru_cons==1){

    sem_wait(&(tab_circulaire1->full1));

    pthread_mutex_lock(&(tab_circulaire1->mutex1));

    printf("2c\n");

    if(tab_circulaire1->in1 != tab_circulaire1->out1 || tab_circulaire1->boucle_cons1!=tab_circulaire1->nbrt1){
      char * str = deleteString_Buff();
      //printf("%s\n",str);
      if(stack_get_size(tab_circulaire1->stack_fin)==0){
        stack_push(tab_circulaire1->stack_fin, str, strlen(str));
      }
      else{

        if(count(str, tab_circulaire1->consonne)== count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          // pop
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
        }

        else if(count(str, tab_circulaire1->consonne)>count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          while (tab_circulaire1->stack_fin->size != 0){
            stack_pop(tab_circulaire1->stack_fin, strlen(tab_circulaire1->stack_fin->head->data));
          }
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
        }
        else{

        }

      }
    }
    else{
      *tru_cons = 0;
    }
    printf("3c\n");

    pthread_mutex_unlock(&(tab_circulaire1->mutex1));

    sem_post(&(tab_circulaire1->empty1));
    printf("4c\n");
  }
  printf("5c\n");
  return NULL;
}

// un méthhode print.

void print_stack(stack_t* s){
  if(tab_circulaire1->out_true==1){
     int file = open(tab_circulaire1->file_out, O_WRONLY | O_CREAT);
    while(stack_get_size(s)!=0){
      write(file,(char *)stack_pop(s, strlen(tab_circulaire1->stack_fin->head->data)+1),sizeof(char)*strlen(tab_circulaire1->stack_fin->head->data)+1);
    }
    close(file);
  }
  else{
    while(stack_get_size(s)!=0){
      printf("%s\n",(char *)stack_pop(s, strlen(tab_circulaire1->stack_fin->head->data)+1));
    }
  }
    destroy_cons();
}

int count(char* str, int consonne){
  int nbr=0;

      if(consonne==0){
        for(int i=0;i<strlen(str);i++){
          if(str[i]=='a' || str[i]=='e' ||str[i]=='i' ||str[i]=='o' ||str[i]=='u' ||str[i]=='y' ||str[i]=='A' ||str[i]=='E' ||str[i]=='I' ||str[i]=='O' ||str[i]=='U' ||str[i]=='Y'){
            nbr = nbr + 1;
          }
        }
      }
      else{
        for(int j = 0;j<strlen(str);j=j+1){
          if(str[j]=='a' || str[j]=='e' ||str[j]=='i' ||str[j]=='o' ||str[j]=='u' ||str[j]=='y' ||str[j]=='A' ||str[j]=='E' ||str[j]=='I' ||str[j]=='O' ||str[j]=='U' ||str[j]=='Y'){

          }
          else{
            nbr = nbr + 1;
          }
        }
      }
   return nbr;
}
