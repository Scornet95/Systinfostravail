
#include "stack.h"

//pré:rien.
//post:initialise une stack.
stack_t* stack_init(void) {
	stack_t* s = (stack_t*) malloc(sizeof(stack_t));
	s->head = NULL;
	s->size = 0;

	return s;
}
//pré: une stack en entrée.
//post:le nombre d'élément dans la stack.
size_t stack_get_size(stack_t* s) {
	return s->size;
}
//pré: une stack, une donné et la taille de la donné.
//post: ajouté l'élément sur la tête de la stack.
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

//pré:une stack, la taille de l'élément à la tête de la stack.
//post:return l'élément à la tête de la stack.
void* stack_peek(stack_t* s, size_t data_size) {
	if (s == NULL) return NULL;
	if (s->head == NULL) return NULL;

	void* ret = malloc(sizeof(data_size));

	memcpy(ret, s->head->data, data_size);

	return ret;
}

//pré:une stack et la taille de l'élément qui va être enlevé.
//post:enlève l'élément à la tête de la stack et il le retourne.
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
//pré: une stack.
//post:détruit//free la stack.
int stack_destroy(stack_t* s) {
	if (s == NULL) return -2;
	if (s->head != NULL) return -2;
	if (s->size != 0) return -2;

	free(s);
	s = NULL;

	return 0;
}
