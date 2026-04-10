#ifndef MAIN_H
#define MAIN_H

#include "vector.h"
#include <stddef.h>

void seed_random(void);

float random_float(float min, float max);

void init_scren(void);

void print_screen(void);

size_t count_particle_overlaps();

void particle_laws(particle_t *);

int interceptStreamParse(char *);

int count_particles(void);

void init_particle(int index);

bool draw_particles_by_amount(void);

void update(particle_t *, float dt);

int main(void);

#endif
