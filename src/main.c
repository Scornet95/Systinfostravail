#include "include/main.h"

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  init_buf(arg.nthreads, arg.consonne, arg.out, arg.output);
  pthread_t producer;
  pthread_t consumer[arg.nthreads];
  pthread_t consumer1;
  int err;
  err = pthread_create(&(producer), NULL,producer_routine,(void *) arg.input);
  if(err!=0){
    printf("pthread_create producer");
  }

  for(int j=0;j<arg.nthreads;j=j+1){
    err =   pthread_create(&(consumer[j]), NULL,consumer_routine,NULL);
    if(err!=0){
      printf("pthread_create consumer_prod");
    }
  }

  err = pthread_create(&(consumer1), NULL, tri_String, NULL);
  if(err!=0){
    printf("pthread_create consumer1");
  }

  err = pthread_join(producer,NULL);
  if(err!=0){
    printf("pthread_join producer");
  }

  err = pthread_join(consumer1, NULL);
  if(err!=0){
    printf("pthread_join consumer");
  }

  for(int l=0;l<arg.nthreads;l=l+1){
    err = pthread_join(consumer[l],NULL);
        printf("un l est join");
    if(err!=0){
      printf("pthread_join consumer_prod");
    }
  }

  err = pthread_mutex_destroy(&(tab_circulaire->mutex));
  if(err!=0){
    printf("pthread_mutex_destroy mutex");
  }
  err = pthread_mutex_destroy(&(tab_circulaire->mutex1));
  if(err!=0){
    printf("pthread_mutex_destroy mutex1");
  }
  sem_destroy(&(tab_circulaire->empty));
  sem_destroy(&(tab_circulaire->full));
  sem_destroy(&(tab_circulaire->empty1));
  sem_destroy(&(tab_circulaire->full1));

  print_stack(tab_circulaire->stack_fin);

  free(tab_circulaire);
  return 0;
}

struct args_t init_args(int argc, char *argv[]){
  int opt;
  stack_t* stack = stack_init();
  Arg arguments = {
    1,
    0,
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
       arguments.out=1;
        break;
    }
  }
  for(;optind<argc;optind++){
    stack_push(arguments.input,argv[optind], strlen(argv[optind]));
  }
  return arguments;
}
