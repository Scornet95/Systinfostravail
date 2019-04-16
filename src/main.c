#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


#include "include/main.h"
#include "include/stack.h"
#include "include/prod_cons.h"

int main(int argc, char *argv[]) {
  Arg arg = init_args(argc, argv);
  init_buf(arg.tailleTab);
  producer_routine(arg.input);

  for(int i=0; i<10; i =i+1){
    for(int j=0;j<10; j=j+1){
      printf("%d", tab_circulaire->buffer)
    }
  }
  return 0;
}
//  Arg init = malloc(sizeof(struct args_t));
//  init.nthreads=1;
//  init.consonne=0;
//  init.output=NULL;
//  init.input= stack_init();
//}
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
