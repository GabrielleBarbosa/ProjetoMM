#include <Stepper.h> 
 
const int stepsPerRevolution = 500; 
  
//Inicializa a biblioteca utilizando as portas de 8 a 11 para 
//ligacao ao motor 
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 
  
void setup() 
{ 
 //Determina a velocidade inicial do motor 
 myStepper.setSpeed(60);
} 
  
void loop() 
{ 
 //Gira o motor no sentido horario a 90 graus
 
 myStepper.step(-512); 
 delay(200);
 
  
 
 delay(200); 
}
