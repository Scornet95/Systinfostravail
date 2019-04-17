#include "include/main.h"
#include <semaphore.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  init_buf(arg.nthreads);
  pthread_t producer;
  pthread_t consumer;
  pthread_create(&producer, NULL,producer_routine,(void *) arg.input);
  pthread_create(&consumer, NULL,consumer_routine,NULL);
  pthread_join(producer,NULL);
  pthread_join(consumer,NULL);
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
