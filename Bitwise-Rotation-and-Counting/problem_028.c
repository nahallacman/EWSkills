#include <stdio.h>
#include <stdint.h>

uint16_t rotate_left(uint16_t reg, uint8_t n) {
    // Your code here
    uint16_t retval = reg;
    uint16_t carry = 0;
    for(int i = 0; i < n; i++){
        carry = retval & 0x8000;
        retval = retval << 1;
        if(carry){
            retval |= 0x0001;
        }
    }

    return retval;
}

// Since we are rotating NIBBLES, not bits (the question does not specify)
#define ROTATION_AMOUNT 1
uint8_t is_circular_match(uint16_t reg, uint16_t target) {
    // Your code here
    for(int i = 0; i < (sizeof(reg)*8); i=i+ROTATION_AMOUNT){
        if(reg == target){
            return 1;
        }
        reg = rotate_left(reg, ROTATION_AMOUNT);
    }
    return 0;
}

int main() {
    uint16_t reg, target;
    scanf("%hu %hu", &reg, &target);
    printf("%hhu", is_circular_match(reg, target));
    return 0;
}