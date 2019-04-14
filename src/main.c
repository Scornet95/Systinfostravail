#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


#include "main.h"
#include "stack.h"

int main(int argc, char *argv[]) {

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
