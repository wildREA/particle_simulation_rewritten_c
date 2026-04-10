cmake_minimum_required(VERSION 4.3.0)
project(particle_simulation_rewritten_c)

set(HEADER_FILES 
  include/main.h
  include/exceptions.h
  include/posix_compatability.h
  include/vector.h
)
set(SOURCES
  src/main.c
  lib/exceptions.c
  lib/posix_compatability.c
  lib/vector.c
)

add_executable(ParticleSim_C ${HEADER_FILES})

target_sources(ParticleSim_C
  PRIVATE
  ${SOURCES}
)

