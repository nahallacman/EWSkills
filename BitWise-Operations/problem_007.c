#include <stdio.h>
#include <stdint.h>

uint8_t is_bit_set(uint8_t reg, uint8_t pos) {
    // Your code here
    if(reg & (1<<pos)){
        return 1;
    }
    return 0;
}

int main() {
    uint8_t reg, pos;
    scanf("%hhu %hhu", &reg, &pos);
    printf("%u", is_bit_set(reg, pos));
    return 0;
}