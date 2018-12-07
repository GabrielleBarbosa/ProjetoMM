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

//BLUETOOTH
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10,11); //TX - RX
 
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
  
void loop() //apenas chama os métodos infinitamente
{  
    for(;;)
    {
       {
        motorDePasso();
        sensorCor();
        servoMotor();
        motorDePasso();
       }
    }
}

//para ler cor com sensor
void sensorCor()
{
int verd = 0;
int verm = 0;
int lar = 0;
int mar = 0;
int amar = 0;
int azu = 0;
 while(azu<4 && amar<4 && verm<4 && verd<4 && lar<4 && mar<4) //verifica mais de uma vez(4), por conta instabilidade do sensor
 {
    valoresCor(); //lê as cores e pega os sinais do sensor
    if(red>174&&red<=185&&green>=126&&green<=135&&blue>=175&&blue<=182) //valores para a cor laranja
    {
        cor = LARANJA;  
        lar++;
    }
    else if(red>=162&&red<=170&&green>=135 &&green<=145&&blue>=173&&blue<=182) //valores para a cor verde
    {
        cor = VERDE;
        verd++;
    }
    else if(red>=163&&red<=170&&green>=121&&green<=129&&blue>=170&&blue<=180) //valores para a cor vermelho
    {
        cor = VERMELHO;
        verm++;
    }
    else if(red>=158&&red<=167&&green>=135&&green<=145&&blue>=188&&blue<=198) //valores para a cor azul
    {
        cor =  AZUL;
        azu++;
    }
    
    else if(red>=158&&red<=166&&green>=120&&green<=130&&blue>=172&&blue<=181) //valores para a cor marrom
    {
        cor = MARROM;
        mar++;
    }
    else if(red>=180&&red<=193 &&green>=150&&green<=159 &&blue>=180&&blue<=190) //valores para a cor amarelo
    {
        cor = AMARELO;
        amar++;
    }
    delay(200);
 }

 if(amar>=4)
 {
    cor = AMARELO;
    qtdAmarelo++;
    Serial.println("AMARELO");
    bluetooth.print("Amarelo"); //manda o nome da cor pelo bluetooth
    bluetooth.print("|");  //divisor usado no app para facilitar a leitura
 }
 else if(mar>=4)
 {
    cor = MARROM;  
    qtdMarrom++;
    Serial.println("MARROM");
    bluetooth.print("Marrom");
    bluetooth.print("|");
 }
 else if(azu>=4)
 {
    cor = AZUL; 
    qtdAzul++; 
    Serial.println("AZUL");
    bluetooth.print("Azul");
    bluetooth.print("|");
 }
 else if(verm>=4)
 {
    cor = VERMELHO;  
    qtdVermelho++;
    Serial.println("VERMELHO");
    bluetooth.print("Vermelho");
    bluetooth.print("|");
 }
 else if(verd>=4)
 {
    cor = VERDE;  
    qtdVerde++;
    Serial.println("VERDE");
    bluetooth.print("Verde");
    bluetooth.print("|");
 }
 else if(lar>=4)
 {
    cor = LARANJA;
    qtdLaranja++;  
    Serial.println("LARANJA");
    bluetooth.print("Laranja");
    bluetooth.print("|");
 }

  //Mostra valores no serial monitor
  delay(1000);
 }


void valoresCor()
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
}


void servoMotor()
{ 
  switch(cor)
  {
    case MARROM:   //totalmente direita(30º)
    
      s.write(30);
      delay(1000);
      break;
    
    case AZUL:////
    
      s.write(60); //um pouco pra direita(60º)
      delay(1000);
      break;

    case LARANJA:  //no meio (80º)

      s.write(80);
      delay(1000);
      break;

    case AMARELO: //um pouco pra esquerda (100º)

      s.write(100);
      delay(1000);
      break;

    case VERDE:  //mais pra esquerda (120º)

      s.write(120);
      delay(1000);
      break;

    case VERMELHO:   //esquerda máxima (140º)

      s.write(140);
      delay(1000);
      break;
  }  
}

void motorDePasso()
{
   //Gira o motor no sentido horario a 90 graus
   //para movimento dos mms

 myStepper.step(-512); 
 
 delay(200); 
}
