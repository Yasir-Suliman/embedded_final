#include <avr/io.h>
#include "pwm.h"

void pwm_init(){
  // set pin PD6 as output
  DDRD = DDRD |(1 << 6);

  // set timer mode to fast PWM
  TCCR0A = TCCR0A |(1 << WGM01) |(1 << WGM00);
  TCCR0B = TCCR0B & ~(1 << WGM02);

  // select pre-scaler (no precaler)
  TCCR0B = TCCR0B |(1 << CS00);
  TCCR0B = TCCR0B & ~(1 << CS01);
  TCCR0B = TCCR0B & ~(1 << CS02);
  
  // selecting PD6
  TCCR0A = TCCR0A |(1 << COM0A1);
  TCCR0A = TCCR0A & ~(1 << COM0A0);
}


void set_dutycycle(int dutyCycle){
  int value = (255*dutyCycle/100);
  OCR0A = value;
}