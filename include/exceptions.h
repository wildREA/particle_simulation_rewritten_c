#ifndef EXCEPTION_H
#define EXCEPTION_H

/**
 * @file exceptions.h
 * @brief Exception-like exit and error signaling helpers.
 */

/**
 * @enum exception_codes
 * @brief Process exit and validation failure codes.
 */
typedef enum exception_codes {
  OK = 0,
  EOF_FAILURE = 1,
  LIMITED_ACCESS = 2,
  NO_RESULT = 3,
  INVALID_LENGTH = 4,
  INVALID_TYPE = 5,
  OUT_OF_BOUNDS = 6
} exception_codes;

/**
 * @brief Performs a non-local jump to the active jump buffer.
 */
void buf_helper(void);

/**
 * @brief Handles a status code by reporting and terminating when needed.
 * @param status Exception code to process.
 */
void jmp_exception(exception_codes status);

#endif
