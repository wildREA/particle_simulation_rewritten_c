#ifndef MAIN_H
#define MAIN_H

#include "vector.h"
#include <stddef.h>

/**
 * @file main.h
 * @brief Public interface for the particle simulation entry module.
 */

/**
 * @brief Seeds the pseudo-random number generator.
 */
void seed_random(void);

/**
 * @brief Generates a random floating-point number in a range.
 * @param min Lower inclusive bound.
 * @param max Upper inclusive bound.
 * @return Random float between @p min and @p max.
 */
float random_float(float min, float max);

/**
 * @brief Initializes the ASCII screen buffer.
 */
void init_scren(void);

/**
 * @brief Prints the ASCII screen buffer to standard output.
 */
void print_screen(void);

/**
 * @brief Counts how many particle pairs overlap in the same rendered cell.
 * @return Number of unique overlapping pairs.
 */
size_t count_particle_overlaps();

/**
 * @brief Applies wall/bounce constraints to a particle.
 * @param p Particle to clamp and reflect when out of bounds.
 */
void particle_laws(particle_t *p);

/**
 * @brief Validates and normalizes one-line numeric user input.
 * @param input Mutable buffer read from standard input.
 * @return 0 when valid; non-zero when invalid.
 */
int interceptStreamParse(char *);

/**
 * @brief Reads and validates the initial particle count selection.
 * @return Number of particles to spawn.
 */
int count_particles(void);

/**
 * @brief Creates and stores one randomized particle.
 * @param index Spawn index used for deterministic offsetting.
 */
void init_particle(int index);

/**
 * @brief Initializes particles according to user selection.
 * @return `true` if initialization succeeded; otherwise `false`.
 */
bool draw_particles_by_amount(void);

/**
 * @brief Advances one particle by a simulation time step.
 * @param p Particle to update.
 * @param dt Time step in seconds.
 */
void update(particle_t *p, float dt);

/**
 * @brief Runs the simulation program.
 * @return Process exit status.
 */
int main(void);

#endif
