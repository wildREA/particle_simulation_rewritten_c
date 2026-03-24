#include <stdbool.h>
#include <stddef.h>

/**
 * @struct particle
 * @brief Represents one simulated particle.
 */
struct particle {
  char emitter;
  float x;
  float y;
  float vx;
  float vy;
};

/**
 * @struct vector
 * @brief Represents a vector-like dynamic array.
 */
struct particle_vector {
  struct particle *data;
  size_t size;
  size_t capacity;
};

bool vector_reserve(struct particle_vector *v, size_t new_capacity);

bool vector_push_back(struct particle_vector *v, struct particle value);

void vector_clear(struct particle_vector *v);

void vector_free(struct particle_vector *v);
