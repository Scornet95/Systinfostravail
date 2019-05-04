#include "consumer.h"


void* tri_String(){

  while(tab_circulaire->in1 != tab_circulaire->out1 || tab_circulaire->boucle_cons1!=tab_circulaire->nbrt){


    sem_wait(&(tab_circulaire->full1));

    pthread_mutex_lock(&(tab_circulaire->mutex1));



    char * str = deleteString_Buff();
    //printf("%s\n",str);
    if(stack_get_size(tab_circulaire->stack_fin)==0){
      stack_push(tab_circulaire->stack_fin, str, strlen(str));
    }
    else{

      if(count(str, tab_circulaire->consonne)== count(tab_circulaire->stack_fin->head->data, tab_circulaire->consonne)){
        // pop
        stack_push(tab_circulaire->stack_fin,str,strlen(str));
      }

      else if(count(str, tab_circulaire->consonne)>count(tab_circulaire->stack_fin->head->data, tab_circulaire->consonne)){
        while (tab_circulaire->stack_fin->size != 0){
          stack_pop(tab_circulaire->stack_fin, strlen(tab_circulaire->stack_fin->head->data));
        }
        stack_push(tab_circulaire->stack_fin,str,strlen(str));
      }

      else{

      }

    }

    pthread_mutex_unlock(&(tab_circulaire->mutex1));

    sem_post(&(tab_circulaire->empty1));

 }
 printf("3cons\n");
  return NULL;
}

// un méthhode print.

void print_stack(stack_t* s){
  if(tab_circulaire->out_true==1){
     int file = open(tab_circulaire->file_out, O_WRONLY | O_CREAT);
    while(stack_get_size(s)!=0){
      write(file,(char *)stack_pop(s, strlen(tab_circulaire->stack_fin->head->data)+1),sizeof(char)*strlen(tab_circulaire->stack_fin->head->data)+1);
    }
    close(file);
  }
  else{
    while(stack_get_size(s)!=0){
      printf("%s\n",(char *)stack_pop(s, strlen(tab_circulaire->stack_fin->head->data)+1));
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
