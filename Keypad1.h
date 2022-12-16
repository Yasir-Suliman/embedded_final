#include <avr/io.h>

#define Key_Dir  DDRB 		/* Define keypad data port direction */
#define Key_Port PORTB		/* Define keypad data port */
#define Key_Pin  PINB		  /* Define keypad data port */
#define Col_0 0
#define Col_1 1
#define Col_2 2
#define Row_0 3
#define Row_1 4
#define Row_2 5

/* row 0 - 0
 row 1 - 1
 row 2 - 2
 col 0 - 3
 col 1 - 4
 col 2 - 5
 
 */
void Keypad_Init(void);
void Key_IsPressed(int key);
int Check_Pressed(void);

int Key_IsPressed_check(int key);