#include "buffer.h"

void init_args(int numb_threads){
  tab_circulaire = malloc sizeof(arg_buffer_t);
  if (tab_circulaire == NULL){
    exit(EXIT_FAILURE);
  }
  tab_circulaire->length = (2*numb_threads);
  tab_circulaire->in = 0;
  tab_circulaire->out = 0;
  tab_circulaire->buffer = malloc(sizeof(uint8_t *)*tab_circulaire->length);
  if (tab_circulaire->buffer == NULL){
    exit(EXIT_FAILURE)
  }
  fot(int i = 0; i < tab_circulaire->length, i++){
    tab_circulaire->buffer[i] = malloc(sizeof(uint8_t)*32);
  }
}
