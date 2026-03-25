#ifndef EXCEPTION_H
#define EXCEPTION_H

typedef enum exception_codes {
  OK = 0,
  EOF_FAILURE = 1,
  NO_RESULT = 2,
  INVALID_TYPE = 3,
  OUT_OF_BOUNDS = 4
} exception_codes;

void buf_helper(void);

void jmp_exception(exception_codes status);

#endif
