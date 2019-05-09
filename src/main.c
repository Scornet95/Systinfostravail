#include "include/main.h"

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  init_buf(arg.nthreads);
  init_buf_string(arg.nthreads, arg.consonne, arg.out, arg.output);
  pthread_t producer;
  pthread_t consumer[arg.nthreads];
  pthread_t consumer1;
  int err;
  err = pthread_create(&(producer), NULL,producer_routine,(void *) arg.input);
  if(err!=0){
    printf("pthread_create producer");
  }

 int tru = 1;
  for(int j=0;j<arg.nthreads;j=j+1){
    err =   pthread_create(&(consumer[j]), NULL,consumer_routine,&tru);
    if(err!=0){
      printf("pthread_create consumer_prod");
    }
  }
int tru1 = 1;
  err = pthread_create(&(consumer1), NULL, tri_String, &tru1);
  if(err!=0){
    printf("pthread_create consumer1");
  }

  err = pthread_join(producer,NULL);
  if(err!=0){
    printf("pthread_join producer");
  }

  for(int l=0;l<arg.nthreads;l=l+1){
    err = pthread_join(consumer[l],NULL);
    if(err!=0){
      printf("pthread_join consumer_prod");
    }
  }

  err = pthread_join(consumer1, NULL);
  if(err!=0){
    printf("pthread_join consumer");
  }

  err = pthread_mutex_destroy(&(tab_circulaire->mutex));
  if(err!=0){
    printf("pthread_mutex_destroy mutex");
  }
  err = pthread_mutex_destroy(&(tab_circulaire1->mutex1));
  if(err!=0){
    printf("pthread_mutex_destroy mutex1");
  }

  sem_destroy(&(tab_circulaire->empty));
  sem_destroy(&(tab_circulaire->full));
  sem_destroy(&(tab_circulaire1->empty1));
  sem_destroy(&(tab_circulaire1->full1));

  print_stack(tab_circulaire1->stack_fin);
  destroy_buffer_prod_cons();
  free(tab_circulaire1->file_out);
  free(tab_circulaire);
  free(tab_circulaire1);

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
