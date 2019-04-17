#ifndef __STACK_H
#define __STACK_H

#include <string.h>
#include <stdlib.h>


typedef struct stack_t stack_t;
typedef struct stack_node_t stack_node_t;

struct stack_node_t {
	stack_node_t* next;
	void* data;
};

struct 	stack_t {
	size_t size;
	stack_node_t* head;
};

stack_t* stack_init(void);

size_t stack_get_size(stack_t* s);

int stack_push(stack_t* s, void* data, size_t data_size);

void* stack_peek(stack_t* s, size_t data_size);

void* stack_pop(stack_t* s, size_t data_size);

int stack_destroy(stack_t* s);

#endif // __STACK_H
