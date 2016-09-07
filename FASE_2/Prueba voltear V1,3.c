/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simpletools header
#include "abdrive.h"                          // Include abdrive header
#include "ping.h"

#include<stdio.h>
#include<stdlib.h>

int L = 0;
int R = 0; 
int frente = 0;
int cont = 0; 
int irLeft, irRight; 




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

/*Codigo para movimiento del robot*/
void izquierda(){
  drive_goto(-25,26);     
}
void derecha(){
  drive_goto(26,-25); 
}

void paso(){
  int paso = 0;
  while(paso<40){
    paso = paso + 5;
    drive_goto(5,5);
    cont=cont+5;
    if(ping_cm(8)<7){
      break;
    }
  } 
}  

/*-----------------------------------------------------------------------------*/
/*Funcion que revisa los lados y frente del robot para tomar datos del entorno*/
/*-----------------------------------------------------------------------------*/
void checking(){
  low(26);
  low(27);
  
  
  freqout(11, 1, 68000);                      // Check left & right objects. Codigo tomado de 
  irLeft = input(10);                         //learn.parallax.com/tutorials/robot/activitybot/activitybot/navigate-infrared-flashlights/roaming-infrared-flashlights

  freqout(1, 1, 68000);
  irRight = input(2);
  
  
  if(irLeft == 0){
    L = 0;
    }
  else{
    L = 1;
    }
    
    
  if(irRight == 0){
    R = 0; 
    }
  else {
    R = 1;
    }
    
    
  if(ping_cm(8)>15){
    frente = 1;
    }
  else{
    frente = 0;
    }
  
  }
/*------------------------------------------------------------------------------------------*/  
/*Funcion que hace los push, dependiendo de lo que encuentre en el camino*/
/*-------------------------------------------------------------------------------------------*/
void result(Stack *stackR,Stack *stackL,Stack *stackRoad){
  int resultado = 0; 
  resultado = L + R + frente; 
  
  /*Si existe una bifurcacion*/
  if(resultado > 1){
    push(stackL, L);
    if (frente == 0){
      push(stackRoad, cont); 
      cont = 0; 
      push(stackRoad, cont); 
      push(stackRoad, -2);
      
      push(stackR, 0);
      
      }
    else{
      push(stackRoad, cont); 
      cont = 0; 
      push(stackRoad, cont); 
      
      push(stackR, R);
      }
    }
    if(frente == 0 && resultado == 1){
      if(L == 1){
        push(stackRoad, cont); 
        push(stackRoad,-1); 
        cont = 0; 
        }
      if(R == 1){
        push(stackRoad,cont);
        push(stackRoad,-2);
        cont = 0;
        }
      }
    if(resultado == 0){
      push(stackRoad,cont);
      cont = 0;
      backtracking(stackR, stackL, stackRoad);
      }
  }

/*----------------------------------------------------------------------------------------------*/
/*Funcion para realizar el backtracing e ir quitando del stack los lugares por donde ya paso*/
/*----------------------------------------------------------------------------------------------*/

void backtracking(Stack *stackR, Stack *stackL, Stack *stackRoad){
  int valor = 0; 
  while(top(stackRoad)!= 0 ){
    if(top(stackRoad)>0){
      valor = top(stackRoad);
      pop(stackRoad);
      valor = valor*(-1);
      drive_goto(valor,valor);
      }
    if(top(stackRoad)==-1){
      pop(stackRoad);
      derecha();
      }
    if(top(stackRoad)==-2){
      pop(stackRoad);
      izquierda();
      }
    }
  checkStacks(stackR,stackL,stackRoad);
  
  
  }
/*------------------------------------------------------------------------------------------*/
/*Funcion para revisar el ultimo dato de los Stacks y en base a eso, realizar una accion*/
/*------------------------------------------------------------------------------------------*/  
void checkStacks(Stack *stackR, Stack *stackL, Stack *stackRoad){
  if (top(stackR)==1 &&top(stackL==0)){
    pop(stackRoad);
    derecha();
    push(stackRoad,-2);
    paso(); /*PASO()*/
    }
  if(top(stackR)==0&&top(stackL)==1){
    pop(stackRoad);
    izquierda();
    push(stackRoad, -1);
    paso();
    
    }
  if(top(stackR)==1&&top(stackL)==1){
    pop(stackR);
    push(stackR,0);
    derecha();
    push(stackRoad,-2);
    paso(); /*PASO()*/
    }
  }

int main() {
  

  int irLeft, irRight; 
  
  low(26);
  low(27); 

  Stack *stackR = createStack(100);
  Stack *stackL = createStack(100);
  Stack *stackRoad = createStack(100);

while (1){
  
  
    freqout(11, 1, 68000);                      // Check left & right objects. Codigo tomado de 
    irLeft = input(10);                         //learn.parallax.com/tutorials/robot/activitybot/activitybot/navigate-infrared-flashlights/roaming-infrared-flashlights

    freqout(1, 1, 68000);
    irRight = input(2);
    
    checking();
    result(stackR, stackL, stackRoad);
    
    if(frente ==1){
      paso();
      }
    else if(R == 1){
      derecha();
      paso();
      }
    else if(L==1){
      izquierda();
      paso();
      }
 
  /*
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
 */   
    
  } 
  
  
}