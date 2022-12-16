#include <avr/io.h>
#include "pwm.h"

void pwm_init(){
  // set pin PB1 as output
  DDRB = DDRB |(1 << PB1);

  // set timer mode to fast PWM
  TCCR1A = TCCR1A |(1 << WGM11) |(1 << WGM10);
  TCCR1B = TCCR1B & ~(1 << WGM12);

  // select pre-scaler
  TCCR1B = TCCR1B & ~(1 << CS10);
  TCCR1B = TCCR1B & ~(1 << CS11);
  TCCR1B = TCCR1B |(1 << CS12);
  
  // selecting PB1
  TCCR1A = TCCR1A |(1 << COM1A1);
  TCCR1A = TCCR1A & ~(1 << COM1A0);
}


void set_dutycycle(int dutyCycle){
  int value = (255*dutyCycle/100);
  OCR1A = value;
}