#ifndef TEST_DRIVER_H
#define TEST_DRIVER_H 1

#ifdef TEST

#include "common.h"

void test_entrypoint(void (*run_tests)(void));

#define test_expect(key, expr) {\
    pid_t __pid = fork();\
    switch (__pid) {\
        case -1: __td_fork_failed(errno);\
        case 0: __td_child_##key(expr); exit(0);\
        default: __td_parent_##key(__FILE__, __LINE__, __pid, #expr);\
    }\
}

void __td_fork_failed(int errnum);

void __td_parent_pass(const char *__file, int __line, pid_t __pid, const char *__expr);
void __td_parent_fail(const char *__file, int __line, pid_t __pid, const char *__expr);
void __td_parent_assert(const char *__file, int __line, pid_t __pid, const char *__expr);

#define __td_child_pass(expr) (expr)
#define __td_child_fail(expr) (expr)
#define __td_child_assert(expr) assert(expr)

#else /* TEST */
#define test_entrypoint(f) ((void)0)
#define test_expect(k, e) ((void)0)
#endif /* TEST */

#endif /* !TEST_DRIVER_H */
