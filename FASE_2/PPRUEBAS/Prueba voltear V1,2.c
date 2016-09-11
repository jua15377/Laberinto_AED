/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"    
#include "abdrive.h"
 
#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"

#include<stdio.h>
#include<stdlib.h>


int main() {
  

  int irLeft, irRight; 
  
  low(26);
  low(27); 
  


while (1){
    freqout(11, 1, 65000);                      // Check left & right objects. Codigo tomado de 
    irLeft = input(10);                         //learn.parallax.com/tutorials/robot/activitybot/activitybot/navigate-infrared-flashlights/roaming-infrared-flashlights

    freqout(1, 1, 65000);
    irRight = input(2);
 
  
    if(ping_cm(8)<7 && irLeft == 0 && irRight == 0){  //Gira en U cuando encuentra todos los caminos Bloqueados
      drive_goto(20,20);
      drive_goto(52,-50);   
      }
    if(ping_cm(8)<7 && irLeft == 1 && irRight == 1){  //gira hacia la derecha cuando la izquierda y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(25,-26); 
      }
    if(ping_cm(8)<7 && irLeft == 1 && irRight == 0){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(-25,26); 
      }
    if(ping_cm(8)<7 && irLeft == 0 && irRight == 1){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(25,-26); 
      } 
    if (ping_cm(8)>7){
    drive_rampStep(30,30); 
      
      }
    
    
  } 
  
  
}                                  

  


