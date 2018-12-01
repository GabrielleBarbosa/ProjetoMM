//  SENSOR DE COR
//Pinos de conexao do modulo
const int s0 = 12;//const int s0 = 8;
const int s1 = 13;//const int s1 = 9;
const int s2 = 14;//const int s2 = 12;
const int s3 = 15;//const int s3 = 11;
const int out = 16;//const int out = 10;

 
//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
int qtdPreto = 0;
int qtdAzul = 0;
int qtdMarrom = 0;
int qtdAmarelo = 0;
int qtdVerde = 0;
int qtdVermelho = 0;
int qtdLaranja = 0;


//MOTOR DE PASSO
#include <Stepper.h> 
 
const int stepsPerRevolution = 500; 
  
Stepper myStepper(stepsPerRevolution, 8,10,9,11); 


// SERVO MOTOR 
#include <Servo.h>
 
#define SERVO 6 // Porta Digital 6 PWM

enum Color { VERMELHO, MARROM, AZUL, AMARELO,  LARANJA, VERDE , PRETO};
 
Servo s; // Variável Servo
int pos; // Posição Servo

Color cor = MARROM; //com sensor

  
void setup() 
{ 
 //MOTOR DE PASSO
 myStepper.setSpeed(60);
 
 //  SENSOR DE COR
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  // SERVO MOTOR 
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
} 
  
void loop() 
{ 
    motorDePasso();
    for(;;)
    {
      sensorCor();
      servoMotor();
      motorDePasso();

      if(qtdPreto > 3)
         break;
    }
}

void sensorCor()
{
  for(int i=0; i<50; i++)
  {
    // Rotina que le o valor das cores
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    //count OUT, pRed, RED
    red += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s3, HIGH);
    //count OUT, pBLUE, BLUE
    blue += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
    digitalWrite(s2, HIGH);
    //count OUT, pGreen, GREEN
    green += pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  }

  //calcula media de 50 medidas
  red = red/50;
  green = green/50;
  blue = blue/50;

  //Mostra valores no serial monitor
  Serial.print("Vermelho :");
  Serial.print(red, DEC);
  Serial.print(" Verde : ");
  Serial.print(green, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue, DEC);
  Serial.println();
  delay(1000);
 
}

void servoMotor()
{
  switch(cor)
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
}

void motorDePasso()
{
   //Gira o motor no sentido horario a 90 graus

 myStepper.step(-512); 
 
 delay(200); 
}
