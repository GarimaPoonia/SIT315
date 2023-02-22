int sensorState = 0;
int buzzer = 7;  // buzzer connected to pin D7

void setup()
{
  pinMode(2, INPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2), motion, RISING);  //detects motion when sensor rises from 0 to 1
}

void loop()
{
  if (sensorState == HIGH) {
  digitalWrite(13, HIGH);
  Serial.println("Sensor activated!");
} 
  else {
  digitalWrite(13, LOW);
}

}

void motion(){
  Serial.println("Motion detected!");
  digitalWrite(buzzer, HIGH);
  //noTone(buzzer);     // Stops the buzzing sound
  Serial.println("Buzzed!");
}
