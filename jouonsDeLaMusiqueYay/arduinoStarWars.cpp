// NB: ALL NOTES DEFINED WITH STANDARD ENGLISH NAMES
#define C0  16.35
#define Db0 17.32
#define D0  18.35
#define Eb0 19.45
#define E0  20.60
#define F0  21.83
#define Gb0 23.12
#define G0  24.50
#define Ab0 25.96
#define A0  27.50
#define Bb0 29.14
#define B0  30.87
#define C1  32.70
#define Db1 34.65
#define D1  36.71
#define Eb1 38.89
#define E1  41.20
#define F1  43.65
#define Gb1 46.25
#define G1  49.00
#define Ab1 51.91
#define A1  55.00
#define Bb1 58.27
#define B1  61.74
#define C2  65.41
#define Db2 69.30
#define D2  73.42
#define Eb2 77.78
#define E2  82.41
#define F2  87.31
#define Gb2 92.50
#define G2  98.00
#define Ab2 103.83
#define A2  110.00
#define Bb2 116.54
#define B2  123.47
#define C3  130.81
#define Db3 138.59
#define D3  146.83
#define Eb3 155.56
#define E3  164.81
#define F3  174.61
#define Gb3 185.00
#define G3  196.00
#define Ab3 207.65
#define A3  220.00
#define Bb3 233.08
#define B3  246.94
#define C4  261.63
#define Db4 277.18
#define D4  293.66
#define Eb4 311.13
#define E4  329.63
#define F4  349.23
#define Gb4 369.99
#define G4  392.00
#define Ab4 415.30
#define A4  440.00
#define Bb4 466.16
#define B4  493.88
#define C5  523.25
#define Db5 554.37
#define D5  587.33
#define Eb5 622.25
#define E5  659.26
#define F5  698.46
#define Gb5 739.99
#define G5  783.99
#define Ab5 830.61
#define A5  880.00
#define Bb5 932.33
#define B5  987.77
#define C6  1046.50
#define Db6 1108.73
#define D6  1174.66
#define Eb6 1244.51
#define E6  1318.51
#define F6  1396.91
#define Gb6 1479.98
#define G6  1567.98
#define Ab6 1661.22
#define A6  1760.00
#define Bb6 1864.66
#define B6  1975.53
#define C7  2093.00
#define Db7 2217.46
#define D7  2349.32
#define Eb7 2489.02
#define E7  2637.02
#define F7  2793.83
#define Gb7 2959.96
#define G7  3135.96
#define Ab7 3322.44
#define A7  3520.01
#define Bb7 3729.31
#define B7  3951.07
#define C8  4186.01
#define Db8 4434.92
#define D8  4698.64
#define Eb8 4978.03
// DURATION OF THE NOTES 
#define BPM 120    //  you can change this value changing all the others
#define Q 60000/BPM //quarter 1/4
#define H 2*Q //half 2/4
#define E Q/2 //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

#include "commonlib.h"

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