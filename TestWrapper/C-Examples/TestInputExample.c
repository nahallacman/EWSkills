#include <stdio.h>

void test_function() {
    int num;
    printf("Enter a number: \n");
    scanf("%d", &num);
    printf("You entered: %d\n", num);
}

int main() {
    // Create a dummy input file
    FILE *input_file = fopen("test_input.txt", "w");
    fprintf(input_file, "123\n");
    fclose(input_file);

    // Redirect stdin
    freopen("test_input.txt", "r", stdin);

    test_function();

    // Restore stdin (optional, good practice)
    freopen("/dev/tty", "r", stdin); // Or another appropriate default

    return 0;
}