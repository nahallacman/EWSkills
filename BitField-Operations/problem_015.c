#include <stdio.h>
#include <stdint.h>

uint8_t set_range(uint8_t reg, uint8_t start, uint8_t end) {
    // Your code here
    uint8_t retval = 0;
    // Set a bit for every number between start and end
    for(int i = start-1; i < end; i++){
        retval = (retval << 1);
        retval |= 0x01;
    }
    // Shift the set bits over to the correct offset
    retval = (retval<<start);
    // Set bits reguardless of their original settings
    retval = retval | reg;
    
    return retval;
}

int main() {
    uint8_t reg, start, end;
    scanf("%hhu %hhu %hhu", &reg, &start, &end);
    printf("%u", set_range(reg, start, end));
    return 0;
}