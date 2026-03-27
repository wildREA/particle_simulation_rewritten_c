#ifndef EXCEPTION_H
#define EXCEPTION_H

typedef enum exception_codes {
  OK = 0,
  EOF_FAILURE = 1,
  LIMITED_ACCESS = 2,
  NO_RESULT = 3,
  INVALID_LENGTH = 4,
  INVALID_TYPE = 5,
  OUT_OF_BOUNDS = 6
} exception_codes;

void buf_helper(void);

void jmp_exception(exception_codes status);

#endif
