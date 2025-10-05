#include <stdio.h>
#include <stdint.h>

#define BUAD_RATE_FIELD_MASK 0x0F00

uint32_t set_baud_rate(uint32_t reg, uint8_t baud) {
    // Your code here
    uint32_t retval = 0;
    // write baud value into temp
    retval |= (baud << 8) & BUAD_RATE_FIELD_MASK;
    // write original value into temp
    retval |= (~BUAD_RATE_FIELD_MASK & reg);

    return retval;
}

int main() {
    uint32_t reg;
    uint8_t baud;
    scanf("%u %hhu", &reg, &baud);
    printf("%u", set_baud_rate(reg, baud));
    return 0;
}