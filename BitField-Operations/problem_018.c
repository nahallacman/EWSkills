#include <stdio.h>
#include <stdint.h>

uint32_t replace_field(uint32_t reg, uint32_t val, uint8_t pos, uint8_t len) {
    // Your code here
    uint32_t retval = reg;
    uint32_t shifted_val = 0;
    uint32_t mask = 0;
    // first make the mask
    for(int i = 0; i < len; i++){
        mask = mask << 1;
        mask |= 1;
    }

    // Use it to mask off the new written value so we don't carry extra bits into the final result
    shifted_val = val & mask;
    // Now move the value over to the position we want it in
    shifted_val = val << pos;

    // Shift it into position
    mask = mask << pos;
    // And invert it since we want to turn off bits
    mask = ~mask;
    // Finally apply mask
    retval &= mask;

    // Then apply the new value at that position
    retval |= shifted_val;

    return retval;
}

int main() {
    uint32_t reg, val;
    uint8_t pos, len;
    scanf("%u %u %hhu %hhu", &reg, &val, &pos, &len);
    printf("%u", replace_field(reg, val, pos, len));
    return 0;
}