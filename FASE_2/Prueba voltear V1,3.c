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

/* Stack has three properties. capacity stands for the maximum number of elements stack can hold.
   Size stands for the current size of the stack and elements is the array of elements */
typedef struct Stack
{
        int capacity;
        int size;
        int *elements;
}Stack;
/* crateStack function takes argument the maximum number of elements the stack can hold, creates
   a stack according to it and returns a pointer to the stack. */
Stack * createStack(int maxElements)
{
        /* Create a Stack */
        Stack *S;
        S = (Stack *)malloc(sizeof(Stack));
        /* Initialise its properties */
        S->elements = (int *)malloc(sizeof(int)*maxElements);
        S->size = 0;
        S->capacity = maxElements;
        /* Return the pointer */
        return S;
}
void pop(Stack *S)
{
        /* If stack size is zero then it is empty. So we cannot pop */
        if(S->size==0)
        {
                printf("Stack is Empty\n");
                return;
        }
        /* Removing an element is equivalent to reducing its size by one */
        else
        {
                S->size--;
        }
        return;
}
int top(Stack *S)
{
        if(S->size==0)
        {
                printf("Stack is Empty\n");
                exit(0);
        }
        /* Return the topmost element */
        return S->elements[S->size-1];
}
void push(Stack *S,int element)
{
        /* If the stack is full, we cannot push an element into it as there is no space for it.*/
        if(S->size == S->capacity)
        {
                printf("Stack is Full\n");
        }
        else
        {
                /* Push an element on the top of it and increase its size by one*/ 
                S->elements[S->size++] = element;
        }
        return;
}
/*--------------------------------------------------------------------------------------------------------------*/
/*Codigo encontrado en internet en fuente https://carreerbuilder.wordpress.com/2015/08/21/data-structuresatcks/*/
/*Codigo para manejo de Stacks*/
/*--------------------------------------------------------------------------------------------------------------*/

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
    else if(ping_cm(8)<7 && irLeft == 1 && irRight == 1){  //gira hacia la derecha cuando la izquierda y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(25,-26); 
      }
    else if(ping_cm(8)<7 && irLeft == 1 && irRight == 0){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(-25,26); 
      }
    else if(ping_cm(8)<7 && irLeft == 0 && irRight == 1){  //gira hacia la izquierda cuando la derecha y adelante estan bloqueados
      drive_goto(20,20);
      drive_goto(25,-26); 
      } 
    else if (ping_cm(8)>7){
    drive_rampStep(30,30); 
      
      }
    
    
  } 
  
  
}