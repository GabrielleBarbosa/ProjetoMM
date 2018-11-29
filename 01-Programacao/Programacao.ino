const int analogInPin = A0;  
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  double media = 0;
  for(int i=0; i<50; i++)
  {
    sensorValue = analogRead(analogInPin);
  
    Serial.print("sensor = ");
    Serial.println(sensorValue);

    media += sensorValue;
    delay(100);
  }

  if(media/50 <= 726 && media/50 >= 725)
    Serial.println("cor");
}
