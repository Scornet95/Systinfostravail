#include "consumer.h"

void* consumer_routine(){
  int i = 0;
  while(i < 10){
  sem_wait(&(tab_circulaire->full));
  pthread_mutex_lock(&(tab_circulaire->mutex));
  char* res = malloc(sizeof(char)*16+1);
  uint8_t* tab32 = delete_buff();
  if (reversehash(tab32, res, 16)){
    printf("%s, %d\n", res, tab_circulaire->in);
  }
  pthread_mutex_unlock(&(tab_circulaire->mutex));
  sem_post(&(tab_circulaire->empty));
  i = i + 1;
  }
  return 0;
}
