# particle_simulation_rewritten_c

Terminal particle simulation rewritten in C.

## Architecture

The project is structured into a small set of focused C modules:

- `src/main.c`: simulation entry point and main loop
	- initializes particles from user input
	- updates position each frame (`dt = 0.1`)
	- applies boundary bounce rules
	- renders a fixed `20 x 20` ASCII grid
	- detects overlaps and spawns extra particles dynamically
- `lib/vector.c` + `include/vector.h`: dynamic particle storage
	- custom vector-like container for `particle_t`
	- reserve/push/clear/free operations for runtime growth
- `lib/posix_compatability.c` + `include/posix_compatability.h`: platform helpers
	- terminal clear function
	- millisecond sleep wrapper for frame pacing
- `lib/exceptions.c` + `include/exceptions.h`: input/error status handling
	- centralized status codes
	- exits with descriptive messages on invalid input

Core runtime flow:

1. Ask user for initial particle mode (single or multiple).
2. Initialize particle vector with randomized position/velocity.
3. For each frame, clear screen, draw particles, update motion, and print.
4. If particles overlap in the same rendered cell, add more particles.
5. Stop after 10 seconds of simulated time.

## Tech

- Language (minimum): C99
- Build system: CMake (primary), GCC/Clang command-line build (supported)
- Standard library usage:
	- memory management (`realloc`, `free`)
	- timing/random (`time`, `srand`, `rand`)
	- terminal/process helpers (`system`, `usleep`)
- Output: plain terminal ASCII rendering (no graphics framework)

## Run locally

### Option 1: CMake (recommended)

```bash
cmake -S . -B build-local
cmake --build build-local
./build-local/ParticleSim_C
```

### Option 2: Direct GCC compile

```bash
mkdir -p build
gcc -std=c11 -Wall -Wextra -Werror -Iinclude \
	src/main.c lib/vector.c lib/exceptions.c lib/posix_compatability.c \
	-o build/particle_sim
./build/particle_sim
```

When prompted, choose:

- `1` for a single starting particle
- `2` for multiple starting particles (currently 4)

