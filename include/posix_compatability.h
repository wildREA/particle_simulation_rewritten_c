#ifndef POSIX_COMPATABILITY_H
#define POSIX_COMPATABILITY_H

enum operating_system { OS_WINDOWS = 0, OS_POSIX = 1 };

int detect_operating_system(void);

void clear_terminal(void);

void sleep_for(int milliseconds);

#endif
