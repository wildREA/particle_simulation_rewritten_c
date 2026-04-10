#include "../include/posix_compatability.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * @file posix_compatability.c
 * @brief OS-dependent terminal and sleep helpers.
 */

/**
 * @brief Returns the active operating system family.
 * @return One value from `enum operating_system`.
 */
int detect_operating_system() {
#ifdef _WIN32
  return OS_WINDOWS;
#else
  return OS_POSIX;
#endif
}

/**
 * @brief Clears the terminal using platform-appropriate command.
 */
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

/**
 * @brief Suspends execution for a number of milliseconds.
 * @param milliseconds Delay duration in milliseconds.
 *
 * sleep() is used over Sleep() due to cross-compilation from Linux.
 * Linux does not have Windows SDKs.
 */
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
