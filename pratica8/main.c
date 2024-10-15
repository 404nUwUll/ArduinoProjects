#include <avr/io.h>

void wait(char time, char scale){
  if (scale > 0){
    for (int i = 0; i < time; i++){
      wait(10, scale-1);
    }
  }
}

char writeBit(char target, char pos, char value){
  char memory = 1 << pos;
  target &= ~memory;
  memory = value << pos;
  target |= memory;
  return target;
}

char debounce(){
  char c = 0;
  char thisState = PINB & 0x2;
  char bfState;
  do{
    bfState = thisState;
    wait(5, 6);
    thisState = PINB & 0x2;
    c = (thisState == bfState) ? c+1 : 0;
  }while(c<10);
  return thisState;
}

void config(){
  DDRB = 0x20;
  PORTB = 0x22;
}

int main(){
  config();
  char isPressed = 0;
  char changeState = 0;
  char state = 0;
  while(1){
    isPressed = debounce();
    if (isPressed){
      changeState = 1;
    }else{
      state ^= changeState;
      changeState = 0;
      PORTB = writeBit(PORTB, 5, state);
    }
  }
  return 0;
}
