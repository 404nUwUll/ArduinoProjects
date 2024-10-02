#include <avr/io.h>

int writeBit(int binario, int pos, int valor){
  int memoria = 1 << pos;
  binario &= ~memoria;
  memoria = valor << pos;
  binario |= memoria;
  return binario;
}

void wait(int i){
  while(i--);
}

int debounce(int pino){
  int c = 0;
  int atual = PINB & pino;
  do{
    int passada = atual;
    wait(100);
    atual = PINB & pino;
    c = (atual == passada) ? c + 1 : 0;
  } while (c < 10);
  return (atual == 0) ? 0 : 1;
}

void startConfig(){
  DDRB = DDRB | 0x20; // Configura PB5(13) do Arduino como Saída, o resto é leitura
  PORTB = PORTB | 0x22; // Configura PB5 como sendo alto, e PB1(9) como sendo alto/ativa resistencia de pull-up
}

int main(){
  startConfig();
  while (1){
    int valor = debounce(0x2);
    PORTB = writeBit(PORTB, 5, valor);
  }
  return 0;
}
