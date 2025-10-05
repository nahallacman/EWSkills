#include <stdio.h>
#include <stdint.h>

uint32_t extract_field(uint32_t reg, uint8_t pos, uint8_t len) {
    // Your code here
    uint32_t retval = 0;
    uint32_t mask = 0;
    // shift register by position count
    retval = (reg >> pos);
    // mask off length we want
    // first make the mask
    for(int i = 0; i < len; i++){
        mask = mask << 1;
        mask |= 1;
    }
    // then apply the mask
    retval &= mask;
    return retval;
}
// Example input:
// reg = 0b1011 0110 0111 0000 0000 0000 0000 0000, pos = 28, len = 4 
// Expected output: 
// 0b1011

// Input
// 0xB6700000 -> 3060793344
// 28
// 4
// Output
// 0xB
int main() {
    uint32_t reg;
    uint8_t pos, len;
    scanf("%u %hhu %hhu", &reg, &pos, &len);
    printf("%u", extract_field(reg, pos, len));
    return 0;
}