#ifndef COMMON_H
#define COMMON_H 1

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#ifndef NDEBUG
#define debug_puts(string) ( (void)fputs((string), stderr) )
#define debug_printf(fmt, ...) ( (void)fprintf(stderr, (fmt), ##__VA_ARGS__) )
#else /* !NDEBUG */
#define debug_puts(string) ((void)0)
#define debug_printf(fmt, ...) ((void)0)
#endif /* !NDEBUG */

// load after common.h
#include "test_driver.h"

#endif /* !COMMON_H */
