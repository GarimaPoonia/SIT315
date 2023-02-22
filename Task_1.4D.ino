const uint8_t LedPin1 = 8;
const uint8_t LedPin2 = 9;
const uint8_t LedPin3 = 10;
const uint8_t PIR1 = 2;
const uint8_t PIR2 = 3;
const uint8_t PIR3 = 4;
const byte TimerLed = 13;

volatile byte r,g,b = 0;

void setup()
{
    pinMode(TimerLed, OUTPUT);
    pinMode(LedPin1, OUTPUT);
    pinMode(PIR1, INPUT);
    pinMode(LedPin2, OUTPUT);
    pinMode(PIR2, INPUT);
    pinMode(LedPin3, OUTPUT);
    pinMode(PIR3, INPUT);

    Serial.begin(9600);

    PCICR |= 0b00000100; // turn on port d
    PCMSK2 |= 0b00011100; // enable pins 2, 3, and 4

    startTimer(); //0.5 Hz = 2 seconds per interupt
}

void loop()
{
    digitalWrite(LedPin1, r);
    digitalWrite(LedPin2, g);
    digitalWrite(LedPin3, b);
}

void startTimer(){
  noInterrupts();
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // led 13 to blink every 2 seconds using:
  // http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
  
  // x = 16 Mhz / (prescaler * x) - 1, x in Hz
  // => 16 Mhz / x(x+1) = prescalar
  
  OCR1A = 31249; // 0.5Hz = 16000000 / (1024 * 0.5) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  interrupts();
}

// timer interupt
ISR(TIMER1_COMPA_vect){
   digitalWrite(TimerLed, digitalRead(TimerLed) ^ 1);
}

//Port D interupt
ISR(PCINT2_vect) // Port D, PCINT16 - PCINT23
{
    r = PIND & B00000100;
    g = PIND & B00001000;
    b = PIND & B00010000;
    if (r)
    {
        Serial.println("PIR1 State Change");
    }
    if (g)
    {
        Serial.println("PIR2 State Change");
    }
    if (b)
    {
        Serial.println("PIR3 State Change");
    }
    
}
