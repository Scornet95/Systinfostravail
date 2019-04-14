#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "include/consumer.h"
#include "lib/reverse.h"

int count=0;
int in=0;
int out=0;


void prendByte_Cons(uint8_t * tab[]){
   char* res=NULL;
  bool i = reversehash(tab[in],res,16);
   in = in+1;
}

int main(int argc, char  *argv[]){
  int tailleTab = 4;
  uint8_t (**buff) = malloc(sizeof(uint8_t)*32*tailleTab);
  uint8_t *hex_byt= malloc(sizeof(uint8_t)*32);
  char *hex_str = argv[1];
  int count = 0;
   for(int i=0;i<1;i=i+1){
     for(int j=0;j<32;j=j+1){
      count = count + (int) buff[i][j];
     }
  }
  printf("%d",count);
}
