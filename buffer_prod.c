
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count=0;
int in=0;
int out=0;

uint8_t ** ajoutString_Prod(uint8_t *t, uint8_t ** tab, int tailleTab){
  int temp = (out+1) % tailleTab;
  tab[temp]=t;
  out = out+1;
  count = count +1;
  return tab;
}

uint8_t* convertString(char* str){
  uint8_t *tab1=malloc(sizeof(uint8_t)*32);
  if(tab1==NULL){
    return NULL;
  }
  char *temp= malloc(sizeof(char)*2+1);
  if(temp==NULL){
    return NULL;
  }
  int j = 0;
  for(int i=0; i<strlen(str);i=i+2){
    temp[0] = str[i];
    temp[1] = str[i+1];
    tab1[j] = (uint8_t) strtol(temp,NULL,16);
    j = j+1;
  }
  return tab1;
}



int main(int argc, char  *argv[]){
  int tailleTab = 4;
  uint8_t (**buff) = malloc(sizeof(uint8_t)*32*tailleTab);
  uint8_t *hex_byt= malloc(sizeof(uint8_t)*32);
  char *hex_str = argv[1];
  hex_byt = convertString(hex_str);
  buff = ajoutString_Prod(hex_byt, buff, tailleTab);
  buff = ajoutString_Prod(hex_byt,buff, tailleTab);
  buff = ajoutString_Prod(hex_byt, buff, tailleTab);
  buff = ajoutString_Prod(hex_byt,buff, tailleTab);
  int count = 0;
   for(int i=0;i<1;i=i+1){
     for(int j=0;j<32;j=j+1){
      count = count + (int) buff[i][j];
     }
  }
  printf("%d",count);
}
