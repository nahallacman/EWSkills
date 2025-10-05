#include <stdio.h>
#include <stdint.h>

void convert_to_big_endian(uint32_t value, uint8_t arr[4]) {
    // Your code here
    uint32_t mask = 0xFF000000;
    uint8_t * ptr = arr;
    // uint32_t temp = 0;
    // Assume the array is always 4 bytes
    for(int i = 24; i >= 0; i = i - 8) {
        // Shift by 24 bits, 16 bits, 8 bits, 0 bits
        *ptr = (mask & value) >> i;
        // temp = (mask & value) >> i;
        // *ptr = temp;

        // Move the pointer to the next index of the array
        ptr++;
        // Shift the mask to the next bit field
        mask = mask >> 8;
    }
}
// Input 0x12345678 -> 305419896
// Output 0x12 0x34 0x56 0x78

int main() {
    uint32_t value;
    uint8_t arr[4];
    scanf("%u", &value);
    convert_to_big_endian(value, arr);
    for (int i = 0; i < 4; i++) {
        printf("%u", arr[i]);
        if(i<3){
            printf(" ");
        }
    }
    return 0;
}