#include <avr/io.h>
#include <util/delay.h>
#include "ADC.h"
#include "dio.h"
#include "LCD.h"
#include "UART.h"
#include "pwm.h"
// #include "Keypad1.h"
#include "I2c.h"
#include "Eeprom.h"


void init();

int main(){
  init();

  // float temp_min = 15.0; // initial temp min limit
  // float temp_max = 30.0; // initial temp max limit
  int duty = 8; // initial duty cycle

  int maxtemp = EEP_Read(0);
  int mintemp = EEP_Read(1);

  char buffer[20];       
  
  while(1){
    int btns = ADC_Read(1); // read ADC value of the buttons pins
    float lm35 = ADC_Read(0); // read ADC value of temp sensor
    float temp_cel = lm35/2.048; // convert temp value to degrees celsius
    char temp_cel_str[5]; // string to store the value of the temp
    itoa(temp_cel, temp_cel_str, 10); // converting temp value from int --> string

    send_string_uart(temp_cel_str); // send temp in celsius

    // display top row info on LCD
    LCD_String_xy(0, 0, "Temp:");
    LCD_String_xy(0, 6, temp_cel_str);
    LCD_String_xy(0, 9, "C");    
    
    // Check which button is pressed and perform certain action
    if(btns < 5){// btn 1 action
      mintemp = mintemp - 1; // decrement min temp limit by 1
      EEP_Write(1, mintemp);
    }
    else if(btns < 520){// btn 2 action
      mintemp = mintemp + 1; // increment min temp limit by 1
      EEP_Write(1, mintemp);
    }
    else if(btns < 690){// btn 3 action
      maxtemp = maxtemp - 1; // decrement max temp limit by 1
      EEP_Write(0, maxtemp);
    }
    else if(btns < 775){// btn 4 action
      maxtemp = maxtemp + 1; // increment max temp limit by 1
      EEP_Write(0, maxtemp);
    }
    else if(btns < 830){// btn 5 action
      DIO_SetPinState('b', 2, 'l');// trigger relay to turn off dc motor
    }
    else if(btns < 865){// btn 6 action
      DIO_SetPinState('b', 2, 'h');// trigger relay to tun on dc motor
    }
    else if(btns < 885){// btn 7 action
      if(duty > 8){
      duty = duty - 2; // rotate the servo motor
      }
    }
    else if(btns < 950){// btn 8 action
      if(duty < 32){
      duty = duty + 2; // rotate the servo motor
      }
    }

    set_dutycycle(duty); // rotate servo motor according to duty cycle

    if(temp_cel >= maxtemp | temp_cel <= mintemp){// when temp not between the limits
      DIO_SetPinState('b', 3, 'h'); // turn warning led on
      DIO_SetPinState('b', 2, 'h');// trigger relay to tun on dc motor
    } else{ // when temp between limits
      DIO_SetPinState('b', 3, 'l'); // turn warning led off
    }
  

    // convert temp limits from int --> string
    char temp_min_str[5];
    itoa(mintemp, temp_min_str, 10);

    char temp_max_str[5];
    itoa(maxtemp, temp_max_str, 10);

    // display temp limits on lower row of LCD
    LCD_String_xy(1, 6, " "); 
    LCD_String_xy(1, 0, "Min:");
    LCD_String_xy(1, 5, temp_min_str);     

    LCD_String_xy(1, 14, " ");             
    LCD_String_xy(1, 8, "Max:");
    LCD_String_xy(1, 13, temp_max_str);    

    _delay_ms(200);
  }

  return 0;
}

void init(){
  //initialize libraries
  init_uart();
  ADC_Init();
  DIO_init();
  LCD_Init();
  init_uart();
  pwm_init();
  I2C_Init();
  // Keypad_Init();
}