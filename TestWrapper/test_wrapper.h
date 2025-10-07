#ifndef TEST_WRAPPER_H
#define TEST_WRAPPER_H

// This header is force-included by the compiler arguments.

// To prevent this header from renaming main within test_wrapper.c itself,
// the wrapper's source file defines IN_TEST_WRAPPER_IMPLEMENTATION before
// this file is processed.

// Step 1: Rename the user's main function, but not in the wrapper source itself.
#ifndef IN_TEST_WRAPPER_IMPLEMENTATION
    #define main user_main
#endif

// Step 2: Redirect standard I/O functions to our custom wrappers.
#define printf mock_printf
#define scanf mock_scanf

// Prototypes for functions in test_wrapper.c
int mock_printf(const char *format, ...);
int mock_scanf(const char *format, ...);

#endif /* TEST_WRAPPER_H */

