const byte ultrasonicTrigPin = 2; // Ultrasonic sensor trigger pin
const byte ultrasonicEchoPin = 3; // Ultrasonic sensor echo pin
const byte pirPin = 4; // PIR motion sensor pin
const byte buzzerPin = 5; // Buzzer pin
const byte ledPin = 6; // LED pin

volatile byte pirState = 0; // PIR motion sensor state

void setup() {
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pirPin), pirInterrupt, CHANGE);
  Serial.begin(9600);
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(ultrasonicTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(ultrasonicTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonicTrigPin, LOW);

  // Read the ultrasonic sensor distance
  long duration = pulseIn(ultrasonicEchoPin, HIGH);
  long distance = duration / 58;

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check the PIR motion sensor state
  if (pirState == HIGH) {
    Serial.println("Motion detected!");
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(500);
  } else {
    Serial.println("No motion detected");
  }

  delay(1000);
}

void pirInterrupt() {
  pirState = digitalRead(pirPin);
}
