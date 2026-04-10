#include "../include/posix_compatability.h"
#include <stdlib.h>
#include <unistd.h>

int detect_operating_system() {
#ifdef _WIN32
  return OS_WINDOWS;
#else
  return OS_POSIX;
#endif
}

void clear_terminal() {
  switch (detect_operating_system()) {
  case OS_WINDOWS:
#ifdef _WIN32
    system("cls");
#endif
    break;
  case OS_POSIX:
  default: {
    system("clear");
  }
  }
}

void sleep_for(int milliseconds) {
  switch (detect_operating_system()) {
  case OS_WINDOWS:
#ifdef _WIN32
    sleep(milliseconds / 1000);
#endif
    break;
  case OS_POSIX:
  default: {
    usleep(milliseconds * 1000);
    break;
  }
  }
}
