#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "main.h"
#include "stack.h"
#include "buffer.h"
#include "producer.h"
#include "reverse.h"
#include "sha256.h"
#include "consumer_prod.h"
#include "consumer.h"

#include <semaphore.h>
#include <pthread.h>

/* permet de récupérer les arguments */
typedef struct args_t {
  int nthreads;
  int consonne;
  char *output;
  stack_t *input;
} Arg;

struct args_t init_args(int argc, char *argv[]);

#endif
