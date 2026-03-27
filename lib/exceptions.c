#include "../include/exceptions.h"
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

static jmp_buf s_jmp_buf;

void buf_helper() { longjmp(s_jmp_buf, 1); }

void jmp_exception(exception_codes status) {
  switch (status) {
  case OK:
    break;
  case EOF_FAILURE:
    fprintf(stderr, "Exit code [%u]: failed to read end of file\n", status);
    exit(status);
    break;
  case LIMITED_ACCESS:
    fprintf(stderr, "Exit code [%u]: unable to access beyond limit\n", status);
    exit(status);
    break;
  case NO_RESULT:
    fprintf(stderr, "Exit code [%u]: found unexpected null\n", status);
    exit(status);
    break;
  case INVALID_LENGTH:
    fprintf(stderr, "Exit code [%u]: invalid length caused overflow\n", status);
    exit(status);
    break;
  case INVALID_TYPE:
    fprintf(stderr, "Exit code [%u]: incomplete type is not allowed\n", status);
    exit(status);
    break;
  case OUT_OF_BOUNDS:
    fprintf(stderr, "Exit code [%u]: parsed value is out of bounds\n", status);
    exit(status);
    break;
  }
}
