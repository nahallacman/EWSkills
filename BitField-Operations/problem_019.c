#include <stdio.h>
#include <stdint.h>

uint32_t extract_even_bits(uint32_t reg) {
    uint32_t retval = 0;
    uint32_t temp = reg;
    uint32_t mask = 0x01;
    // sizeof returns the number of bytes, so to get the total number of bits multiply the bytes by 8
    uint32_t SIZE_OF_REGISTER = (sizeof(reg)*8);

    // For all even values (0, 2, 4, ...) to half of the size of the register,
    for(int i = 0; i < (SIZE_OF_REGISTER / 2); i++){
        // mask off the lowest bit and save it
        retval |= (temp & mask);
        // then shift the value down so the next time we mask it's an even value
        // All bits shifted off the low end of the register are lost and that's intended, we don't need them anymore
        temp = temp >> 1;
        // Shift the mask up one bit so we can get the next highest bit next time we mask
        mask = mask << 1;
    }
    return retval;
}
// Input 0x55 -> 85
// Output 0x0F

int main() {
    uint32_t reg;
    scanf("%u", &reg);
    printf("%u", extract_even_bits(reg));
    return 0;
}