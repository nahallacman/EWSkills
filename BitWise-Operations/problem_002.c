#include <stdio.h>

int toggleFifthBit(int n) {
    // Write your code here
    return (n ^ 0x20);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d", toggleFifthBit(n));
    return 0;
}