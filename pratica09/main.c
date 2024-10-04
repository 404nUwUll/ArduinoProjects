#include <avr/io.h>
#include <avr/interrupt.h>

volatile int state = 0;

void INT0_ISR();

void delay(){
    unsigned int i = 65000;
    while(i--);
}

void setup(){
    DDRB = 0x20;
    PORTB = 0x20;
}

void main(){
    setup();
    while (1){

    }
    return 0;
}

void INT0_ISR(){
    state != state;
}
