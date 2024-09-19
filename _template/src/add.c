#include "common.h"
#include "add.h"

int add(int a, int b) {
    return a + b;
}

#ifdef TEST
void __add_h__run_tests() {
    test_expect(assert, add(2, 2) == 4);
}
#endif
