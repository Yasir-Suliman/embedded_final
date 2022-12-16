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

  float temp_min = 15.0;
  float temp_max = 30.0;
  int duty = 8;

  while(1){
    int btns = ADC_Read(1);
    float lm35 = ADC_Read(0);
    float temp_cel = lm35/2.048;
    char temp_cel_str[5];
    itoa(temp_cel, temp_cel_str, 10);

    LCD_String_xy(0, 0, "Temp:");
    LCD_String_xy(0, 6, temp_cel_str);
    LCD_String_xy(0, 9, "C");    
    
    if(btns < 5){
      temp_min = temp_min - 1;
    }
    else if(btns < 520){
      temp_min = temp_min + 1;
    }
    else if(btns < 690){
      temp_max = temp_max - 1;
    }
    else if(btns < 775){
      temp_max = temp_max + 1;
    }
    else if(btns < 830){
      temp_min = 15.0;
    }
    else if(btns < 865){
      temp_max = 30.0;
    }
    else if(btns < 885){
      if(duty > 8){
      duty = duty - 2;
      }
    }
    else if(btns < 950){
      if(duty < 32){
      duty = duty + 2;
      }
    }

    if(temp_cel >= temp_max | temp_cel <= temp_min){
      DIO_SetPinState('c', 5, 'h');
    } else{
      DIO_SetPinState('c', 5, 'l');
    }
    
    Serial.println(duty);
    set_dutycycle(duty);

    char temp_min_str[5];
    itoa(temp_min, temp_min_str, 10);

    char temp_max_str[5];
    itoa(temp_max, temp_max_str, 10);

    LCD_String_xy(1, 0, "Min:");
    LCD_String_xy(1, 5, temp_min_str);     

    LCD_String_xy(1, 8, "Max:");
    LCD_String_xy(1, 13, temp_max_str);    

    _delay_ms(200);
  }

  return 0;
}

void init(){
  ADC_Init();
  DIO_init();
  LCD_Init();
  init_uart();
  pwm_init();
  // Keypad_Init();  
  Serial.begin(9600);

}