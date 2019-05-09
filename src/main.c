#include "include/main.h"

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  //initialisation du premier buffer.
  init_buf(arg.nthreads);
  //initialisation du deuxième buffer.
  init_buf_string(arg.nthreads, arg.consonne, arg.out, arg.output);
  pthread_t producer;
  pthread_t consumer[arg.nthreads];
  pthread_t consumer1;
  int err;
  //création du thread producer.
  err = pthread_create(&(producer), NULL,producer_routine,(void *) arg.input);
  if(err!=0){
    printf("pthread_create producer");
  }

 int tru = 1;
 //création des threads du consommateur et producteur.
  for(int j=0;j<arg.nthreads;j=j+1){
    err =   pthread_create(&(consumer[j]), NULL,consumer_routine,&tru);
    if(err!=0){
      printf("pthread_create consumer_prod");
    }
  }
int tru1 = 1;
//création du thread du deuxième consommateur.
  err = pthread_create(&(consumer1), NULL, tri_String, &tru1);
  if(err!=0){
    printf("pthread_create consumer1");
  }

//join le thread du premier producer.
  err = pthread_join(producer,NULL);
  if(err!=0){
    printf("pthread_join producer");
  }
// join les threads du producteurs et consommateur.
  for(int l=0;l<arg.nthreads;l=l+1){
    err = pthread_join(consumer[l],NULL);
    if(err!=0){
      printf("pthread_join consumer_prod");
    }
  }
// join le thread du deuxième consommateur.
  err = pthread_join(consumer1, NULL);
  if(err!=0){
    printf("pthread_join consumer");
  }

//détstruction des mutex.
  err = pthread_mutex_destroy(&(tab_circulaire->mutex));
  if(err!=0){
    printf("pthread_mutex_destroy mutex");
  }
  err = pthread_mutex_destroy(&(tab_circulaire1->mutex1));
  if(err!=0){
    printf("pthread_mutex_destroy mutex1");
  }

//destruction des sémaphore.
  sem_destroy(&(tab_circulaire->empty));
  sem_destroy(&(tab_circulaire->full));
  sem_destroy(&(tab_circulaire1->empty1));
  sem_destroy(&(tab_circulaire1->full1));

//impression de la stack composant les string.
  print_stack(tab_circulaire1->stack_fin);

  //déstruction du premier buffer.
  destroy_buffer_prod_cons();
  //destruction du fichier de sortie.
  free(tab_circulaire1->file_out);

  //destruction des structures buffer.
  free(tab_circulaire);
  free(tab_circulaire1);

  return 0;
}

//pre: les commande entré par l'utilisateur.
//post: les commandes entrées par le consommateure stocker dans les structure.
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
