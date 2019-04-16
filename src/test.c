#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/stack.h"
#include "include/buffer.h"


int main(int argc, char *argv[]){
  uint8_t *buf = malloc(32);
      printf("zeb\n");
  FILE* f = fopen(argv[1], "rb");

  if (f == NULL){
    exit(EXIT_FAILURE);
  }
  while(fread(buf, 32, 1, f) > 0){
    //sem_wait(&empty);
    //pthread_mutex_lock(&mutex);
    //ajoutByte_Buff(buf, tab_circulaire->buffer, tab_circulaire->length, tab_circulaire);
    //pthread_mutex_unlock(&mutex);
    //sem_post(&full);
  }
}
void producer_routine(char *stack){

}
