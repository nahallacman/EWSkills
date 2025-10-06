#include <stdio.h>
#include <stdint.h>

#define REGISTER_MASK 0x01F0
#define REGISTER_SHIFT_COUNT 4

uint8_t extract_field(uint16_t reg) {
    // Your logic here
    uint16_t temp = 0;
    temp = (REGISTER_MASK & reg) >> REGISTER_SHIFT_COUNT;
    // Since desired bits are all in the lower byte and we masked off everything else, we should be fine.
    return (uint8_t)temp;
}

int main() {
    uint16_t reg;
    scanf("%hx", &reg);
    printf("%u", extract_field(reg));
    return 0;
}