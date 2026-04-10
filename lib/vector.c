#include "../include/vector.h"
#include <stdlib.h>

/**
 * @file vector.c
 * @brief Dynamic vector operations for particle storage.
 */

/**
 * @brief Ensures vector capacity is at least @p new_capacity.
 * @param v Target vector.
 * @param new_capacity Requested minimum capacity.
 * @return `true` on success, `false` on allocation failure.
 */
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

/**
 * @brief Appends a particle to the end of the vector.
 * @param v Target vector.
 * @param value Particle value to append.
 * @return `true` on success, `false` when reallocation fails.
 */
bool vector_push_back(struct particle_vector *v, struct particle value) {
  if (v->size == v->capacity) {
    size_t next = (v->capacity == 0) ? 8 : v->capacity * 2;
    if (!vector_reserve(v, next))
      return false;
  }

  v->data[v->size++] = value;

  return true;
}

/**
 * @brief Clears all logical elements while keeping allocated memory.
 * @param v Target vector.
 */
void vector_clear(struct particle_vector *v) { v->size = 0; }

/**
 * @brief Frees vector storage and resets metadata.
 * @param v Target vector.
 */
void vector_free(struct particle_vector *v) {
  free(v->data);
  v->data = NULL;
  v->size = 0;
  v->capacity = 0;
}
