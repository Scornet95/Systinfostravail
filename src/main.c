#include "include/main.h"

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  init_buf(arg.nthreads);
  pthread_t producer;
  pthread_t consumer[arg.nthreads];
  int err;

  //printf("1\n");

 err = pthread_mutex_init(&(tab_circulaire->mutex),NULL);
  if(err!=0){
   printf("pthread_mutex_init");
  }
  
  //printf("2\n");

  err = sem_init(&(tab_circulaire->empty), 0, tab_circulaire->length-1);
  if(err!=0){
    printf("sem_init");
  }

  err = sem_init(&(tab_circulaire->full), 0, 0);
  if(err!=0){
    printf("sem_init");
  }

  //printf("3\n");

  err = pthread_create(&(producer), NULL,producer_routine,(void *) arg.input);
  if(err!=0){
    printf("pthread_create producer");
  }

  //printf("4\n");


  for(int j=0;j<arg.nthreads;j=j+1){
    err =   pthread_create(&(consumer[j]), NULL,consumer_routine,NULL);
    printf("le numéro du thead %d\n", j);
    if(err!=0){
      printf("pthread_create consumer");
    }
  }

  //printf("5\n");


  err = pthread_join(producer,NULL);
  if(err!=0){
    printf("pthread_join producer");
  }

  //printf("6\n");

  for(int l=0;l<arg.nthreads;l=l+1){
    err = pthread_join((consumer[l]),NULL);
    if(err!=0){
      printf("pthread_join consumer");
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
