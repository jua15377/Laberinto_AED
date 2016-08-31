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


void paso(){
  int paso = 0;                              //Se creara una variable que sea el limite maximo que pueda caminar
  while(paso<45){                            //Mientras no se haya pasado del limite (el cual es aproximadamente la distancia)
    paso = paso + 5;                         //Se suma una distancia de 5 pasos
    drive_goto(5,5);                         // y nos movemos 5 pasos junto con el contador
    if(ping_cm(8)<7){                        //Si en dado caso a medio metodo existiera un bloqueo, terminara en ese instante el movimientos
      break;
    }
  } 
}  




int main() {
  

  int irLeft, irRight; 
  
  low(26);
  low(27); 

while (1){
    
    freqout(11, 1, 38000);                      // Check left & right objects. Codigo tomado de 
    irLeft = input(10);                         //learn.parallax.com/tutorials/robot/activitybot/activitybot/navigate-infrared-flashlights/roaming-infrared-flashlights

    freqout(1, 1, 38000);
    irRight = input(2); 
    
    if(ping_cm(8)<15 && irLeft == 0 && irRight == 0){  //Gira en U cuando encuentra todos los caminos Bloqueados
      drive_goto(52,-50);   
      }
    if(ping_cm(8)<15 && irLeft == 0 && irRight == 1){  //gira hacia la derecha cuando la izquierda y adelante estan bloqueados
      drive_goto(25,-26); 
      }
    if(ping_cm(8)<15 && irLeft == 1 && irRight == 0){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(-25,26); 
      }
    if(ping_cm(8)<15 && irLeft == 1 && irRight == 1){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(25,-26); 
      }
    
   paso();   

  } 
  
  
}                                  

  


