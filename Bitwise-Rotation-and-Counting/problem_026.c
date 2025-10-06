#include <stdio.h>
#include <stdint.h>

uint8_t rotate_left(uint8_t reg, uint8_t n) {
    // Your code here
    uint8_t retval = reg;
    uint8_t carry = 0;
    for(int i = 0; i < n; i++){
        carry = retval & 0x80;
        retval = retval << 1;
        if(carry){
            retval |= 0x01;
        }
    }

    return retval;
}

int main() {
    uint8_t reg, n;
    scanf("%hhu %hhu", &reg, &n);
    printf("%u", rotate_left(reg, n));
    return 0;
}