#include <stdio.h>
#include <stdint.h>

// bits 10 to 14
// 0b0111_1100_0000_0000
// 0x7C00
#define REGISTER_FIELD_MASK 0x7C00
#define REGISTER_SHIFT_COUNT 10

uint32_t update_register(uint32_t reg) {
    // Your logic here
    uint32_t temp = 0;
    temp = (reg & REGISTER_FIELD_MASK) >> REGISTER_SHIFT_COUNT;

    // If temp == 31, then don't increment.
    // 31 wil fill all 6 bits of the field so no worries about overflow
    if(temp < 31) {
        temp++;
    }

    temp = temp << REGISTER_SHIFT_COUNT;
    // preserve previous values in the register
    temp |= reg & ~REGISTER_FIELD_MASK;

    return temp;
}

int main() {
    uint32_t reg;
    scanf("%u", &reg);
    uint32_t updated = update_register(reg);
    printf("%u", updated);
    return 0;
}