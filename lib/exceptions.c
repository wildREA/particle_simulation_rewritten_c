#include "../include/exceptions.h"
#include <setjmp.h>
#include <stdio.h>

static jmp_buf s_jmp_buf;

void buf_helper() { longjmp(s_jmp_buf, 1); }

void jmp_exception(exception_codes status) {
  switch (status) {
  case OK:
    break;
  case EOF_FAILURE:
    fprintf(stderr, "Exit code [%d]: failed to read end of file\n", status);
    break;
  case NO_RESULT:
    fprintf(stderr, "Exit code [%d]: found unexpected null", status);
    break;
  case INVALID_TYPE:
    fprintf(stderr, "Exit code [%d]: incomplete type is not allowed\n", status);
    break;
  case OUT_OF_BOUNDS:
  default: ///< Cases that haven't been specified, switch-case unfinished
    fprintf(stderr, "Exit code [%d]: parsed value is out of bounds\n", status);
  }
}
