#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "include/buffer.h"
#include "include/main.h"

int main(int argc, char const *argv[]) {
  /*d'abord recupérer les arguments dans la structure*/
  /*créer ldeux sémpahores et un mutex (empty, full, mutex buf-hash)*/
  /*faire appel aux threads producteur/consommateur*/
  int sem_init(&empty, 0, 0);
  int sem_init(&full, 0, nthreads);
  return 0; /*declare l'argument args_t afin d'avoir les arguments en ordre */

};

struct args_t init_args(int argc, char *argv[]){
  int opt;
  struct args_t* arguments = malloc(sizeof(struct args_t));
  if arguments== NULL{
    exit(EXIT_FAILURE);
  }
  while ((opt = getopt(argc, argv, "t:o:c"))){
    switch(opt){
      case 't':
        arguments->nthreads = (int) optarg;
        break;
      case 'c':
        arguments->consonne = true;
        break;
      case 'o' :
        strcopy(arguments->output, optarg);
        break;
    }
    for (; optind < argc; optind++){
      push(arguments->input, argv[optind]);
    return arguments;
  }

}
void consumer_routine(){
  while(){

  }
};
void producer_routine(stack_t args){
  char *buf = malloc(32);
  while (args->input->length != 0){
    int fd = open(args->input->head, O_RDONLY);
    if (fd == -1){
      exit(EXIT_FAILURE)
    }
    while(read(fd, buf, 32) > 0){
      sem_wait(&empty);
      pthread_mutex_lock(&mutex);
    /*Insert in the buffer*/
      insert_item();
      pthread_mutex_unlock(&mutex);
      sem_post(&full);
  }
  args.pop();
}
