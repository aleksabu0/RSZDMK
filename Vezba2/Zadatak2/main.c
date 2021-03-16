#include <avr/io.h>
#include <avr/interrupt.h>

unsigned long t0_cnt = 0;
unsigned char disp= 1<<5;
unsigned char duty=0;

ISR(TIMER0_COMPA_vect)
{
  t0_cnt++;
}

void my_delay(){
	if(t0_cnt<duty){
	       disp |= 1 << 5;
	       PORTB = disp;
	      }
	else{
		disp&= ~(1 << 5);
	    PORTB = disp;
	}
	if(t0_cnt>255){
		t0_cnt=0;
		duty++;
	}
	if(duty>=255){
		duty =0;
	}
}

int main()
{
   DDRB |= 1 << 5; //PB5 je izlaz

   TCCR0A = 0x02; //tajmer 0: CTC mod
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
