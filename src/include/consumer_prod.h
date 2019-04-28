#ifndef __CONSUMER_PROD_H
#define __CONSUMER_PROD_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include "reverse.h"
#include "buffer.h"


void* consumer_routine();
#endif
