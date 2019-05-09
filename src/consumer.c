#include "consumer.h"


void* tri_String(void * tru1){
  int *tru_cons= tru1;
  while(*tru_cons==1){

    sem_wait(&(tab_circulaire1->full1));
    pthread_mutex_lock(&(tab_circulaire1->mutex1));


    if(tab_circulaire1->i1<tab_circulaire1->count1){
      char * str = malloc(sizeof(char)*17);
      deleteString_Buff(str);
      //printf("%s\n",str);
      if(stack_get_size(tab_circulaire1->stack_fin)==0){
        stack_push(tab_circulaire1->stack_fin, str, strlen(str));
        free(str);
      }
      else{

        if(count(str, tab_circulaire1->consonne)== count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          // pop
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
          free(str);
        }

        else if(count(str, tab_circulaire1->consonne)>count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          while (tab_circulaire1->stack_fin->size != 0){
            char* del = stack_pop(tab_circulaire1->stack_fin, strlen(tab_circulaire1->stack_fin->head->data));
            free(del);
          }
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
          free(str);
        }
        else{
          free(str);
        }

      }
      tab_circulaire1->i1 = tab_circulaire1->i1+1;
    }
    else{
      char * str1 = malloc(sizeof(char)*17);
      deleteString_Buff(str1);
      if(stack_get_size(tab_circulaire1->stack_fin)==0){
        stack_push(tab_circulaire1->stack_fin, str1, strlen(str1));
        free(str1);
      }
      else{

        if(count(str1, tab_circulaire1->consonne)== count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          // pop
          stack_push(tab_circulaire1->stack_fin,str1,strlen(str1));
          free(str1);
        }

        else if(count(str1, tab_circulaire1->consonne)>count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){
          while (tab_circulaire1->stack_fin->size != 0){
           char *del1 = stack_pop(tab_circulaire1->stack_fin, strlen(tab_circulaire1->stack_fin->head->data));
            free(del1);
          }
          stack_push(tab_circulaire1->stack_fin,str1,strlen(str1));
          free(str1);
        }
        else{
          free(str1);
        }

      }
      tab_circulaire1->i1=tab_circulaire1->i1+1;
      *tru_cons = 0;
    }
    //printf("3c\n");
    if(tab_circulaire1->boucle_cons1==0){
      pthread_mutex_unlock(&(tab_circulaire1->mutex1));

      sem_post(&(tab_circulaire1->full1));
    }
    else{
      pthread_mutex_unlock(&(tab_circulaire1->mutex1));

      sem_post(&(tab_circulaire1->empty1));
    }

    //printf("4c\n");
  }
  //printf("5c\n");
  return NULL;
}

// un méthhode print.


void print_stack(stack_t* s){
  if(tab_circulaire1->out_true==1){
     int file = open(tab_circulaire1->file_out, O_RDWR | O_CREAT |O_TRUNC);
    while(stack_get_size(s)!=0){
      char* temp = concat((char *)stack_pop(s, strlen(tab_circulaire1->stack_fin->head->data)+1), "\n");
      write(file,temp,sizeof(char)*strlen(temp)+1);
      free(temp);
    }
    close(file);
  }
  else{
    while(stack_get_size(s)!=0){
      char* temp1 = (char *)stack_pop(s, strlen(tab_circulaire1->stack_fin->head->data)+1);
      printf("%s\n",temp1);
      free(temp1);
    }
  }
    destroy_cons();
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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
