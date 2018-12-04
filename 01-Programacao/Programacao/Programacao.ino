//  SENSOR DE COR
//Pinos de conexao do modulo
const int s0 = 13;//const int s0 = 8;
const int s1 = 12;//const int s1 = 9;
const int s2 = 50;//const int s2 = 12;
const int s3 = 52;//const int s3 = 11;
const int out = 48;//const int out = 10;

 
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
int frequency = 0; //frequencia das cores

  
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
    //motorDePasso();
    for(;;)
    {
      sensorCor();
      if(qtdPreto > 3)
         break;
    }
}
void sensorCor()
{
  for(int i=0; i<50; i++)
  {
     // Setting RED (R) filtered photodiodes to be read
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
   // Printing the RED (R) value
  Serial.print("R = ");
    frequency = map(frequency,300,1500,255,0);
    red = red + frequency;
  Serial.print(frequency);
  delay(1);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
    frequency = map(frequency,300,1500,255,0);
    green = green + frequency;

  Serial.print(frequency);
  delay(1);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
    frequency = map(frequency,300,1500,255,0);
    blue = blue + frequency;
  Serial.println(frequency);
  delay(1);
  }

  //calcula media de 50 medidas
  red = red/50;
  green = green/50;
  blue = blue/50;

Serial.println(red);
Serial.println(green);
Serial.println(blue);
delay(2000);

  
  if(red>=160&&red<=200&&green>=90&&green<=130&&blue>=150&&blue<=180)
    {
    cor = AMARELO;
    Serial.println("AMARELO");
    }
    else if(red>=100&&red<=160&&green>=30&&green<=55&&blue>=75&&blue<=75)
    {
    cor =  VERMELHO;
        Serial.println("VERMELHO");
    }
    else if(red>=100&&red<=160&&green>=40&&green<=110&&blue>=110&&blue<=130)
    {
    cor = VERDE;
        Serial.println("VERDE");
    }
    else if(red>=165&&red<=205&&green>=100&&green<=150&&blue>=140&&blue<=185)
    {
    cor = LARANJA;
        Serial.println("LARANJA");
    }
    else if(red>=160&&red<=200&&green>=135&&green<=158&&blue>=150&&blue<=190)
    {
    cor = AZUL;
        Serial.println("AZUL");
    }

    else if(red>=115&&red<=185&&green>=80&&green<=130&&blue>=138&&blue<=170)
    {
    cor = MARROM;  
        Serial.println("MARROM");
    }




  //Mostra valores no serial monitor
  delay(1000);
 
}

void servoMotor()
{ 
  switch(cor)
  {
    case MARROM:   //totalmente direita
    
      s.write(140);
      delay(1000);
      break;
    
    case AZUL:////
    
      s.write(110); //um pouco pra direita
      delay(1000);
      break;

    case LARANJA:  //no meio

      s.write(90);
      delay(1000);
      break;

    case AMARELO: //um pouco pra esquerda

      s.write(70);
      delay(1000);
      break;

    case VERDE:  //mais pra esquerda

      s.write(60);
      delay(1000);
      break;

    case VERMELHO:   //esquerda máxima

      s.write(40);
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
