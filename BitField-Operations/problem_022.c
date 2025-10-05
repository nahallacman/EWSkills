#include <stdio.h>
#include <stdint.h>

#define MODE_MASK 0x07
#define SPEED_MASK 0xF8
// #define RESERVED_MASK 0x0300
#define STATUS_MASK 0xFC00
#define MODE_SHIFT 0
#define SPEED_SHIFT 3
#define STATUS_SHIFT 10

uint16_t pack_register(uint8_t mode, uint8_t speed, uint8_t status) {
    // Your logic here
    uint16_t retval = 0;
    retval |= (status   << STATUS_SHIFT ) & STATUS_MASK ;
    retval |= (speed    << SPEED_SHIFT  ) & SPEED_MASK  ;
    retval |= (mode     << MODE_SHIFT   ) & MODE_MASK   ;
    return retval;
}

int main() {
    uint8_t mode, speed, status;
    scanf("%hhu %hhu %hhu", &mode, &speed, &status);

    uint16_t reg = pack_register(mode, speed, status);
    printf("%u", reg);
    return 0;
}