
#include "stack.h"


stack_t* stack_init(void) {
	stack_t* s = (stack_t*) malloc(sizeof(stack_t));
	s->head = NULL;
	s->size = 0;

	return s;
}

size_t stack_get_size(stack_t* s) {
	return s->size;
}

int stack_push(stack_t* s, void* data, size_t data_size) {
	if (s == NULL) return -2;

	stack_node_t* new_head = (stack_node_t*) malloc(sizeof(stack_node_t));
	if (new_head == NULL) return -1;
	new_head->data = malloc(sizeof(data_size));
	if (new_head->data == NULL) {
		free(new_head);
		return -1;
	}

	memcpy(new_head->data, data, data_size);
	new_head->next = s->head;
	s->head = new_head;
	s->size++;

	return 0;
}

void* stack_peek(stack_t* s, size_t data_size) {
	if (s == NULL) return NULL;
	if (s->head == NULL) return NULL;

	void* ret = malloc(sizeof(data_size));

	memcpy(ret, s->head->data, data_size);

	return ret;
}

void* stack_pop(stack_t* s, size_t data_size) {
	if (s == NULL) return NULL;
	if (s->head == NULL) return NULL;

	void* ret = malloc(sizeof(data_size));

	memcpy(ret, s->head->data, data_size);

	stack_node_t* old_head = s->head;
	s->head = s->head->next;
	s->size--;

	free(old_head->data);
	free(old_head);

	return ret;
}

int stack_destroy(stack_t* s) {
	if (s == NULL) return -2;
	if (s->head != NULL) return -2;
	if (s->size != 0) return -2;

	free(s);
	s = NULL;

	return 0;
}
