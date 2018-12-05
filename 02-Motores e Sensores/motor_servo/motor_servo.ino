#include <Servo.h>
 
#define SERVO 6 // Porta Digital 6 PWM[

enum Color { VERMELHO, MARROM, AZUL, AMARELO,  LARANJA, VERDE };
 
Servo s; // Variável Servo
int pos; // Posição Servo

Color cor = MARROM; //com sensor
 
void setup ()
{
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
}
 //170 -> marrom
 //140 -> azul
 //110 -> laranja
 //80 -> amarelo
 //50 -> vermelho
 //20 -> verde
void loop()
{
  /*switch(cor)
  {
    case MARROM:
    
      s.write(170);
      delay(1000);
      break;
    
    case AZUL:
    
      s.write(140);
      delay(1000);
      break;

    case LARANJA:

      s.write(110);
      delay(1000);
      break;

    case AMARELO:

      s.write(80);
      delay(1000);
      break;

    case VERMELHO:

      s.write(50);
      delay(1000);
      break;

    case VERDE:

      s.write(20);
      delay(1000);
      break;
  }
  */
  s.write(90);
}
