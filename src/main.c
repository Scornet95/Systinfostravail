#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>


#include "include/main.h"
#include "include/stack.h"
#include "include/prod_cons.h"

int main(int argc, char *argv[]) {
 Arg arg = init_args(argc, argv);
 arg_prod_cons_t arg1= {
   arg->input,
   0,
   0,
   arg->nthreads,
   NULL,
   arg->consonne,
 };
  producer_routine(arg1);
  for(int j=0;j<20;j++){
    for(int i=0;i<20;i++){
          printf("%d", arg1.buffer[i][j]);
    }
  }
  return 0;
}
//void init_struct(){
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
