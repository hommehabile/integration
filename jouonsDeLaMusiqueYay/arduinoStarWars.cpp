#include "arduinoStarWars.h"

void tone(uint16_t frequency, uint16_t duration) {
	//ajustement du PWM avec un prescaling de 8
    TCNT1 = 0;
    uint16_t top = round(500000 / frequency);
	OCR1A = top;
    
    //activation du son
    TCCR1B |= _BV(CS11);
    
    //attente
    /*
    uint32_t duree_ms = 2000 * duration; //duree en ms * 8000000 / (4 * 1000)
    if(duree_ms < 17000)
        PORTA = 0x02;
    uint16_t reste = duree_ms % 65536;
    for(uint8_t i=0; i<(duree_ms-reste)/65535; i++) {
        _delay_loop_2(65535);
    }
    _delay_loop_2(reste);
    */
    for(uint16_t i = 0; i < duration; i++)
        _delay_loop_2(2000);

	//arret du son
    TCCR1B &= ~(_BV(CS12) | _BV(CS11) | _BV(CS10));
	_delay_ms(1);
}

// the loop routine runs over and over again forever:
void loop() {
  //tone(pin, note, duration)
    tone(A3,Q); 
    //_delay_ms(1+Q); //delay duration should always be 1 ms more than the note in order to separate them.
    tone(A3,Q);
    //_delay_ms(1+Q);
    tone(A3,Q);
    //_delay_ms(1+Q);
    tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    
    tone(A3,Q);
    //_delay_ms(1+Q);
    tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    tone(A3,H);
    //_delay_ms(1+H);
    
    tone(E4,Q); 
    //_delay_ms(1+Q); 
    tone(E4,Q);
    //_delay_ms(1+Q);
    tone(E4,Q);
    //_delay_ms(1+Q);
    tone(F4,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    
    tone(Ab3,Q);
    //_delay_ms(1+Q);
    tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    tone(A3,H);
    //_delay_ms(1+H);
    
    tone(A4,Q);
    //_delay_ms(1+Q);
    tone(A3,E+S);
    //_delay_ms(1+E+S);
    tone(A3,S);
    //_delay_ms(1+S);
    tone(A4,Q);
    //_delay_ms(1+Q);
    tone(Ab4,E+S);
    //_delay_ms(1+E+S);
    tone(G4,S);
    //_delay_ms(1+S);
    
    tone(Gb4,S);
    //_delay_ms(1+S);
    tone(E4,S);
    //_delay_ms(1+S);
    tone(F4,E);
    //_delay_ms(1+E);
    //_delay_ms(1+E);//PAUSE
    tone(Bb3,E);
    //_delay_ms(1+E);
    tone(Eb4,Q);
    //_delay_ms(1+Q);
    tone(D4,E+S);
    //_delay_ms(1+E+S);
    tone(Db4,S);
    //_delay_ms(1+S);
    
    tone(C4,S);
    //_delay_ms(1+S);
    tone(B3,S);
    //_delay_ms(1+S);
    tone(C4,E);
    //_delay_ms(1+E);
    //_delay_ms(1+E);//PAUSE QUASI FINE RIGA
    tone(F3,E);
    //_delay_ms(1+E);
    tone(Ab3,Q);
    //_delay_ms(1+Q);
    tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(A3,S);
    //_delay_ms(1+S);
    
    tone(C4,Q);
    //_delay_ms(1+Q);
     tone(A3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    tone(E4,H);
    //_delay_ms(1+H);
    
     tone(A4,Q);
    //_delay_ms(1+Q);
    tone(A3,E+S);
    //_delay_ms(1+E+S);
    tone(A3,S);
    //_delay_ms(1+S);
    tone(A4,Q);
    //_delay_ms(1+Q);
    tone(Ab4,E+S);
    //_delay_ms(1+E+S);
    tone(G4,S);
    //_delay_ms(1+S);
    
    tone(Gb4,S);
    //_delay_ms(1+S);
    tone(E4,S);
    //_delay_ms(1+S);
    tone(F4,E);
    //_delay_ms(1+E);
    //_delay_ms(1+E);//PAUSE
    tone(Bb3,E);
    //_delay_ms(1+E);
    tone(Eb4,Q);
    //_delay_ms(1+Q);
    tone(D4,E+S);
    //_delay_ms(1+E+S);
    tone(Db4,S);
    //_delay_ms(1+S);
    
    tone(C4,S);
    //_delay_ms(1+S);
    tone(B3,S);
    //_delay_ms(1+S);
    tone(C4,E);
    //_delay_ms(1+E);
    //_delay_ms(1+E);//PAUSE QUASI FINE RIGA
    tone(F3,E);
    //_delay_ms(1+E);
    tone(Ab3,Q);
    //_delay_ms(1+Q);
    tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    
    tone(A3,Q);
    //_delay_ms(1+Q);
     tone(F3,E+S);
    //_delay_ms(1+E+S);
    tone(C4,S);
    //_delay_ms(1+S);
    tone(A3,H);
    //_delay_ms(1+H);
    
    //_delay_ms(2*H);
}