#include <stdio.h>
#include <stdint.h>

uint8_t count_set_bits(uint8_t reg) {
    // Your code here
    uint8_t retval = 0;
    for(int i = 0; i < (sizeof(reg) * 8); i++) {
        if(reg & 0x01){
            retval++;
        }
        reg = reg >> 1;
    }
    return retval;
}

int main() {
    uint8_t reg;
    scanf("%hhu", &reg);
    printf("%u", count_set_bits(reg));
    return 0;
}