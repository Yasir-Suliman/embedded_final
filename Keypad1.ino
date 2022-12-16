#include <avr/io.h>
#include "Keypad1.h"


void Keypad_Init(void){
  Key_Dir |= (1 << Row_0) | (1 << Row_1) | (1 << Row_2);
  Key_Dir &= ~((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
  //Key_Port = 0x0F;
}

int Key_IsPressed_check(){
  Key_Dir |= ((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
  Key_Port |= ((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
  Key_Dir |= (1 << Row_0) | (1 << Row_1) | (1 << Row_2);
  Key_Dir &= ~(1 << Row_0) | (1 << Row_1) | (1 << Row_2);

  if(!(Key_Pin & (1 << Col_0))){
    Key_Port &= ~((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
    Key_Port |= ((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
    Key_Dir |= (1 << Row_0);
    if(Key_Pin & (1 << Col_0)){
      return 1;      
    }
    Key_Dir |= (1 << Row_1);
    if(Key_Pin & (1 << Col_0)){
      return 4;      
    }
    Key_Dir |= (1 << Row_2);
    if(Key_Pin & (1 << Col_0)){
      return 7;      
    }            
    
  }
  else if(!(Key_Pin & (1 << Col_1))){
    Key_Port |= ((1 << Col_0) | (1 << Col_1) | (1 << Col_2));    
    Key_Dir |= (1 << Row_0) | (1 << Row_1) | (1 << Row_2);
    
  }
  else if(!(Key_Pin & (1 << Col_2))){
    Key_Port |= ((1 << Col_0) | (1 << Col_1) | (1 << Col_2));
    Key_Dir |= (1 << Row_0) | (1 << Row_1) | (1 << Row_2);
    
  }
     
}

// void Key_IsPressed(int key){
//   if(key == 1){
//     if(Key_Pin &((1 << Row_0) |(1 << Col_0))){
//       //BTN 1 action
//     }
//   }

//   if(key == 2){
//     if(Key_Pin &((1 << Row_0) |(1 << Col_1))){
//       //BTN 2 action
//     }
//   }

//   if(key == 3){
//     if(Key_Pin &((1 << Row_0) |(1 << Col_2))){
//       //BTN 3 action
//     }
//   }

//   if(key == 4){
//     if(Key_Pin &((1 << Row_1) |(1 << Col_0))){
//       //BTN 4 action
//     }
//   }

//   if(key == 5){
//     if(Key_Pin &((1 << Row_1) |(1 << Col_1))){
//       //BTN 5 action
//     }
//   }

//   if(key == 6){
//     if(Key_Pin &((1 << Row_1) |(1 << Col_2))){
//       //BTN 6 action
//     }
//   }

//   if(key == 7){
//     if(Key_Pin &((1 << Row_2) |(1 << Col_0))){
//       //BTN 7 action
//     }
//   }
  
//   if(key == 8){
//     if(Key_Pin &((1 << Row_2) |(1 << Col_1))){
//       //BTN 8 action
//     }
//   }

//   if(key == 9){
//     if(Key_Pin &((1 << Row_2) |(1 << Col_2))){
//       //BTN 9 action
//     }
//   }    
// }

// int Check_Pressed(void){
//   if(!(Key_Pin &((1 << Row_0) |(1 << Col_0)))){
//       return 1;
//     }
//   if(!(Key_Pin &((1 << Row_0) |(1 << Col_1)))){
//       return 2;
//     }
//   if(!(Key_Pin &((1 << Row_0) |(1 << Col_2)))){
//       return 3;
//     }
//   if(!(Key_Pin &((1 << Row_1) |(1 << Col_0)))){
//       return 4;
//     }
//   if(!(Key_Pin &((1 << Row_1) |(1 << Col_1)))){
//       return 5;
//     }
//   if(!(Key_Pin &((1 << Row_1) |(1 << Col_2)))){
//       return 6;
//     }
//   if(!(Key_Pin &((1 << Row_2) |(1 << Col_0)))){
//       return 7;
//     }
//   if(!(Key_Pin &((1 << Row_2) |(1 << Col_1)))){
//       return 8;
//     }
//   if(!(Key_Pin &((1 << Row_2) |(1 << Col_2)))){
//       return 9;
//     }
// }