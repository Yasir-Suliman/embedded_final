#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "dio.h"
#include "LCD.h"
#include "UART.h"
#include "pwm.h"
// #include "Keypad1.h"

void init();

int main(){
  init();

  float temp_min = 20.0;
  float temp_max = 30.0;

  while(1){
    LCD_String_xy(0, 0, "Temp:");
    float lm35 = ADC_Read(0);
    float temp_cel = lm35/2.048;
    char temp_cel_str[5];
    itoa(temp_cel, temp_cel_str, 10);

    LCD_String_xy(0, 6, temp_cel_str);
    LCD_String_xy(0, 9, "C");

    int btn = Key_IsPressed_check();
    Serial.print("Btn:");
    Serial.println(btn);
    
    if(temp_cel >= temp_max | temp_cel <= temp_min){
      DIO_SetPinState('c', 5, 'h');
    } else{
      DIO_SetPinState('c', 5, 'l');
    }

    _delay_ms(200);
  }

  return 0;
}

void init(){
  ADC_Init();
  DIO_init();
  LCD_Init();
  init_uart();
  // pwm_init();
  // Keypad_Init();  
  Serial.begin(9600);

}