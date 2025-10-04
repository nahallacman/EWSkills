#include <stdio.h>
#include <stdint.h>

// Define bitwise macros here

uint8_t modify_register(uint8_t reg) {
    // Apply operations in order
    // Set bits 2 and 7
    reg |= 0x84;
    // Clear bit 3
    reg &= ~(0x08);
    // Toggle bit 5
    reg ^= 0x20;
    return reg;
}

int main() {
    uint8_t reg;
    scanf("%hhu", &reg);
    printf("%u", modify_register(reg));
    return 0;
}