#include "consumer.h"

//pré: une variable pour la boucle while.
//post: a mis les string qu'il faut garder dans une stack.
void* tri_String(void * tru1){
  int *tru_cons= tru1;
  while(*tru_cons==1){

    sem_wait(&(tab_circulaire1->full1));
    pthread_mutex_lock(&(tab_circulaire1->mutex1));


    if(tab_circulaire1->i1<tab_circulaire1->count1){ //tant qu'il y a plus qu'un élement dans le deuxième buffer.
      char * str = malloc(sizeof(char)*17);
      deleteString_Buff(str);
      if(stack_get_size(tab_circulaire1->stack_fin)==0){ //si il n'y a pas encore délément dans la stack.
        stack_push(tab_circulaire1->stack_fin, str, strlen(str));
        free(str);
      }
      else{

        if(count(str, tab_circulaire1->consonne)== count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){//on ajoute le string si le string a autant de consonne ou de voyelle que le string sur la tête de la stack.
          // pop
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
          free(str);
        }

        else if(count(str, tab_circulaire1->consonne)>count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){//on supprime tous les string de la stack et on ajoute le nouveau string qui a plus de consonne ou de voyelle que l'ancien string à la tête de la stack.
          while (tab_circulaire1->stack_fin->size != 0){
            char* del = stack_pop(tab_circulaire1->stack_fin, strlen(tab_circulaire1->stack_fin->head->data));
            free(del);
          }
          stack_push(tab_circulaire1->stack_fin,str,strlen(str));
          free(str);
        }
        else{ // n'ajoute pas le string dans la stack car le string a moin de voyelle ou de consonne que le string à la tête de la stack.
          free(str);
        }

      }
      tab_circulaire1->i1 = tab_circulaire1->i1+1;
    }
    else{ // si il reste qu'un seul élément dans le deuxième buffer.
      char * str1 = malloc(sizeof(char)*17);
      deleteString_Buff(str1);
      if(stack_get_size(tab_circulaire1->stack_fin)==0){//si il n'y a pas encore délément dans la stack.
        stack_push(tab_circulaire1->stack_fin, str1, strlen(str1));
        free(str1);
      }
      else{

        if(count(str1, tab_circulaire1->consonne)== count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){//on ajoute le string si le string a autant de consonne ou de voyelle que le string sur la tête de la stack.
          // pop
          stack_push(tab_circulaire1->stack_fin,str1,strlen(str1));
          free(str1);
        }

        else if(count(str1, tab_circulaire1->consonne)>count(tab_circulaire1->stack_fin->head->data, tab_circulaire1->consonne)){//on supprime tous les string de la stack et on ajoute le nouveau string qui a plus de consonne ou de voyelle que l'ancien string à la tête de la stack.
          while (tab_circulaire1->stack_fin->size != 0){
           char *del1 = stack_pop(tab_circulaire1->stack_fin, strlen(tab_circulaire1->stack_fin->head->data));
            free(del1);
          }
          stack_push(tab_circulaire1->stack_fin,str1,strlen(str1));
          free(str1);
        }
        else{// n'ajoute pas le string dans la stack car le string a moin de voyelle ou de consonne que le string à la tête de la stack.
          free(str1);
        }

      }
      tab_circulaire1->i1=tab_circulaire1->i1+1;
      *tru_cons = 0;//permet de sortir de la boucle while.
    }
    if(tab_circulaire1->boucle_cons1==0){// si le consumer_produ a fini de mettre tous les string dans le deuxième buffer.
      pthread_mutex_unlock(&(tab_circulaire1->mutex1));

      sem_post(&(tab_circulaire1->full1));
    }
    else{ // si le consumer_prod n'a pas fini de mettre tous les string dans le deuxième buffer.
      pthread_mutex_unlock(&(tab_circulaire1->mutex1));

      sem_post(&(tab_circulaire1->empty1));
    }

  }
  return NULL;
}
//pré: une stack avec tous les bon string.
//post: met les string sur la sortie standard si il n'y a pas de fichier de sortie et écrit dans le fichier de sortie si il y en a un.
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
//pré: deux string.
//post: concaténation de deux string.
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
//pré: un string et une variable indiquant si il faut compter le nombre de consonne ou le nombre de voyelle.
//post: le nombre de voyelle ou le nombre de consonne.
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
