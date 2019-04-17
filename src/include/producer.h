#ifndef __PRODUCER_H
#define __PRODUCER_H
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "stack.h"
#include "buffer.h"

#include "stack.h"

void* producer_routine(stack_t* stack);

#endif // __PRODUCER_H
