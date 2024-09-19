#ifdef TEST

#include "common.h"
#include <string.h>
#include <sys/wait.h>

#include "test_driver.h"

static size_t _test_count = 0, _passed_test_count = 0;

void __td_fork_failed(int errnum) {
    fprintf(stderr, "test_driver.c: fork() failed: %s", strerror(errnum));
    abort();
}

static void wait_failed(int errnum, pid_t pid) {
    fprintf(stderr, "test_driver.c: waitpid(%u) failed: %s", pid, strerror(errnum));
    abort();
}

static bool is_pass(pid_t pid) {
    int wstatus;
    if (waitpid(pid, &wstatus, 0) == -1)
        wait_failed(errno, pid);
    return WIFEXITED(wstatus) && (WEXITSTATUS(wstatus) == 0);
}

void __td_parent_pass(const char *file, int line, pid_t pid, const char *expr) {
    ++_test_count;
    fprintf(stderr, "%s:%d\ttest_expect(pass, %s)\n", file, line, expr);
    if (is_pass(pid)) ++_passed_test_count, fputs("... passed.\n", stderr);
    else fputs("... FAILED!\n", stderr);
}

void __td_parent_fail(const char *file, int line, pid_t pid, const char *expr) {
    ++_test_count;
    fprintf(stderr, "%s:%d\ttest_expect(fail, %s)\n", file, line, expr);
    if (!is_pass(pid)) ++_passed_test_count, fputs("... failed, as expected.\n", stderr);
    else fputs("... FAILED TO FAIL!\n", stderr);
}

void __td_parent_assert(const char *file, int line, pid_t pid, const char *expr) {
    ++_test_count;
    fprintf(stderr, "%s:%d\ttest_expect(assert, %s)\n", file, line, expr);
    if (is_pass(pid)) ++_passed_test_count, fputs("... ok.\n", stderr);
    else fputs("... ERROR!\n", stderr);
}

void test_entrypoint(void (*func)(void)) {
    func();
    fprintf(stderr, "\nTests passed: %lu out of %lu.\n", _passed_test_count, _test_count);
    exit((int)(_test_count != _passed_test_count));
}

#endif /* TEST */
