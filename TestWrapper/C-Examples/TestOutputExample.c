#include <stdio.h>

void test_function() {
    printf("Hello from test_function!\n");
}

int main() {
    // Redirect stdout
    freopen("test_output.txt", "w", stdout);

    test_function();

    // Restore stdout (optional, good practice)
    freopen("/dev/tty", "w", stdout); // Or another appropriate default

    // Now you can open "test_output.txt" and verify its content
    return 0;
}