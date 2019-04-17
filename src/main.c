#include "include/main.h"
#include <semaphore.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
  printf("1");
  Arg arg = init_args(argc, argv);
  printf("1");

  init_buf(arg.nthreads);
  printf("1");
  pthread_t producer;
  pthread_create(&producer, NULL,&(producer_routine),(void *) arg.input);
  printf("1");
  for(int i=0; i<tab_circulaire->length; i =i+1){
    for(int j=0;j<32; j=j+1){
      printf("%d, %d\n", tab_circulaire->buffer[i][j], tab_circulaire->length);
    }
  }
  return 0;
}

struct args_t init_args(int argc, char *argv[]){
  int opt;
  stack_t* stack = stack_init();
  Arg arguments = {
    1,
    0,
    "stdout",
    stack
  };

  while ((opt = getopt(argc, argv, ":ct:o:")) !=-1){
    switch(opt){
      case 't' :
       arguments.nthreads = atoi(optarg);
       break;
      case 'c':
        arguments.consonne = 1;
        break;
      case 'o' :
        arguments.output = malloc(sizeof(char)*strlen(optarg)+1);
        strcpy(arguments.output, optarg);
        break;
    }
  }
  for(;optind<argc;optind++){
    stack_push(arguments.input,argv[optind], strlen(argv[optind]));
  }
  return arguments;
}
