#include <stdio.h>
#include <stdint.h>

uint32_t rotate_right(uint32_t reg, uint8_t n) {
    // Your code here
    uint32_t retval = reg;
    uint8_t mask = 0;
    for(int i=0; i < n; i++){
        mask = retval & 0x01;
        retval = retval >> 1;
        if(mask){
            retval |= 0x80000000;
        }
    }

    return retval;
}

int main() {
    uint32_t reg;
    uint8_t n;
    scanf("%u %hhu", &reg, &n);
    printf("%u", rotate_right(reg, n));
    return 0;
}