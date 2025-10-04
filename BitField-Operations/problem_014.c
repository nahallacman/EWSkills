#include <stdio.h>

#define UPPER_NIBBLE_MASK 0xF0
#define LOWER_NIBBLE_MASK 0x0F

unsigned char extractNibble(unsigned char reg, int pos) {
    unsigned char retval = 0;
    // Write your code here
    // If position, mask off upper nibble and shift to lower nibble
    if(pos){
        retval = reg & UPPER_NIBBLE_MASK;
        retval = (retval >> 4);
    } else {
        // Just mask off lower nibble
        retval = reg & LOWER_NIBBLE_MASK;
    }
    return retval;
}

int main() {
    unsigned char reg;
    int pos;
    scanf("%hhu %d", &reg, &pos);
    printf("%d", extractNibble(reg, pos));
    return 0;
}