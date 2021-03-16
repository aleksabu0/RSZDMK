#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long t0_cnt = 0;
unsigned char disp= 1<<5;
ISR(TIMER0_COMPA_vect)
{
  t0_cnt++;
}

void my_delay(){
	if(t0_cnt<2){
	       disp |= 1 << 5;
	       PORTB = disp;
	      }
	else{
		disp&= ~(1 << 5);
	    PORTB = disp;
	}
	if(t0_cnt>256){
		t0_cnt=0;
	}
}

int main()
{
   DDRB |= 1 << 5; //PB5 je izlaz

   TCCR0A = 0x01; //tajmer 0: CTC mod
   TCCR0B = 0x02; //tajmer 0: fclk = fosc/64
   OCR0A = 19;
   OCR0B =
   TIMSK0 = 0x02;

   sei();
   while (1)
   {
     my_delay(t0_cnt);
   }
   return 0;
}
