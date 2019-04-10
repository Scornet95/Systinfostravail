#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char const *argv[]) {
  ; /*declare l'argument args_t afin d'avoir les arguments en ordre */

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
  }
  for (; optind < argc; optind++){
    push(arguments->input, argv[optind]);
  return arguments;
}
