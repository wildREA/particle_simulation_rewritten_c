#ifndef POSIX_COMPATABILITY_H
#define POSIX_COMPATABILITY_H

/**
 * @file posix_compatability.h
 * @brief Small operating-system compatibility utilities.
 */

/**
 * @enum operating_system
 * @brief Supported operating system families.
 */
enum operating_system { OS_WINDOWS = 0, OS_POSIX = 1 };

/**
 * @brief Detects current operating system family.
 * @return One value from `enum operating_system`.
 */
int detect_operating_system(void);

/**
 * @brief Clears the active terminal screen.
 */
void clear_terminal(void);

/**
 * @brief Sleeps for a requested number of milliseconds.
 * @param milliseconds Delay duration in milliseconds.
 */
void sleep_for(int milliseconds);

#endif
