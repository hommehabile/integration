#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "eddymalou.h"
#include <avr/interrupt.h>
#define SAMPLE_RATE 8000;

volatile uint32_t sample = 44;
uint8_t sample_count;

void pwm_init();

int main(void)
{
   pwm_init();
   while(1);//do nothing
}

/* Version a 3.91kHz avec CTC */
ISR(TIMER1_OVF_vect)
{ 
    sample_count--;
    if (sample_count == 0)
    {
        sample_count = 4;          
        OCR1A = pgm_read_byte(&pcm_samples[sample++]);
        if(sample>pcm_len)
            sample=0;
    }
}
//initialise the PWM
void pwm_init() {
    // use OC1A pin as output 
    DDRD = _BV(PD5);
    PORTD = 0x00;

    //clear OC1A on compare match
    //set OC1A at BOTTOM, non-inverting mode
    //Fast PWM, 8bit
    TCCR1A |= _BV(COM1A1) | _BV(WGM10);
   
    //Fast PWM, 8bit
    //Prescaler: clk/1 = 8MHz
    //PWM frequency = 8MHz / (255 + 1) = 31.25kHz
    TCCR1B |= _BV(WGM12) | _BV(CS10);
   
    //set initial duty cycle to zero
    OCR1A = 0;
   
    //Setup Timer1
    //TCCR1 |= (1 << CS00); //nope
    TCNT1 = 0;
    TIMSK1 |= (1 << TOIE1);
    sample_count = 4;
    sei(); //Enable interrupts
}


/* Version a 31.25kHz 

ISR(TIMER1_OVF_vect)
{ 
    sample_count--;
    if (sample_count == 0)
    {
        sample_count = 32;          
        OCR1A = pgm_read_byte(&pcm_samples[sample++]);
        if(sample>pcm_len)
            sample=0;
    }
}
//initialise the PWM
void pwm_init() {
    // use OC1A pin as output 
    DDRD = _BV(PD5);
    PORTD = 0x00;

    //clear OC1A on compare match
    //set OC1A at BOTTOM, non-inverting mode
    //Fast PWM, 8bit
    TCCR1A |= _BV(COM1A1) | _BV(WGM10);
   
    //Fast PWM, 8bit
    //Prescaler: clk/1 = 8MHz
    //PWM frequency = 8MHz / (255 + 1) = 31.25kHz
    TCCR1B |= _BV(WGM12) | _BV(CS10);
   
    //set initial duty cycle to zero
    OCR1A = 0;
   
    //Setup Timer1
    //TCCR1 |= (1 << CS00); //nope
    TCNT1 = 0;
    TIMSK1 |= (1 << TOIE1);
    sample_count = 4;
    sei(); //Enable interrupts
}

*/




