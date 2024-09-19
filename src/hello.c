#include "common.h"
#include "add.h"

void tests();

int main() {
    test_entrypoint(tests);
    puts("Hello, world!");
    return 0;
}

void tests() {
#ifdef TEST
    __add_h__run_tests();
    test_expect(fail, assert(2 + 2 == 5));
    /* test_expect(pass, assert(2 + 2 == 5)); */
#endif
}
