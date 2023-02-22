const uint8_t LedPin1 = 8;
const uint8_t LedPin2 = 9;
const uint8_t PIR1 = 2;
const uint8_t PIR2 = 3;

uint8_t PIRstate1 = LOW;
uint8_t PIRstate2 = LOW;

void setup()
{
    pinMode(LedPin1, OUTPUT);
    pinMode(PIR1, INPUT);
    pinMode(LedPin2, OUTPUT);
    pinMode(PIR2, INPUT);

    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(PIR1), PIR1MotionDetected, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIR2), PIR2MotionDetected, CHANGE);
}

void loop()
{
}

void PIR1MotionDetected()
{
    MotionDetected(PIR1, PIRstate1, LedPin1, "PIR1");
}

void PIR2MotionDetected()
{
    MotionDetected(PIR2, PIRstate2, LedPin2, "PIR2");
}

void MotionDetected(const uint8_t &input, uint8_t &state, const uint8_t &output, const String &device)
{
    state = digitalRead(input);
    if (state)
    {
        digitalWrite(output, HIGH);
        Serial.println("Motion Detected on " + device);
    }
    else
    {
        digitalWrite(output, LOW);
        Serial.println("No Motion Detected on " + device);
    }
}
