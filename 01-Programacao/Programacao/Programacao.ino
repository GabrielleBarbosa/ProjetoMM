//  SENSOR DE COR
//Pinos de conexao do modulo
const int s0 = 13;//const int s0 = 8;
const int s1 = 12;//const int s1 = 9;
const int s2 = 50;//const int s2 = 12;
const int s3 = 52;//const int s3 = 11;
const int out = 48;//const int out = 10;

 
//Variaveis cores retornadas
int red = 0;
int green = 0;
int blue = 0;

//quantidades de cada M&M
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

enum Color { VERMELHO, MARROM, AZUL, AMARELO,  LARANJA, VERDE , PRETO}; //cores possiveis (PRETO é quando não identifica nenhuma)
 
Servo s; // Variável Servo

Color cor = MARROM; //com sensor
int frequency = 0; //frequencia das cores

  
void setup() 
{ 
 //MOTOR DE PASSO
 myStepper.setSpeed(60);
 
 //SENSOR DE COR
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
  s.write(90); // Inicia motor posição zero
} 
  
void loop() 
{  
   //motorDePasso();
    for(;;)
    {
       {
        sensorCor();
        //servoMotor();
       // motorDePasso();
       }
    }
}

//para ler cor com sensor
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

    if(red>205&&red<=217&&green>=170&&green<=180&&blue>=209&&blue<=220)
    {
        cor = LARANJA;  
        Serial.println("LARANJA");
    } 
    else if(red>=147&&red<=154&&green>=110&&green<=120&&blue>=157&&blue<=164)
    {
        cor = MARROM;
        Serial.println("MARROM");
    }
    else if(red>=214&&red<=221 &&green>=186&&green<=195 &&blue>=212&&blue<=220)
    {
        cor = AMARELO;
        Serial.println("AMARELO");
    }
    else if(red>=215&&red<=225&&green>=186 &&green<=195&&blue>=218&&blue<=225)
    {
        cor = VERDE;
        Serial.println("VERDE");
    }
    else if(red>=196&&red<=205&&green>=176&&green<=186&&blue>=218&&blue<=225)
    {
        cor =  AZUL;
        Serial.println("AZUL");
    }
    else if(red>=148&&red<=155&&green>=100&&green<=113&&blue>=152&&blue<=162)
    {
        cor = VERMELHO;
        Serial.println("VERMELHO");
    }
    
    
    

  //Mostra valores no serial monitor
  delay(1000);
 
}

void servoMotor()
{ 
  switch(cor)
  {
    case MARROM:   //totalmente direita
    
      s.write(30);
      delay(1000);
      break;
    
    case AZUL:////
    
      s.write(60); //um pouco pra direita
      delay(1000);
      break;

    case LARANJA:  //no meio

      s.write(80);
      delay(1000);
      break;

    case AMARELO: //um pouco pra esquerda

      s.write(100);
      delay(1000);
      break;

    case VERDE:  //mais pra esquerda

      s.write(120);
      delay(1000);
      break;

    case VERMELHO:   //esquerda máxima

      s.write(140);
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
