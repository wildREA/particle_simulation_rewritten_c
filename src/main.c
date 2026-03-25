#define _DEFAULT_SOURCE

#include "../include/main.h"
#include "../include/exceptions.h"
#include "../include/vector.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#endif

/**
 * @file main.cc
 * @brief Terminal-based particle simulation on a fixed 2D ASCII grid.
 *
 * The program:
 * - asks for an initial particle count,
 * - simulates particle movement with simple boundary bounce rules,
 * - renders each frame to a text buffer,
 * - adds particles when overlap is detected,
 * - stops after a fixed simulated duration.
 */

/// Width of the simulation screen in characters.
#define width 20
/// Height of the simulation screen in characters.
#define height 20

/// ASCII frame buffer (indexed as screen[row][col]).
char screen[width][height];

/// Dynamic collection of all active particles.
static struct particle_vector particles = {0};

/**
 * @brief Generates a random float in [min, max].
 * @param min Lower bound.
 * @param max Upper bound.
 * @return Random floating-point value.
 */
float random_float(float min, float max) {
  float unit = (float)rand() / (float)RAND_MAX;
  return min + (max - min) * unit;
}

/**
 * @brief Resets the screen buffer to background characters.
 */
void init_screen() {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      screen[row][col] = '-';
    }
  }
}

/**
 * @brief Draws one particle into the screen buffer if in bounds.
 * @param p Particle to draw.
 */
void draw_particle(struct particle p) {
  int col = (int)p.x;
  int row = (int)p.y;

  if (row >= 0 && row < height && col >= 0 && col < width) {
    screen[row][col] = p.emitter;
  }
}

/**
 * @brief Prints the current screen buffer to stdout.
 */
void print_screen() {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      printf("%c", screen[row][col]);
    }

    printf("\n");
  }

  printf("\n");
}

/**
 * @brief Checks whether any two particles occupy the same exact position.
 * @return true if at least one overlap exists; otherwise false.
 *
 * @warning Comparison uses exact float equality for x/y.
 */
bool is_particle_overlapping() {
  for (size_t i = 0; i < particles.size; i++) {
    for (size_t j = i + 1; j < particles.size; j++) {
      if (particles.data[i].x == particles.data[j].x &&
          particles.data[i].y == particles.data[j].y) {
        return true;
      }
    }
  }

  return false;
}

/**
 * @brief Applies boundary rules to keep a particle visible in the grid.
 * @param p Particle to clamp and bounce.
 *
 * Velocity is inverted and damped by factor `0.7` on collision.
 */
void particle_laws(struct particle *p) {
  // Keep particle visible (bounce)
  if (p->x < 0.0f) {
    p->x = 0.0f;
    p->vx *= -0.7f;
  }
  if (p->x >= width) {
    p->x = width - 1.0f;
    p->vx *= -0.7f;
  }
  if (p->y < 0.0f) {
    p->y = 0.0f;
    p->vy *= -0.7f;
  }
  if (p->y >= height) {
    p->y = height - 1.0f;
    p->vy *= -0.7f;
  }
}

/**
 * @brief Reads initial particle count from stdin.
 * @return Number of particles to spawn (minimum 1).
 *
 * Empty or invalid input falls back to 1.
 */
int count_particles() {
  printf("1) Singular\n2) Multiple\nAmount of particles: ");

  char input[16] = {0};
  int amount = 1;

  if (!fgets(input, sizeof(input), stdin)) {
    jmp_exception(EOF_FAILURE);
    return 0;
  }

  if (input[0] == '\0') {
    jmp_exception(NO_RESULT);
    return 0;
  }

  for (int i = 0; input[i] != '\0'; i++) {
    if (!isdigit((unsigned char)input[i])) {
      jmp_exception(INVALID_TYPE);
      return 0;
    }
  }

  int parsed = atoi(input);

  if (!(0 < parsed) && !(parsed < 3)) {
    jmp_exception(OUT_OF_BOUNDS);
    return 0;
  }
  amount = parsed;

  printf("\ncount: %d\n", amount);
  sleep(1);

  return amount;
}

/**
 * @brief Creates and appends one particle with randomized state.
 * @param index Spawn index used for small anti-overlap offsets.
 */
void init_particle(int index) {
  struct particle p = {0};
  p.emitter = '*';
  p.x = random_float(1.0f, width - 2.0f);
  p.y = random_float(1.0f, height - 2.0f);
  p.vx = random_float(-4.0f, 4.0f);
  p.vy = random_float(-4.0f, 4.0f);

  // Small index-based offset to reduce initial overlap in dense spawns
  p.x += (float)(index % 3) * 0.2f;
  p.y += (float)((index / 3) % 3) * 0.2f;

  vector_push_back(&particles, p);
}

/**
 * @brief Prompts user for particle count, then initializes that many particles.
 */
bool draw_particles_by_amount() {
  int count = count_particles();
  if (count < 1) {
    return false;
  }

  vector_clear(&particles);
  vector_reserve(&particles, (size_t)count);

  for (int i = 0; i < count; i++) {
    init_particle(i);
  }

  return true;
}

enum operating_system { OS_WINDOWS = 0, OS_POSIX = 1 };

int detect_operating_system() {
#ifdef _WIN32
  return OS_WINDOWS;
#else
  return OS_POSIX;
#endif
}

void sleep_for(int milliseconds) {
  switch (detect_operating_system()) {
  case OS_WINDOWS:
#ifdef _WIN32
    Sleep((DWORD)milliseconds);
#endif
    break;
  case OS_POSIX:
  default:
    sleep(milliseconds * 0.001);
    break;
  }
}

/**
 * @brief Advances one particle by a fixed time step.
 * @param p Particle to update.
 * @param dt Time step in seconds.
 */
void update(struct particle *p, float dt) {
  /*
   * Position from velocity over time
   * s_r = v_0 * t
   */
  p->x += p->vx * dt;
  p->y += p->vy * dt;

  particle_laws(p);
}

/**
 * @brief Program entry point.
 * @return 0 on normal completion.
 */
int main() {
  float dt = 0.1f;      // step size
  float elapsed = 0.0f; // simulated time
  bool running = true;

  if (!draw_particles_by_amount()) {
    vector_free(&particles);
    return EXIT_FAILURE;
  }

  while (running) {
    system("clear");
    init_screen();

    for (size_t i = 0; i < particles.size; i++) {
      struct particle *p = &particles.data[i];
      draw_particle(*p);
      update(p, dt);
    }

    if (is_particle_overlapping()) {
      vector_reserve(&particles, particles.size + 2);
      for (unsigned i = 0; i < 2; i++, init_particle((int)particles.size))
        ;
    }

    print_screen();

    sleep_for(50); // miliseconds
    elapsed += dt;
    running = (elapsed < 10.0f); // 10 / 0.1 = 100
  }

  vector_free(&particles);

  return 0;
}
