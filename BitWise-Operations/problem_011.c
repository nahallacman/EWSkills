#include <stdio.h>
#include <stdint.h>

#define POWER_ON 0x01
#define ERROR 0x02
#define TX_READY 0x04
#define RX_READY 0x08
#define OVERHEAT 0x10
#define UNDERVOLTAGE 0x20
#define TIMEOUT 0x40
#define RESERVED 0x80

void decode_status(uint8_t status_reg) {
    // Your logic here
    if(status_reg & POWER_ON){
        printf("Power On");
    }
    if(status_reg & ERROR){
        printf("Error");
    }
    if(status_reg & TX_READY){
        printf("Tx Ready");
    }
    if(status_reg & RX_READY){
        printf("Rx Ready");
    }
    if(status_reg & OVERHEAT){
        printf("Overheat");
    }
    if(status_reg & UNDERVOLTAGE){
        printf("Undervoltage");
    }
    if(status_reg & TIMEOUT){
        printf("Timeout");
    }
    if(status_reg & RESERVED){
        printf("Reserved");
    }
}

int main() {
    uint8_t reg;
    scanf("%hhu", &reg);
    decode_status(reg);
    return 0;
}