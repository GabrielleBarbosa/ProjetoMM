//Pinos de conexao do modulo
const int s0 = 13;
const int s1 = 12;
const int s2 = 50;
const int s3 = 52;
const int out = 48;
 
//Pinos do led RGB
//int pinoledverm = 2;
//int pinoledverd = 3;
//int pinoledazul = 4;
 
//Variaveis cores
int red = 0;
int green = 0;
int blue = 0;
 
void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  //pinMode(pinoledverm, OUTPUT);
  //pinMode(pinoledverd, OUTPUT);
  //pinMode(pinoledazul, OUTPUT);
  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
}
 int frequency = 0;
void loop()
{
  //Detecta a cor
  color3();
  /*
  //Mostra valores no serial monitor
  red = map(red,300,1500,255,0);
  green = map(green,300,1500,255,0);
  blue = map(blue,300,1500,255,0);
  Serial.print("Vermelho :");
  Serial.print(red, DEC);
  Serial.print(" Verde : ");
  Serial.print(green, DEC);
  Serial.print(" Azul : ");
  Serial.print(blue, DEC);
  Serial.println();
  
 
  //Verifica se a cor vermelha foi detectada
 
  if (red > blue && red > green )
  {
    Serial.println("Vermelho");
    //digitalWrite(pinoledverm, LOW); //Acende o led vermelho
    //digitalWrite(pinoledverd, HIGH);
    //digitalWrite(pinoledazul, HIGH);
  }
 
  //Verifica se a cor azul foi detectada
  else if (red<blue && green<blue)
  {
    Serial.println("Azul");
    //digitalWrite(pinoledverm, HIGH);
    //digitalWrite(pinoledverd, HIGH);
    //digitalWrite(pinoledazul, LOW); //Acende o led azul
  }
 
  //Verifica se a cor verde foi detectada
  else if (green > red && green > blue)
  {
    Serial.println("Verde");
    //digitalWrite(pinoledverm, HIGH);
    //digitalWrite(pinoledverd, LOW); //Acende o led verde
    //digitalWrite(pinoledazul, HIGH);
  }
  Serial.println();
 
  //Delay para apagar os leds e reiniciar o processo
  //digitalWrite(pinoledverm, HIGH);
  //digitalWrite(pinoledverd, HIGH);
  //digitalWrite(pinoledazul, HIGH);
  */
  delay(1000);
}
 
void color()
{
  //Rotina que le o valor das cores
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  //count OUT, pRed, RED
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  //count OUT, pBLUE, BLUE
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);
  //count OUT, pGreen, GREEN
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void color2()
{
 digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency, 300,1500,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency,300,1500,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequency = map(frequency,300,1500,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
}

void color3()
{

  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(s2,LOW);
  digitalWrite(s3,LOW);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  
   // Printing the RED (R) value
  Serial.print("R = ");
    frequency = map(frequency,300,1500,255,0);

  Serial.print(frequency);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(s2,HIGH);
  digitalWrite(s3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
    frequency = map(frequency,300,1500,255,0);

  Serial.print(frequency);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(s2,LOW);
  digitalWrite(s3,HIGH);
  
  // Reading the output frequency
  frequency = pulseIn(out, LOW);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
    frequency = map(frequency,300,1500,255,0);

  Serial.println(frequency);
  delay(100);
}



