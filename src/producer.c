#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/producer.h"


int in=0;
int out=0;
uint8_t* buffer[32];

int ajoutByte_Prod(uint8_t *t, uint8_t * tab[], int tailleTab){
  tab[out]=t;
  if(out==0 && in !=0){
    in= in-1;
  }
  out = (out+1) %tailleTab;
  return 9;
}

void producer_routine(void* arg){
  char*fichier=(char*)arg;
  char *buf = malloc(32);
  FILE* f = fopen(fichier, "rb");
    if (f == NULL){
      exit(EXIT_FAILURE);
    }
    int j=0;
    while(fread(buf, 32, 1, f) > 0 && j!=10){
      j=j+1;
      //sem_wait(&empty);
      //pthread_mutex_lock(&mutex);
      ajoutByte_Prod(buf, buffer, 10);
      //pthread_mutex_unlock(&mutex);
      //sem_post(&full);
  }
}


void main(int argc, char* argv[]) {
  producer_routine(argv[1]);
//  for (int i = 0; i < 10; i++) {
    for (int i = 0; i < 10; i++){
      for(int j=0;j<32;j++){
              printf("%d", buffer[i][j]);
      }
    }
    printf("\n");
}
