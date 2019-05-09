#ifndef __CONSUMER_H
#define __CONSUMER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "buffer1.h"
#include "stack.h"

void* tri_String(void * tru1);

void print_stack(stack_t* s);

char* concat(const char *s1, const char *s2);

int count(char* str, int consonne);

#endif
