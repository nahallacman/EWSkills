#include <stdio.h>
#include <stdint.h>

#define ENABLE_MASK 0x01
#define MODE_MASK 0x06
#define SPEED_MASK 0x38
#define RESERVED_MASK 0xC0

#define MODE_SHIFT 0x01
#define SPEED_SHIFT 0x03

// Define macros here
uint16_t build_register(uint8_t enable, uint8_t mode, uint8_t speed) {
    // Use macros to set fields
    uint16_t retval = 0;
    retval |= (enable & ENABLE_MASK);
    retval |= (mode<<MODE_SHIFT) & MODE_MASK;
    retval |= (speed<<SPEED_SHIFT) & SPEED_MASK;

    return retval;
}

int main() {
    uint8_t enable, mode, speed;
    scanf("%hhu %hhu %hhu", &enable, &mode, &speed);

    uint16_t reg = build_register(enable, mode, speed);
    printf("%u", reg);
    return 0;
}