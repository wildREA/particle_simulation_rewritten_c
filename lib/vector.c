#include "../include/vector.h"
#include <stdlib.h>

bool vector_reserve(struct particle_vector *v, size_t new_capacity) {
  if (new_capacity <= v->capacity)
    return true;

  struct particle *new_data =
      realloc(v->data, new_capacity * sizeof(*new_data));

  if (!new_data)
    return false;

  v->data = new_data;
  v->capacity = new_capacity;

  return true;
}

bool vector_push_back(struct particle_vector *v, struct particle value) {
  if (v->size == v->capacity) {
    size_t next = (v->capacity == 0) ? 8 : v->capacity * 2;
    if (!vector_reserve(v, next))
      return false;
  }

  v->data[v->size++] = value;

  return true;
}

void vector_clear(struct particle_vector *v) { v->size = 0; }

void vector_free(struct particle_vector *v) {
  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}
