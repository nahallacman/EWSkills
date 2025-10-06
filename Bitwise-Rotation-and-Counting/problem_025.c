#include <stdio.h>

int countSetBits(unsigned int n) {
    // Write your code here
    int retval = 0;
    for(int i = 0; i < ( sizeof(n) * 8 ); i++){
        if(n & 0x01){
            retval++;
        }
        n = n >> 1;
    }
    return retval;
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", countSetBits(n));
    return 0;
}