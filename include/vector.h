#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @file vector.h
 * @brief Dynamic array interface for `struct particle`.
 *
 * C rewrite note:
 * - This header provides a minimal vector-like API replacing C++ container
 * usage.
 *
 * @todo Add explicit error-reporting strategy (error codes/logging) for
 * allocation failures.
 * @todo Add capacity-shrinking API if memory reclamation during runtime is
 * required.
 */

/**
 * @struct particle
 * @brief Represents one simulated particle.
 *
 * @var particle::emitter ASCII character used when rendering this particle.
 * @var particle::x Horizontal position in simulation space.
 * @var particle::y Vertical position in simulation space.
 * @var particle::vx Horizontal velocity.
 * @var particle::vy Vertical velocity.
 */
typedef struct particle {
  char emitter;
  float x;
  float y;
  float vx;
  float vy;
} particle_t;

void draw_particle(particle_t);

/**
 * @struct particle_vector
 * @brief Vector-like dynamic array for particles.
 *
 * @var particle_vector::data Pointer to contiguous particle storage.
 * @var particle_vector::size Number of initialized elements.
 * @var particle_vector::capacity Allocated element capacity.
 */
struct particle_vector {
  struct particle *data;
  size_t size;
  size_t capacity;
};

/**
 * @brief Ensures storage can hold at least `new_capacity` particles.
 * @param v Vector instance.
 * @param new_capacity Requested minimum capacity.
 * @return `true` on success or if no growth is needed; `false` on allocation
 * failure.
 */
bool vector_reserve(struct particle_vector *v, size_t new_capacity);

/**
 * @brief Appends one particle to the end of the vector.
 * @param v Vector instance.
 * @param value Particle to append.
 * @return `true` on success; `false` if growth/allocation fails.
 */
bool vector_push_back(struct particle_vector *v, struct particle value);

/**
 * @brief Clears logical contents while keeping allocated storage.
 * @param v Vector instance.
 */
void vector_clear(struct particle_vector *v);

/**
 * @brief Releases allocated storage and resets vector state.
 * @param v Vector instance.
 */
void vector_free(struct particle_vector *v);

#endif
