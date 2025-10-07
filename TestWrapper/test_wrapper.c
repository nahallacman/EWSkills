// Define this macro BEFORE any headers are included.
// This prevents test_wrapper.h from renaming this file's `main` function.
#define IN_TEST_WRAPPER_IMPLEMENTATION

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// It's good practice to include this header to ensure consistency.
#include "test_wrapper.h"

// The user's main function, which has been renamed to `user_main` by test_wrapper.h.
// Declaring it this way allows the linker to find it regardless of its original arguments.
extern int user_main();

// --- Global state for the wrapper ---
#define MAX_LINES 50
#define LINE_LENGTH 256

static char* inputs[MAX_LINES];
static int input_count = 0;
static int current_input_index = 0;

static char* expected_outputs[MAX_LINES];
static int expected_outputs_count = 0;
static int current_expected_output_index = 0;

// --- Private Helper Functions ---

// Cleans up memory used for test data
static void cleanup() {
    for (int i = 0; i < input_count; i++) free(inputs[i]);
    for (int i = 0; i < expected_outputs_count; i++) free(expected_outputs[i]);
    // Reset counters for next potential run (though process exits)
    input_count = 0;
    expected_outputs_count = 0;
    current_input_index = 0;
    current_expected_output_index = 0;
}

// Reads test inputs and expected outputs from the data file.
static int setup_test_io() {
    FILE* file = fopen("current_test_data.txt", "r");
    if (!file) {
        fprintf(stderr, "Wrapper Error: Could not open 'current_test_data.txt'.\n");
        return 1;
    }

    char line[LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0; // Remove newline character

        if (strncmp(line, "INPUT:", 6) == 0) {
            if (input_count < MAX_LINES) {
                inputs[input_count++] = strdup(line + 6);
            }
        } else if (strncmp(line, "EXPECTED:", 9) == 0) {
            if (expected_outputs_count < MAX_LINES) {
                expected_outputs[expected_outputs_count++] = strdup(line + 9);
            }
        }
    }
    fclose(file);
    return 0;
}

// --- Mocked I/O Functions ---

// Custom printf that captures output and validates it against expected output.
int mock_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char temp_buffer[LINE_LENGTH];
    int count = vsnprintf(temp_buffer, sizeof(temp_buffer), format, args);
    va_end(args);

    if (count < 0) return count;

    if (current_expected_output_index >= expected_outputs_count) {
        fprintf(stderr, "\nWrapper Error: Unexpected output generated.\n  Output: \"%s\"\n", temp_buffer);
        exit(1);
    }

    if (strcmp(temp_buffer, expected_outputs[current_expected_output_index]) != 0) {
        fprintf(stderr, "\nWrapper Error: Output mismatch.\n");
        fprintf(stderr, "  Expected: \"%s\"\n", expected_outputs[current_expected_output_index]);
        fprintf(stderr, "  Actual:   \"%s\"\n", temp_buffer);
        exit(1);
    }
    current_expected_output_index++;
    return count;
}

// Custom scanf that provides stored inputs from the test file.
int mock_scanf(const char *format, ...) {
    // fprintf(stderr, "DEBUG: mock_scanf() was called!\n");

    if (current_input_index >= input_count) {
        fprintf(stderr, "Wrapper Error: scanf called, but no more inputs are available.\n");
        return EOF;
    }

    va_list args;
    va_start(args, format);
    int ret = vsscanf(inputs[current_input_index], format, args);
    va_end(args);
    current_input_index++;
    return ret;
}

// --- Main Test Entry Point ---

// This is the real entry point for the test executable. Because we defined
// IN_TEST_WRAPPER_IMPLEMENTATION, it does NOT get renamed by the header file.
int main(void) {
    if (setup_test_io() != 0) {
        cleanup();
        return 1;
    }

    // Call the user's program, which was renamed to `user_main`.
    user_main();

    if (current_expected_output_index < expected_outputs_count) {
        fprintf(stderr, "\nWrapper Error: Not all expected outputs were produced.\n");
        fprintf(stderr, "  Expected output \"%s\" was never printed.\n", expected_outputs[current_expected_output_index]);
        cleanup();
        return 1;
    }

    cleanup();
    return 0; // Success
}